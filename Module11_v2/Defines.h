#pragma once

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
	INVALID
};

int CalculateGridIndex(int width, int height, int x, int y);
Position GetPositionForString(const char* pPosition);
const char* GetStringForPosition(Position pos);