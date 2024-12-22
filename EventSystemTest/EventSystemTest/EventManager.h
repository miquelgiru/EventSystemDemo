#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include "EventHandler.h"
#include "PlayerInputEvents.h"
#include "GameStateEvents.h"
#include "EntityInteractionsEvents.h"
#include <memory>

class EventManager 
{

public:

    EventManager();
    static EventManager* getInstance();

    EventHandler<PlayerInputEvents>* GetPlayerInputEventHandler() { return m_playerInputEventsHandler; }
    EventHandler<GameStateEvents>* GetGameStateEventHandler() { return m_gameStateEventsHandler; }
    EventHandler<EntityInteractionsEvents>* GetEntityInteractionsEventHandler() { return m_entityInteractionsEventsHandler; }


    void SubscribeToPlayerInputEvent(PlayerInputEvents type, const std::function<void(const Event<PlayerInputEvents>&)>& callback);
    void SubscribeToGameStateEvent(GameStateEvents type, const std::function<void(const Event<GameStateEvents>&)>& callback);
    void SubscribeToEntityInteractionsEvent(EntityInteractionsEvents type, const std::function<void(const Event<EntityInteractionsEvents>&)>& callback);

#define AddPlayerInputEventListener(eventType, func, arg) EventManager::getInstance()->GetPlayerInputEventHandler()->AddListener(eventType, std::bind(&func, arg, std::placeholders::_1));
#define AddGameStateEventListener(eventType, func, arg) EventManager::getInstance()->GetGameStateEventHandler()->AddListener(eventType, std::bind(&func, arg, std::placeholders::_1));
#define AddEntityInteractionsEventListener(eventType, func, arg) EventManager::getInstance()->GetEntityInteractionsEventHandler()->AddListener(eventType, std::bind(&func, arg, std::placeholders::_1));

#define RemovePlayerInputEventListener(eventType, func, arg) EventManager::getInstance()->GetPlayerInputEventHandler()->RemoveListener(eventType, std::bind(&func, arg, std::placeholders::_1))
#define RemoveGameStateEventListener(eventType, func, arg) EventManager::getInstance()->GetGameStateEventHandler()->RemoveListener(eventType, std::bind(&func, arg, std::placeholders::_1))
#define RemoveEntityInteractionsEventListener(eventType, func, arg) EventManager::getInstance()->GetEntityInteractionsEventHandler()->RemoveListener(eventType, std::bind(&func, arg, std::placeholders::_1))

#define SendWindowEvent(_event) EventManager::getInstance()->WindowEventDispatcher.SendEvent(_event)
#define SendMouseEvent(_event) EventManager::getInstance()->MouseEventDispatcher.SendEvent(_event)
#define SendKeyEvent(_event) EventManager::getInstance()->KeyEventDispatcher.SendEvent(_event)

private:

    // Player Input Events
    EventHandler<PlayerInputEvents>* m_playerInputEventsHandler;
    // Game State Events
    EventHandler<GameStateEvents>* m_gameStateEventsHandler;
    // Entity Interactions Events
    EventHandler<EntityInteractionsEvents>* m_entityInteractionsEventsHandler;

    static std::unique_ptr<EventManager> m_instance;

};


#endif //__EVENT_MANAGER__

