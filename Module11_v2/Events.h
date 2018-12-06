#pragma once
#include <map>
#include <list>
#include "Defines.h"

class BasketballTeam;
class Player;

enum EventType
{
	ATTEMPT_SHOT,
	RECEIVE_PASS,
	TEAM_SCORE_UPDATE,
	GAME_SCORE_UPDATE,
	GAME_OVER
};

class Event
{
public:
	Event(EventType t)
		: m_type(t)
	{
		// 
	}

	virtual ~Event() {}

	EventType GetType() { return m_type; }

private:
	EventType m_type;
};

class EventListener
{
public:
	virtual void OnEvent(Event* pEvent) = 0;
};

class EventDispatcher
{
public:
	virtual ~EventDispatcher() {}

	virtual void AddListener(EventType t, EventListener* pListener) = 0;
	virtual void RemoveListener(EventType t, EventListener* pListener) = 0;
	virtual void DispatchEvent(Event* pEvent) = 0;
};

class ConcreteEventDispatcher : public EventDispatcher
{
public:
	~ConcreteEventDispatcher();

	virtual void AddListener(EventType t, EventListener* pListener) override;
	virtual void RemoveListener(EventType t, EventListener* pListener) override;
	virtual void DispatchEvent(Event* pEvent) override;

private:
	std::map<EventType, std::list<EventListener*>> m_listeners;
};

// specific event types

class ScoreUpdateEvent : public Event
{
public:
	ScoreUpdateEvent(BasketballTeam* pTeam)
		: Event(EventType::TEAM_SCORE_UPDATE)
		, m_pTeam(pTeam)
	{}

	BasketballTeam* GetTeam() { return m_pTeam; }
	
private:
	BasketballTeam* m_pTeam;
};

class GameScoreUpdateEvent : public Event
{
public:
	GameScoreUpdateEvent(BasketballTeam* pTeam1, BasketballTeam* pTeam2)
		: Event(EventType::GAME_SCORE_UPDATE)
		, m_pTeam1(pTeam1)
		, m_pTeam2(pTeam2)
	{}

	BasketballTeam* GetTeam1() { return m_pTeam1; }
	BasketballTeam* GetTeam2() { return m_pTeam2; }

private:
	BasketballTeam* m_pTeam1;
	BasketballTeam* m_pTeam2;
};

class GameOverEvent : public Event
{
public:
	GameOverEvent(BasketballTeam* pTeam)
		: Event(EventType::GAME_OVER)
		, m_pTeam(pTeam)
	{}
	BasketballTeam* GetWinner() { return m_pTeam; }

private:
	BasketballTeam* m_pTeam;
};

class ReceivePassEvent : public Event
{
public:
	ReceivePassEvent(Player* pPlayer)
		: Event(EventType::RECEIVE_PASS)
		, m_pPlayer(pPlayer)
	{
		//
	}

	Player* GetPlayer() { return m_pPlayer; }
private:
	Player* m_pPlayer;
};

class AttemptShotEvent : public Event
{
public:

	AttemptShotEvent(Player* pPlayer, ShotResult result)
		: Event(EventType::ATTEMPT_SHOT)
		, m_pPlayer(pPlayer)
		, m_result(result)
	{
		// nothing else
	}

	Player* GetPlayer() { return m_pPlayer; }
	bool GetSuccess() { return m_result.success; }
	int GetExpectedPoints() { return m_result.attemptedPoints; }

private:
	Player* m_pPlayer;
	ShotResult m_result;
};

