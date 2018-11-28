#pragma once
#include "Defines.h"

class Offense
{
public:
	Offense(int rating2Point, int rating3Point);

private:
	int m_rating2Point;
	int m_rating3Point;
};

class Defense
{
public: 
	Defense(int rating);

private:
	int m_rating;
};

class Player
{
public:

	Player(int id, const char* pName, Position position);
	
	void AttemptShot(Player* pOpponent);

private:
	const char* m_pName;
	int m_id;
	Position m_position;
	
};

