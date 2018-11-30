#pragma once

#include <string>
#include "Defines.h"

struct Point2d
{
	int x;
	int y;
};

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

int CalculateGridIndex(int width, int height, int x, int y);
Position GetPositionForString(const char* pPosition);
const char* GetStringForPosition(Position pos);
int RollRandomNumber(int min, int max);

struct PlayerConfig
{
	int id;
	std::string name;
	std::string team;
	int offense2Point;
	int offense3Point;
	int defense;
	Position position;

	PlayerConfig(int idIn, const char* nameIn, const char* teamIn, int offense2PointIn, int offense3PointIn, int defenseIn, const char* positionIn)
		: id(idIn)
		, name(std::string(nameIn))
		, team(teamIn)
		, offense2Point(offense2PointIn)
		, offense3Point(offense3PointIn)
		, defense(defenseIn)
		, position(GetPositionForString(positionIn))
	{

	}

	PlayerConfig()
		: PlayerConfig(-1, "", "", 0, 0, 0, "")
	{

	}
};

struct TeamConfig
{
	int id;
	std::string name;
	std::string city;
	std::string shortName;

	TeamConfig(int id, const char* name, const char* city, const char* shortName)
		: id(id)
		, name(std::string(name))
		, shortName(std::string(shortName))
		, city(std::string(city))
	{

	}

	TeamConfig()
		: TeamConfig(-1, "", "", "")
	{

	}
};

const TeamConfig k_DefaultTeamConfig;
const PlayerConfig k_DefaultPlayerConfig;

class DeleteMe
{
public:
	static const std::string k_name;
}; 