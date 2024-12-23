
#include "EventManager.h"

std::unique_ptr<EventManager> EventManager::m_instance = nullptr;

EventManager::EventManager() {

    m_playerInputEventsHandler = new EventHandler<PlayerInputEvents>();
    m_gameStateEventsHandler = new EventHandler<GameStateEvents>();
    m_entityInteractionsEventsHandler = new EventHandler<EntityInteractionsEvents>();
}

EventManager* EventManager::getInstance()
{
	if (!m_instance)
        m_instance = std::make_unique<EventManager>();

    return m_instance.get();
}

//template<typename EventType, typename Func, typename Arg>
//void EventManager::SubscribeToPlayerInputEvent(PlayerInputEvents type, Func func, Arg arg)
//{
//	m_playerInputEventsHandler->AddListener(type, callback);
//}
//
//void EventManager::SubscribeToGameStateEvent(GameStateEvents type, const std::function<void(const Event<GameStateEvents>&)>& callback)
//{
//	m_gameStateEventsHandler->AddListener(type, callback);
//}
//
//void EventManager::SubscribeToEntityInteractionsEvent(EntityInteractionsEvents type, const std::function<void(const Event<EntityInteractionsEvents>&)>& callback)
//{
//	m_entityInteractionsEventsHandler->AddListener(type, callback);
//}