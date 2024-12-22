
#include "EventManager.h"


EventManager::EventManager() {

}

EventManager* EventManager::getInstance()
{
	if (!m_instance)
		m_instance.reset(new EventManager());

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