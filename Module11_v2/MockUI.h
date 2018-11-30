#pragma once
#include "Events.h"
#include "Team.h"
#include "Player.h"
#include "BasketballGame.h"

class MockUI : public EventListener
{
public:
	virtual void OnEvent(Event* pEvent);

private:
	void OnGameScore(GameScoreUpdateEvent* pEvent);
	void OnGameOver(GameOverEvent* pEvent);
	void OnShotAttempt(AttemptShotEvent* pEvent);
};

