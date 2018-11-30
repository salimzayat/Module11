#pragma once
#include "AbstractGame.h"
#include "Team.h"
#include "Events.h"
#include "Factory.h"

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

class BasketballGame :
	public EventDispatcher, 
	public EventListener
{
public:
	BasketballGame();
	virtual ~BasketballGame();
	void Run();

protected:
	void PopulateTeam(BasketballTeam* pTeam, BasketballTeam* pOpponent, Factory factory);
	void Initialize();
	void Step();
	bool IsOver();
	void Render();
	void Shutdown();

	BasketballTeam* SwapCurrentTeam();

	virtual void OnEvent(Event* pEvent);

private:
	BasketballTeam* m_pTeam1;
	BasketballTeam* m_pTeam2;

	BasketballTeam* m_pCurTeam;
};

