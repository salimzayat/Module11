#pragma once
#include <list>
#include "Defines.h"
#include "Player.h"
#include "Events.h"

class BasketballTeam : public EventListener, public EventDispatcher
{
public:
	BasketballTeam(int id, const char* pName, const char* pCity, const char* pAbbreviation);

	// get the score
	int GetScore()
	{
		return m_score;
	}
	// the id
	int GetID() { return m_id; }
	// and the name
	const char* GetName()
	
{
		return m_pName;
	}
	const char* GetShortName() { return m_pAbbreviation; }
	const char* GetCity() { return m_city; }
	// select a player (i.e. pass the ball to a player)
	Player* SelectPlayer();
	// get the player associated with a position
	Player* GetPlayerForPosition(Position position);
	Player* GetPlayerGuarding(Player* pOpponentPlayer);
	
	// add a player to the team
	void AddPlayer(Player* pPlayer) { m_players.push_back(pPlayer); }

	virtual void OnEvent(Event* pEvent) override;

private:
	int m_id;
	const char* m_city;
	const char* m_pName;
	const char* m_pAbbreviation;


	void HandleAttempShot(AttemptShotEvent* pEvent);
	void HandlePlayerReceivePass(ReceivePassEvent* pEvent);

	int m_score;
	std::list<Player*> m_players;
	
};

class ScoreUpdateEvent : public Event
{
public:
	ScoreUpdateEvent(BasketballTeam* pTeam)
		: Event(EventType::SCORE_UPDATE)
		, m_pTeam(pTeam)
	{}

	BasketballTeam* GetTeam() { return m_pTeam; }
	int GetScore() { return m_pTeam->GetScore(); }

private:
	BasketballTeam* m_pTeam;
};
