#include "pch.h"
#include "BasketballGame.h"
#include <iostream>
#include <assert.h>
#include "ResourceManager.h"

BasketballGame::BasketballGame()
	: m_pTeam1(nullptr)
	, m_pTeam2(nullptr)
{
	// assume the current team is the first one
	m_pCurTeam = m_pTeam1;
}

BasketballGame::~BasketballGame()
{
	// free up the memory
	if (m_pTeam1 != nullptr)
	{
		delete m_pTeam1;
	}
	if (m_pTeam2 != nullptr)
	{
		delete m_pTeam2;
	}
}

void BasketballGame::Run()
{
	Initialize();
	do
	{
		Step();
		Render();
	} while (!IsOver());
	Shutdown();
}

void BasketballGame::Initialize()
{
	// let's relive the 2016 championships again
	ResourceManager::GetInst()->LoadXml();
	Factory factory;

	int numTeams = ResourceManager::GetInst()->GetTeamCount();

	int teamId = RollRandomNumber(0, numTeams);

	m_pTeam1 = factory.GetTeam(teamId);
	m_pTeam2 = factory.GetTeam((teamId + 1) % numTeams);

	PopulateTeam(m_pTeam1, m_pTeam2, factory);
	PopulateTeam(m_pTeam2, m_pTeam1, factory);

	// and the event listeners
	m_pTeam1->AddListener(EventType::SCORE_UPDATE, this);
	m_pTeam2->AddListener(EventType::SCORE_UPDATE, this);

	m_pCurTeam = m_pTeam1;
}

void BasketballGame::PopulateTeam(BasketballTeam* pTeam, BasketballTeam* pOpponent, Factory factory)
{
	std::list<int> playerIds = ResourceManager::GetInst()->GetPlayerIdsForTeam(pTeam->GetID());
	for (int id : playerIds)
	{
		Player* pPlayer = factory.GetPlayer(id);
		pTeam->AddPlayer(pPlayer);
		// and add listeners
		pPlayer->AddListener(EventType::ATTEMPT_SHOT, pTeam);
		pPlayer->AddListener(EventType::RECEIVE_PASS, pOpponent);
	}
}



void BasketballGame::Step()
{
	// swap the team
	BasketballTeam* pTeam = SwapCurrentTeam();
	BasketballTeam* pOtherTeam = (pTeam == m_pTeam1) ? m_pTeam2 : m_pTeam1;
	// let that team select its current player
	Player* pPlayerOff = pTeam->SelectPlayer();
	// just use the defender for that postion
	// TODO: expose this as a method which takes in the player, and then let it choose the defender more intelligently
	Player* pPlayerDef = pOtherTeam->GetPlayerGuarding(pPlayerOff);
	// now simulate it
	pPlayerOff->AttemptShot(pPlayerDef);
}

BasketballTeam* BasketballGame::SwapCurrentTeam()
{
	if (m_pCurTeam == m_pTeam1)
	{
		m_pCurTeam = m_pTeam2;
	}
	else
	{
		m_pCurTeam = m_pTeam1;
	}
	return m_pCurTeam;
}

bool BasketballGame::IsOver()
{
	// check the score to our target score of 11
	return ((m_pTeam1->GetScore() >= 11) || (m_pTeam2->GetScore() >= 11));
}

void BasketballGame::Render()
{
	//std::cout << "=============================" << std::endl;
	//std::cout << "| " << m_pTeam1->GetName() << " :: " << m_pTeam1->GetScore() << std::endl;
	//std::cout << "-----------------------------" << std::endl;
	//std::cout << "| " << m_pTeam2->GetName() << " :: " << m_pTeam2->GetScore() << std::endl;
	//std::cout << "=============================" << std::endl;
} 

void BasketballGame::Shutdown()
{
	// print out the winner
	if (m_pTeam1->GetScore() > m_pTeam2->GetScore()) 
	{
		std::cout << m_pTeam1->GetName() << " WIN!!" << std::endl;
	}
	else if (m_pTeam2->GetScore() > m_pTeam1->GetScore())
	{
		std::cout << m_pTeam2->GetName() << " WIN!!" << std::endl;
	}
	else
	{
		std::cout << m_pTeam1->GetName() << " and " << m_pTeam2->GetName() << " tie" << std::endl;
	}
}

void BasketballGame::OnEvent(Event* pEvent)
{
	assert(pEvent->GetType() == EventType::SCORE_UPDATE);
	ScoreUpdateEvent* pScoreUpdateEvent = (ScoreUpdateEvent*)pEvent;
	DispatchEvent(new GameScoreUpdateEvent(m_pTeam1, m_pTeam2));
	if (pScoreUpdateEvent->GetScore() >= 11)
	{
		DispatchEvent(new GameOverEvent(pScoreUpdateEvent->GetTeam()));
	}
 }