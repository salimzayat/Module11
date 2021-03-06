// Module11_v2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "ResourceManager.h"
#include "Team.h"
#include "Player.h"
#include "Factory.h"
#include "BasketballGame.h"
#include <time.h>

int main()
{
	srand(time(NULL));
	BasketballGame* pGame = new BasketballGame();
	pGame->Run();

	delete pGame;

	return 0;
}