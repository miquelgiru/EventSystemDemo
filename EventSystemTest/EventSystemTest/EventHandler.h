#ifndef __EVENT_HANDLER__
#define __EVENT_HANDLER__

#include <string>
#include <map>
#include <functional>
#include <vector>
#include <any>
#include <utility>

#include "Event.h"

using namespace std;

template<typename T>
class EventHandler
{
private:
    using Func = function<void(const Event<T>&)>;
    using FuncArgs = function<void(const Event<string>&, const vector<any>&)>;
    using ListenerID = int;

    /// <summary>
    /// Map to handle listeners for predefinet (core) events
    /// </summary>
    unordered_map<T, vector<pair<ListenerID, Func>>> m_listeners;

    /// <summary>
    /// Map to handle listeners for generic (custom) events
    /// </summary>
    unordered_map<T, vector<pair<ListenerID, FuncArgs>>> m_genericListeners;

    /// <summary>
    /// Listener id generator
    /// </summary>
    ListenerID listenerIndex = 0;

public:

    /// <summary>
    /// Default constructor
    /// </summary>
    EventHandler() = default;
    
    /// <summary>
    /// Destructor. Automatically cleans up all resources
    /// </summary>
    ~EventHandler() = default;  
    
    /// <summary>
    /// Add a listener to the type of event
    /// </summary>
    /// <param name="type">Event type</param>
    /// <param name="callback">Callback listener callback with an event type as a parameter</param>
    /// <returns>Listener id generated</returns>
    ListenerID AddListener(T type, const Func& callback){

        m_listeners[type].emplace_back(listenerIndex, callback);
        return listenerIndex++;
    }
  
    /// <summary>
    /// Add a listener to the type of event
    /// </summary>
    /// <param name="type">Event type</param>
    /// <param name="callback">Callback listener callback with an event type and a vector args as parameters</param>
    /// <returns>Listener id generated</returns>
    ListenerID AddListener(T type, const FuncArgs& callback) {

        m_genericListeners[type].emplace_back(listenerIndex, callback);
        return listenerIndex++;
    }
   
    /// <summary>
    /// Removes a listener based on its type and listener ID
    /// </summary>
    /// <param name="type">Type of the event where to remove the listener</param>
    /// <param name="id">Listener ID generated when added</param>
    /// <param name="isGenericEvent">If it is a core type event or a custom one</param>
    /// <returns>Operation success result</returns>
    bool RemoveListener(const T& type, const ListenerID & id, bool isGenericEvent = true) {

        if (!isGenericEvent) {
            auto it = m_listeners.find(type);
            if (it != m_listeners.end()) {
                auto& vec = it->second;
                auto funcIt = std::remove_if(vec.begin(), vec.end(), [id](const auto& pair) { return pair.first == id; });
                if (funcIt != vec.end()) {
                    vec.erase(funcIt, vec.end());
                    return true;
                }
            }
        }
        else {
            auto it = m_genericListeners.find(type);
            if (it != m_genericListeners.end()) {
                auto& vec = it->second;
                auto funcIt = std::remove_if(vec.begin(), vec.end(), [id](const auto& pair) { return pair.first == id; });
                if (funcIt != vec.end()) {
                    vec.erase(funcIt, vec.end());
                    return true;
                }
            }
        }
        
        return false;
    }

    /// <summary>
    /// Dispatch the event to all its listeners
    /// </summary>
    /// <param name="event">Event to be dispatched</param>
    void DispatchEvent(const Event<T>& event){

        auto it = m_listeners.find(event.GetType());
        if (it != m_listeners.end())
        {
            for (const auto& [id, listener] : it->second)
            {
                listener(event); // Call the registered callbacks
            }
        }
    }
 
    /// <summary>
    /// Dispatch the event to all its listeners
    /// </summary>
    /// <param name="event">event to be dispatched</param>
    /// <param name="args">event args to be dispatched</param>
    void DispatchEvent(const Event<string>& event, const vector<any>& args)
    {
        auto it = m_genericListeners.find(event.GetType());
        if (it != m_genericListeners.end())
        {
            for (const auto& [id, listener] : it->second)
            {
                listener(event, args); // Call the registered callbacks with arguments
            }
        }
    }
};

#endif //__EVENT_HANDLER__
