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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


//XMLDocument doc;
//XMLError err = doc.LoadFile("demo.xml");
//XMLElement* root = doc.FirstChildElement("config");
//// get the teams
//XMLNode* teamsNode = root->FirstChildElement("teams");
//for (XMLElement* teamElem = teamsNode->FirstChildElement("team"); teamElem != NULL; teamElem = teamElem->NextSiblingElement())
//{
//	int id = -1;
//	const char* name = "foo";
//	teamElem->QueryAttribute("id", &id);
//	teamElem->QueryStringAttribute("name", &name);
//	std::cout << "(" << id << ")" << name << std::endl;
//}
