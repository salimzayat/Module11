#pragma once
#include <list>
#include "Defines.h"
#include "Player.h"
#include "Events.h"

class BasketballTeam : public EventDispatcher, public EventListener
{
public:
	BasketballTeam(int id, const char* pName, const char* pCity, const char* pAbbreviation);
	~BasketballTeam();

	// get the score
	int GetScore() { return m_score; }
	// config level getters
	int GetID() { return m_id; }
	const char* GetName() { return m_pName; }
	const char* GetShortName() { return m_pAbbreviation; }
	const char* GetCity() { return m_city; }
	// select a player (i.e. pass the ball to a player)
	Player* SelectPlayer();
	// get the player associated with a position
	Player* GetPlayerForPosition(Position position);
	Player* GetPlayerGuarding(Player* pOpponentPlayer);
	// add a player to the team
	void AddPlayer(Player* pPlayer) { m_players.push_back(pPlayer); }
	// event methods
	virtual void AddListener(EventType t, EventListener* pListener) override { m_delegate->AddListener(t, pListener); }
	virtual void RemoveListener(EventType t, EventListener* pListener) override { m_delegate->RemoveListener(t, pListener); }
	virtual void OnEvent(Event* pEvent) override;

protected:
	virtual void DispatchEvent(Event* pEvent) override { m_delegate->DispatchEvent(pEvent); }
	// wrap the dispatch so we can also delete the event immediately afterwards
	void DispatchAndDeleteEvent(Event* pEvent);

private:
	int m_id;
	const char* m_city;
	const char* m_pName;
	const char* m_pAbbreviation;
	
	void HandleAttempShot(AttemptShotEvent* pEvent);
	void HandlePlayerReceivePass(ReceivePassEvent* pEvent);
	
	int m_score;
	std::list<Player*> m_players;
	EventDispatcher* m_delegate;
};

