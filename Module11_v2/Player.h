#pragma once
#include "Defines.h"
#include "Events.h"

struct ShotResult
{
	bool success;
	int attemptedPoints;	// 2 or 3
};

class Defense
{
public:
	Defense(int rating);

	int GetRating() { return m_rating; }
	void SetRating(int rating) { m_rating = rating; }

private:
	int m_rating;
};

class Shooting
{
public:
	Shooting(int rating2Point, int rating3Point);

	void SetRatings(int rating2Point, int rating3Point);

	ShotResult Run(Defense* pDefense);

private:
	int m_rating2Point;
	int m_rating3Point;
};


class Player : public EventDispatcher
{
public:

	Player(int id, const char* pName, Position position);
	~Player();
	
	void AttemptShot(Player* pOpponent);

	Shooting* GetShootingComponent() { return m_shootingComponent;  }
	Defense* GetDefenseComponent() { return m_defenseComponent;  }

	const char* GetName() { return m_pName; }
	Position GetPosition() { return m_position; }

	void ReceivePass();

private:
	const char* m_pName;
	int m_id;
	Position m_position;
	
	Shooting* m_shootingComponent;
	Defense* m_defenseComponent;
	
};

class AttemptShotEvent : public Event
{
public:
	AttemptShotEvent(Player* pPlayer, ShotResult result);

	Player* GetPlayer() { return m_pPlayer; }
	bool GetSuccess() { return m_result.success; }
	int GetExpectedPoints() { return m_result.attemptedPoints; }

private:
	Player* m_pPlayer;
	ShotResult m_result;
};

class ReceivePassEvent : public Event
{
public:
	ReceivePassEvent(Player* pPlayer);

	Player* GetPlayer() { return m_pPlayer; }
private:
	Player* m_pPlayer;
};