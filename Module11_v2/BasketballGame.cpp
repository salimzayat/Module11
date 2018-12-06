#include "pch.h"
#include "BasketballGame.h"
#include <iostream>
#include <assert.h>
#include "ResourceManager.h"

BasketballGame::BasketballGame()
	: m_pTeam1(nullptr)
	, m_pTeam2(nullptr)
	, m_isOver(false)
{
	// assume the current team is the first one
	m_pCurTeam = m_pTeam1;
	m_delegate = new ConcreteEventDispatcher();
	m_pUI = new SimpleUI();
	// and add the few events we know we need
	AddListener(EventType::GAME_SCORE_UPDATE, m_pUI);
	AddListener(EventType::GAME_OVER, m_pUI);
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
	delete m_delegate;
	delete m_pUI;
}

void BasketballGame::DispatchAndDeleteEvent(Event* pEvent)
{
	m_delegate->DispatchEvent(pEvent);
	delete pEvent;
}

void BasketballGame::Run()
{
	Initialize();
	do
	{
		Step();
	} while (!IsOver());
}

void BasketballGame::Initialize()
{
	Factory factory;

	int numTeams = ResourceManager::GetInst()->GetTeamCount();

	int teamId = RollRandomNumber(0, numTeams);

	m_pTeam1 = factory.GetTeam(teamId);
	m_pTeam2 = factory.GetTeam((teamId + 1) % numTeams);

	PopulateTeam(m_pTeam1, m_pTeam2, factory);
	PopulateTeam(m_pTeam2, m_pTeam1, factory);

	// and the event listeners
	m_pTeam1->AddListener(EventType::TEAM_SCORE_UPDATE, this);
	m_pTeam2->AddListener(EventType::TEAM_SCORE_UPDATE, this);

	m_pCurTeam = m_pTeam1;
	m_isOver = false;
}

void BasketballGame::PopulateTeam(BasketballTeam* pTeam, BasketballTeam* pOpponent, Factory factory)
{
	std::list<int> playerIds = ResourceManager::GetInst()->GetPlayerIdsForTeam(pTeam->GetID());
	for (int id : playerIds)
	{
		Player* pPlayer = factory.GetPlayer(id);
		pTeam->AddPlayer(pPlayer);
		// and add listeners
		pPlayer->AddListener(EventType::RECEIVE_PASS, m_pUI);
		pPlayer->AddListener(EventType::ATTEMPT_SHOT, m_pUI);
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
	return m_isOver;
}

void BasketballGame::OnEvent(Event* pEvent)
{
	assert(pEvent->GetType() == EventType::TEAM_SCORE_UPDATE);
	ScoreUpdateEvent* pScoreUpdateEvent = (ScoreUpdateEvent*)pEvent;
	DispatchAndDeleteEvent(new GameScoreUpdateEvent(m_pTeam1, m_pTeam2));
	if (pScoreUpdateEvent->GetTeam()->GetScore() >= 11)
	{
		m_isOver = true;
		DispatchAndDeleteEvent(new GameOverEvent(pScoreUpdateEvent->GetTeam()));
	}
 }