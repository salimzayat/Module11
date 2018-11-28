#include "pch.h"
#include "AbstractGame.h"


AbstractGame::AbstractGame()
{
	// do any initialization
}


AbstractGame::~AbstractGame()
{
	// do any cleanup
}

void AbstractGame::Run()
{
	// this is the actual game loop
	Initialize();
	Render();
	while (!IsOver())
	{
		Step();
		Render();
	}
	Shutdown();
}
