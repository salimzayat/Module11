#pragma once
#include <map>
#include <list>

enum  EventType
{
	ATTEMPT_SHOT,
	RECEIVE_PASS,
	SCORE_UPDATE,
	GAME_SCORE_UPDATE,
	GAME_OVER
};

class Event
{
public:
	Event(EventType t)
		: m_type(t)
	{

	}

	EventType GetType() { return m_type; }

protected:
	EventType m_type;
};


class EventListener
{
public:
	virtual void OnEvent(Event* pEvent) = 0;
};

class EventDispatcher
{
public:
	void RemoveListener(EventType e, EventListener* pListener);
	void AddListener(EventType e, EventListener* pListener);

	void DispatchEvent(Event* pEvent);

protected:
	std::map<EventType, std::list<EventListener*>> m_listeners;
};
