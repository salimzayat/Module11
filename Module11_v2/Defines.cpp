#include "pch.h"
#include "Defines.h"
#include <string>

int CalculateGridIndex(int width, int height, int x, int y)
{
	if ((x < 0) || (x >= width) || (y < 0) || (y >= height))
	{
		return -1;
	}
	else
	{
		return y * width + x;
	}
}

Position GetPositionForString(const char* pPosition)
{
	std::string pos = std::string(pPosition);
	if (pos.compare("C") == 0)
	{
		return Position::CENTER;
	}
	else if (pos.compare("PG") == 0)
	{
		return Position::POINT_GUARD;
	}
	else if (pos.compare("SG") == 0)
	{
		return Position::SHOOTING_GUARD;
	}
	else if (pos.compare("SF") == 0)
	{
		return Position::SMALL_FORWARD;
	}
	else if (pos.compare("PF") == 0)
	{
		return Position::POWER_FORWARD;
	}
	else
	{
		return Position::INVALID;
	}
}

const char* GetStringForPosition(Position pos)
{
	switch (pos)
	{
	case Position::CENTER:
		return "C";
	case Position::POINT_GUARD:
		return "PG";
	case Position::SHOOTING_GUARD:
		return "SG";
	case Position::SMALL_FORWARD:
		return "SF";
	case Position::POWER_FORWARD:
		return "PF";
	default:
		return "";
	}
}