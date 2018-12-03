// Module11_v2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "tinyxml2.h"
using namespace tinyxml2;

#include "Renderable.h"
#include "RenderBuffer.h"
#include "UIElements.h"
#include "ResourceManager.h"
#include "Team.h"
#include "Factory.h"
#include "BasketballGame.h"
#include "MockUI.h"
#include <time.h>


int main()
{	
	srand(time(NULL));

	RenderBuffer* pBuffer = new RenderBuffer(30, 4);
	Renderable* pIcon = new Icon(8, 4);
	Renderable* pLabel = new Label(22, 4, "Player: FOO");
	pBuffer->AddToBuffer({ 0, 0 }, pIcon);
	pBuffer->AddToBuffer({ 8, 0 }, pLabel);
	pBuffer->Update();
	pBuffer->Render();
	
	

	// populate the two teams
	BasketballGame* pGame = new BasketballGame();
	MockUI* pUI = new MockUI();
	pGame->AddListener(EventType::GAME_SCORE_UPDATE, pUI);
	pGame->AddListener(EventType::GAME_OVER, pUI);

	pGame->Run();

	return 0;
}