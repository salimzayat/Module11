#include "pch.h"
#include "BasketballGame.h"
#include <iostream>

BasketballGame::BasketballGame()
	: m_pTeam1(nullptr)
	, m_pTeam2(nullptr)
{
	// nothing else
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

void BasketballGame::Initialize()
{
	// let's relive the 2016 championships again
	m_pTeam1 = new BasketballTeam("Cleveland Cavaliers");
	m_pTeam2 = new BasketballTeam("Golden State Warrios");
}

void BasketballGame::Step()
{
	// update the first team
	m_pTeam1->Update();
	if (!IsOver())
	{
		// if the game is still happening, update the second team
		m_pTeam2->Update();
	}
}

bool BasketballGame::IsOver()
{
	// check the score to our target score of 11
	return ((m_pTeam1->GetScore() >= 11) || (m_pTeam2->GetScore() >= 11));
}

void BasketballGame::Render()
{
	std::cout << "=============================" << std::endl;
	std::cout << "| " << m_pTeam1->GetName() << " :: " << m_pTeam1->GetScore() << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << "| " << m_pTeam2->GetName() << " :: " << m_pTeam2->GetScore() << std::endl;
	std::cout << "=============================" << std::endl;
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

 