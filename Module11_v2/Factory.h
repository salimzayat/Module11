#pragma once
#include "Defines.h"
#include "Team.h"
#include "Player.h"

class Factory
{
public:
	BasketballTeam* GetTeam(int teamId);
	Player* GetPlayer(int playerId);
};

