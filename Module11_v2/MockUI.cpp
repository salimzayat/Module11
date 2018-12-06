#include "pch.h"
#include "MockUI.h"
#include <iostream>
#include "Defines.h"

void SimpleUI::OnEvent(Event* pEvent)
{
	switch (pEvent->GetType())
	{
		case EventType::ATTEMPT_SHOT:
			OnShotAttempt((AttemptShotEvent*)pEvent);
			break;
		case EventType::GAME_SCORE_UPDATE:
			OnGameScore((GameScoreUpdateEvent*)pEvent);
			break;
		case EventType::GAME_OVER:
			OnGameOver((GameOverEvent*)pEvent);
			break;
	}
}

void SimpleUI::OnShotAttempt(AttemptShotEvent* pEvent)
{
	std::cout << "[UI] " << pEvent->GetPlayer()->GetName() << " " << 
		(pEvent->GetSuccess() ? " made " : " missed ") << " a " 
		<< pEvent->GetExpectedPoints() << " pointer" << std::endl;
}

void SimpleUI::OnGameScore(GameScoreUpdateEvent* pEvent)
{
	std::cout << "[UI] +--------------------------------------+" << std::endl;
	std::cout << "[UI] " << pEvent->GetTeam1()->GetShortName() << " ::: " << pEvent->GetTeam1()->GetScore() << std::endl;
	std::cout << "[UI] " << pEvent->GetTeam2()->GetShortName() << " ::: " << pEvent->GetTeam2()->GetScore() << std::endl;
	std::cout << "[UI] +--------------------------------------+" << std::endl;
}

void SimpleUI::OnGameOver(GameOverEvent* pEvent)
{
	std::cout << "[UI] " << "**********************" << std::endl;
	std::cout << "[UI] " << pEvent->GetWinner()->GetCity() << " " << pEvent->GetWinner()->GetName() << " WIN!!!" << std::endl;
	std::cout << "[UI] " << "**********************" << std::endl;
}