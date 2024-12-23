#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include "EventHandler.h"
#include "PlayerInputEvents.h"
#include "GameStateEvents.h"
#include "EntityInteractionsEvents.h"
#include <memory>

using namespace std;

class EventManager 
{

private:

    // Player Input Events
    EventHandler<PlayerInputEvents>* m_playerInputEventsHandler = nullptr;
    // Game State Events
    EventHandler<GameStateEvents>* m_gameStateEventsHandler = nullptr;
    // Entity Interactions Events
    EventHandler<EntityInteractionsEvents>* m_entityInteractionsEventsHandler = nullptr;
    //Generic Events
    EventHandler<string>* m_genericEventsHandler = nullptr;


    static unique_ptr<EventManager> m_instance;

public:

    EventManager();
    static EventManager* getInstance();

    inline EventHandler<PlayerInputEvents>* GetPlayerInputEventHandler() { return m_playerInputEventsHandler; }
    inline EventHandler<GameStateEvents>* GetGameStateEventHandler() { return m_gameStateEventsHandler; }
    inline EventHandler<EntityInteractionsEvents>* GetEntityInteractionsEventHandler() { return m_entityInteractionsEventsHandler; }
    inline EventHandler<string>* GetGenericEventHandler() {return m_genericEventsHandler;}

#define AddPlayerInputEventListener(eventType, func, arg) EventManager::getInstance()->GetPlayerInputEventHandler()->AddListener(eventType, bind(&func, arg, placeholders::_1));
#define AddGameStateEventListener(eventType, func, arg) EventManager::getInstance()->GetGameStateEventHandler()->AddListener(eventType, bind(&func, arg, placeholders::_1));
#define AddEntityInteractionsEventListener(eventType, func, arg) EventManager::getInstance()->GetEntityInteractionsEventHandler()->AddListener(eventType, bind(&func, arg, placeholders::_1));
#define AddGenericEventListener(eventID, func, arg) EventManager::getInstance()->GetGenericEventHandler()->AddListener(eventID, bind(&func, arg, placeholders::_1));

#define RemovePlayerInputEventListener(eventType, func, arg) EventManager::getInstance()->GetPlayerInputEventHandler()->RemoveListener(eventType, bind(&func, arg, placeholders::_1));
#define RemoveGameStateEventListener(eventType, func, arg) EventManager::getInstance()->GetGameStateEventHandler()->RemoveListener(eventType, bind(&func, arg, placeholders::_1));
#define RemoveEntityInteractionsEventListener(eventType, func, arg) EventManager::getInstance()->GetEntityInteractionsEventHandler()->RemoveListener(eventType, bind(&func, arg, placeholders::_1));
//todo remove generic event

#define SendPlayerInputEvent(_event) EventManager::getInstance()->GetPlayerInputEventHandler()->DispatchEvent(_event);
#define SendGameStateEvent(_event) EventManager::getInstance()->GetGameStateEventHandler()->DispatchEvent(_event);
#define SendEntityInteractionsEvent(_event) EventManager::getInstance()->GetEntityInteractionsEventHandler()->DispatchEvent(_event);
#define SendGenericEvent(_event) EventManager::getInstance()->GetGenericEventHandler()->DispatchEvent(_event);


    static void AddEventListener(const string& eventID, function<void(const Event<string>&)> callback);
};


#endif //__EVENT_MANAGER__

