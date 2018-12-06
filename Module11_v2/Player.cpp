#include "pch.h"
#include "Player.h"
#include <iostream>

Player::Player(int id, const char* pName, Position position)
	: m_id(id)
	, m_pName(pName)
	, m_position(position)
{
	m_shootingComponent = new Shooting(0, 0);
	m_defenseComponent = new Defense(0);
	m_delegate = new ConcreteEventDispatcher();
}

Player::~Player()
{
	delete m_shootingComponent;
	delete m_defenseComponent;
	delete m_delegate;
}

void Player::AttemptShot(Player* pOpponent)
{
	// leave it up to the component
	ShotResult result = m_shootingComponent->Run(pOpponent->GetDefenseComponent());
	DispatchAndDeleteEvent(new AttemptShotEvent(this, result));
}

void Player::ReceivePass()
{
	// std::cout << "player " << m_pName << " received a pass" << std::endl;
	DispatchAndDeleteEvent(new ReceivePassEvent(this));
}

void Player::DispatchAndDeleteEvent(Event* pEvent)
{
	// wrap the method to dispatch the event AND delete it
	// otherwise, the code will always be:
	// Event* pEvent = new Event(...);
	// DispatchEvent(pEvent);
	// delete pEvent;
	DispatchEvent(pEvent);
	delete pEvent;
}

Shooting::Shooting(int rating2Point, int rating3Point)
{
	SetRatings(rating2Point, rating3Point);
}

void Shooting::SetRatings(int rating2Point, int rating3Point)
{
	m_rating2Point = rating2Point;
	m_rating3Point = rating3Point;
}

ShotResult Shooting::Run(Defense* pDefense)
{
	// keep it simple
	// 1) roll a random number between the sum of 2pt and 3pt
	//		* select one of the two options from that distribution depending on where that number falls
	// 2) roll a random number between the sum of 2pt/3pt (whichever was selected) and the defensive rating, 
	//		* success if it falls on the offensive side of the distribution or not
	int twoOrThreePointer = RollRandomNumber(0, m_rating2Point + m_rating3Point);
	int shotThreshhold;
	ShotResult result;
	if (twoOrThreePointer < m_rating2Point)
	{
		shotThreshhold = m_rating2Point;
		result.attemptedPoints = 2;
	}
	else
	{
		shotThreshhold = m_rating3Point;
		result.attemptedPoints = 3;
	}

	// and now the success
	bool success = RollRandomNumber(0, shotThreshhold + pDefense->GetRating()) < shotThreshhold;
	result.success = success;
	return result;
}

Defense::Defense(int rating)
	: m_rating(rating)
{

}
