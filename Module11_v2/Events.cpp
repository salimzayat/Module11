#include "pch.h"
#include "Events.h"

ConcreteEventDispatcher::~ConcreteEventDispatcher()
{
	std::map<EventType, std::list<EventListener*>>::iterator it;
	for (it = m_listeners.begin(); it != m_listeners.end(); it++)
	{
		std::list<EventListener*> listeners = it->second;
		listeners.clear();
	}
	m_listeners.clear();
}

void ConcreteEventDispatcher::AddListener(EventType e, EventListener* pListener)
{
	m_listeners[e].push_back(pListener);
}


void ConcreteEventDispatcher::RemoveListener(EventType e, EventListener* pListener)
{
	if (m_listeners.find(e) != m_listeners.end())
	{
		std::list<EventListener*> listeners = m_listeners[e];
		listeners.remove(pListener);
	}
}

void ConcreteEventDispatcher::DispatchEvent(Event* pEvent)
{
	if (m_listeners.find(pEvent->GetType()) != m_listeners.end())
	{
		std::list<EventListener*> listeners = m_listeners[pEvent->GetType()];
		for (EventListener* pListener : listeners)
		{
			pListener->OnEvent(pEvent);
		}
	}
}
