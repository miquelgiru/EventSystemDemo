
#include "EventManager.h"

unique_ptr<EventManager> EventManager::m_instance = nullptr;

EventManager::EventManager() 
{
    m_playerInputEventsHandler = new EventHandler<PlayerInputEvents>();
    m_gameStateEventsHandler = new EventHandler<GameStateEvents>();
    m_entityInteractionsEventsHandler = new EventHandler<EntityInteractionsEvents>();
    m_genericEventsHandler = new EventHandler<string>();
}

EventManager* EventManager::getInstance()
{
	if (!m_instance)
        m_instance = make_unique<EventManager>();

    return m_instance.get();
}

void EventManager::AddEventListener(const string& eventID, function<void(const Event<string>&, const vector<any>&)> callback)
{
    EventManager::getInstance()->GetGenericEventHandler()->AddListener(eventID, callback);
}
