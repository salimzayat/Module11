#include "pch.h"
#include "Player.h"

AttemptShotEvent::AttemptShotEvent(Player* pPlayer, ShotResult result)
	: Event(EventType::ATTEMPT_SHOT)
	, m_pPlayer(pPlayer)
	, m_result(result)
{

}

ReceivePassEvent::ReceivePassEvent(Player* pPlayer)
	: Event(EventType::RECEIVE_PASS)
	, m_pPlayer(pPlayer)
{

}

Player::Player(int id, const char* pName, Position position)
	: m_id(id)
	, m_pName(pName)
	, m_position(position)
{
	m_shootingComponent = new Shooting(0, 0);
	m_defenseComponent = new Defense(0);
}

Player::~Player()
{
	delete m_shootingComponent;
	delete m_defenseComponent;
}

void Player::ReceivePass()
{
	DispatchEvent(new ReceivePassEvent(this));
}

void Player::AttemptShot(Player* pOpponent)
{
	// leave it up to the component
	ShotResult result = m_shootingComponent->Run(pOpponent->GetDefenseComponent());
	// and dispatch
	DispatchEvent(new AttemptShotEvent(this, result));
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
	// 1) roll a random number between the sum of 2pt and 3pt and select one of the two options from that distribution depending on where that number falls
	// 2) roll a random number between the sum of 2pt/3pt (whichever was selected) and the defensive rating, success if it falls on the offensive side of the distribution or not
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