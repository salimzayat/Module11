#pragma once
#include "Defines.h"
#include "Events.h"


class Defense
{
public:
	Defense(int rating);

	int GetRating() { return m_rating; }
	void SetRating(int rating) { m_rating = rating; }

private:
	int m_rating;
};

class Shooting
{
public:
	Shooting(int rating2Point, int rating3Point);

	void SetRatings(int rating2Point, int rating3Point);

	ShotResult Run(Defense* pDefense);

private:
	int m_rating2Point;
	int m_rating3Point;
};

class Player : public EventDispatcher
{
public:

	Player(int id, const char* pName, Position position);
	~Player();
	// attempt a shot against the given opponent
	void AttemptShot(Player* pOpponent);
	// receive a pass (i.e. select this player)
	void ReceivePass();
	// return the components
	Shooting* GetShootingComponent() { return m_shootingComponent;  }
	Defense* GetDefenseComponent() { return m_defenseComponent;  }
	// standard getters
	const char* GetName() { return m_pName; }
	Position GetPosition() { return m_position; }

	virtual void AddListener(EventType t, EventListener* pListener) override { m_delegate->AddListener(t, pListener); }
	virtual void RemoveListener(EventType t, EventListener* pListener) override { m_delegate->RemoveListener(t, pListener); }

protected:
	virtual void DispatchEvent(Event* pEvent) override { m_delegate->DispatchEvent(pEvent); }
	// wrap the dispatch so we can also delete the event immediately afterwards
	void DispatchAndDeleteEvent(Event* pEvent);

private:
	const char* m_pName;
	int m_id;
	Position m_position;
	
	Shooting* m_shootingComponent;
	Defense* m_defenseComponent;

	ConcreteEventDispatcher* m_delegate;
};