#include "pch.h"
#include "Team.h"
#include <iostream>
#include "Defines.h"


BasketballTeam::BasketballTeam(int id, const char* pName, const char* pCity, const char* pAbbreviation)
	: m_pName(pName)
	, m_id(id)
	, m_city(pCity)
	, m_pAbbreviation(pAbbreviation)
	, m_score(0)
{
	
}

Player* BasketballTeam::SelectPlayer()
{
	// apply some heurisitc?  go with the hot-hand?
	// for now, randomly choose
	Player* pResult = m_players.front();

	int place = RollRandomNumber(0, m_players.size());
	for (Player* pPlayer : m_players)
	{
		if (pPlayer->GetPosition() == place)
		{
			pResult = pPlayer;
			break;
		}
	}
	
	// return it
	// see if this workds
	pResult->DispatchEvent(new ReceivePassEvent(pResult));
	return pResult;

}

Player* BasketballTeam::GetPlayerForPosition(Position position)
{
	for (Player* pPlayer : m_players)
	{
		if (pPlayer->GetPosition() == position)
		{
			return pPlayer;
		}
	}
	return nullptr;
}

void BasketballTeam::OnEvent(Event* pEvent)
{
	switch (pEvent->GetType())
	{
	case EventType::ATTEMPT_SHOT:
		HandleAttempShot((AttemptShotEvent*)pEvent);
		break;
	case EventType::RECEIVE_PASS:
		HandlePlayerReceivePass((ReceivePassEvent*)pEvent);
		break;
	}
}

void BasketballTeam::HandleAttempShot(AttemptShotEvent* pEvent)
{
	if (pEvent->GetSuccess())
	{
		// update the score
		m_score += pEvent->GetExpectedPoints();
		// and dispatch
		DispatchEvent(new ScoreUpdateEvent(this));
	}
}

Player* BasketballTeam::GetPlayerGuarding(Player* pOpponentPlayer)
{
	return GetPlayerForPosition(pOpponentPlayer->GetPosition());
}

void BasketballTeam::HandlePlayerReceivePass(ReceivePassEvent* pEvent)
{
	// In a normal game, you might determine the closest player and have
	// that player switch to the player who just received a pass
	// at that point, you might set your player to be in a strategy that players them
	// up on the ball. We will just print it out
	std::cout << "oppponent " << pEvent->GetPlayer()->GetName() << " just received a pass. guarded by " << GetPlayerForPosition(pEvent->GetPlayer()->GetPosition())->GetName() << std::endl;
}