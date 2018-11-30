#include "pch.h"
#include "Events.h"


void EventDispatcher::AddListener(EventType e, EventListener* pListener)
{
	m_listeners[e].push_back(pListener);
}

void EventDispatcher::RemoveListener(EventType e, EventListener* pListener)
{
	if (m_listeners.find(e) != m_listeners.end())
	{
		std::list<EventListener*> listeners = m_listeners[e];
		listeners.remove(pListener);
	}
}

void EventDispatcher::DispatchEvent(Event* pEvent)
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