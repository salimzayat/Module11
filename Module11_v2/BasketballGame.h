#pragma once
#include "AbstractGame.h"
#include "Team.h"
#include "Events.h"
#include "Factory.h"
#include "MockUI.h"

class BasketballGame : public EventDispatcher, public EventListener
{
public:
	BasketballGame();
	virtual ~BasketballGame();
	void Run();
	// from EventDispatcher
	virtual void AddListener(EventType t, EventListener* pListener) override { m_delegate->AddListener(t, pListener); }
	virtual void RemoveListener(EventType t, EventListener* pListener) override { m_delegate->RemoveListener(t, pListener); }

private:
	// given two teams and a factory, populate the teams and apply all the necessary event listening
	void PopulateTeam(BasketballTeam* pTeam, Factory factory);
	// initialize the game
	void Initialize();
	// step through the sim
	void Step();
	// return whether or not the game is over
	bool IsOver();
	// swap the current team in possession of the ball
	BasketballTeam* SwapCurrentTeam();
	// from EventListener
	virtual void OnEvent(Event* pEvent);
	// from EventDispatcher
	virtual void DispatchEvent(Event* pEvent) override { m_delegate->DispatchEvent(pEvent); }
	// wrap the dispatch so we can also delete the event immediately afterwards
	void DispatchAndDeleteEvent(Event* pEvent);
	// configure listeners
	void ConfigureListeners();
	void ConfigureListenerForPlayer(Player* pPlayer, BasketballTeam* pTeam, BasketballTeam* pOpposingTeam);

	// and all the vars...
	BasketballTeam* m_pTeam1;
	BasketballTeam* m_pTeam2;
	BasketballTeam* m_pCurTeam;

	bool m_isOver;

	EventDispatcher* m_delegate;
	SimpleUI* m_pUI;
};

