#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include <memory>
#include <any>

#include "EventHandler.h"
#include "PlayerInputEvents.h"
#include "GameStateEvents.h"
#include "EntityInteractionsEvents.h"

using namespace std;

class EventManager 
{

private:

    // Player Input event handler
    EventHandler<PlayerInputEvents>* m_playerInputEventsHandler = nullptr;
    // Game State event handler
    EventHandler<GameStateEvents>* m_gameStateEventsHandler = nullptr;
    // Entity Interactions event handler
    EventHandler<EntityInteractionsEvents>* m_entityInteractionsEventsHandler = nullptr;
    //Generic event handler
    EventHandler<string>* m_genericEventsHandler = nullptr;

    //Singleton instance
    static unique_ptr<EventManager> m_instance;

public:

    /// <summary>
    /// Constructor
    /// </summary>
    EventManager();

    /// <summary>
    /// Destructor
    /// </summary>
    ~EventManager();

    /// <summary>
    /// Event Manager Singleton
    /// </summary>
    /// <returns>EventManager instance</returns>
    static EventManager* getInstance();

    //Getters
    EventHandler<PlayerInputEvents>* GetPlayerInputEventHandler()const { return m_playerInputEventsHandler; }
    EventHandler<GameStateEvents>* GetGameStateEventHandler()const { return m_gameStateEventsHandler; }
    EventHandler<EntityInteractionsEvents>* GetEntityInteractionsEventHandler()const { return m_entityInteractionsEventsHandler; }
    EventHandler<string>* GetGenericEventHandler()const {return m_genericEventsHandler;}

    //Definitions

    ///Add listeners defs: Adds a new listener to an eventhandler based on the event type. Binds callback function with sender. Returns the listener ID

#define AddPlayerInputEventListener(eventType, func, sender) EventManager::getInstance()->GetPlayerInputEventHandler()->AddListener(eventType, bind(&func, sender, placeholders::_1));
#define AddGameStateEventListener(eventType, func, sender) EventManager::getInstance()->GetGameStateEventHandler()->AddListener(eventType, bind(&func, sender, placeholders::_1));
#define AddEntityInteractionsEventListener(eventType, func, sender) EventManager::getInstance()->GetEntityInteractionsEventHandler()->AddListener(eventType, bind(&func, sender, placeholders::_1));
#define AddGenericEventListener(eventType, func, sender) EventManager::getInstance()->GetGenericEventHandler()->AddListener(eventType, bind(&func, sender, placeholders::_1, placeholders::_2));

    ///Remove listeners defs: Removes a new listener from an eventhandler based on the event type and a listener ID. Returns success result.

#define RemovePlayerInputEventListener(eventType, listenerID) EventManager::getInstance()->GetPlayerInputEventHandler()->RemoveListener(eventType, listenerID, false);
#define RemoveGameStateEventListener(eventType, listenerID) EventManager::getInstance()->GetGameStateEventHandler()->RemoveListener(eventType, listenerID, false);
#define RemoveEntityInteractionsEventListener(eventType, listenerID) EventManager::getInstance()->GetEntityInteractionsEventHandler()->RemoveListener(eventType, listenerID, false);
#define RemoveGenericEventListener(eventType, listenerID) EventManager::getInstance()->GetGenericEventHandler()->RemoveListener(eventType, listenerID);

    ///Send a new event using an event handler based on the event type.

#define SendPlayerInputEvent(_event) EventManager::getInstance()->GetPlayerInputEventHandler()->DispatchEvent(_event);
#define SendGameStateEvent(_event) EventManager::getInstance()->GetGameStateEventHandler()->DispatchEvent(_event);
#define SendEntityInteractionsEvent(_event) EventManager::getInstance()->GetEntityInteractionsEventHandler()->DispatchEvent(_event);
#define SendGenericEvent(_event, args) EventManager::getInstance()->GetGenericEventHandler()->DispatchEvent(_event, args);

    /// <summary>
    /// Add a new listener to the generic event handler
    /// </summary>
    /// <param name="eventID">Event identifier</param>
    /// <param name="callback">Function that contains the event to subscribe and the event args</param>
    static void AddEventListener(const string& eventID, function<void(const Event<string>&, const vector<any>&)> callback);
};


#endif //__EVENT_MANAGER__

