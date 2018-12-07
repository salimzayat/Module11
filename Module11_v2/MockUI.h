#pragma once
#include "Events.h"
#include "Team.h"
#include "Player.h"

class SimpleUI : public EventListener
{
public:
	virtual void OnEvent(Event* pEvent) override;

private:
	void OnGameScore(GameScoreUpdateEvent* pEvent);
	void OnGameOver(GameOverEvent* pEvent);
	void OnShotAttempt(AttemptShotEvent* pEvent);
};

