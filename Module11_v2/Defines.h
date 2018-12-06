#pragma once

#include <string>

enum Position
{
	POINT_GUARD,
	SHOOTING_GUARD,
	SMALL_FORWARD,
	POWER_FORWARD,
	CENTER,
	NUM_POSITIONS,
	INVALID
};

struct PlayerConfig
{
	int id;
	std::string name;
	std::string team;
	int offense2Point;
	int offense3Point;
	int defense;
	Position position;
};

struct TeamConfig
{
	int id;
	std::string name;
	std::string city;
	std::string shortName;

};

struct ShotResult
{
	bool success;
	int attemptedPoints;	// 2 or 3
};

// map a string (e.g. "C", "PG") to a position enum value
Position GetPositionForString(const char* pPosition);
// map a position enum value to a string (e.g. "C", "PG")
const char* GetStringForPosition(Position pos);
// roll a random number between (inclusive) min and (exclusive) max
int RollRandomNumber(int min, int max);


// define two defaults to use if all else fails
const TeamConfig k_defaultTeamConfig = { -1, "", "", "" };
const PlayerConfig k_defaultPlayerConfig = { -1, "", "", 0, 0, 0, Position::INVALID };
