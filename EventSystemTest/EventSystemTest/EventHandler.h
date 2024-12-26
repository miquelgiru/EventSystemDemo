#ifndef __EVENT_HANDLER__
#define __EVENT_HANDLER__

#include <string>
#include <map>
#include <functional>
#include <vector>
#include <any>

#include "Event.h"

using namespace std;

template<typename T>
class EventHandler
{
private:
    using Func = function<void(const Event<T>&)>;
    using FuncArgs = function<void(const Event<string>&, const vector<any>&)>;

    /// <summary>
    /// Map to handle listeners for predefinet (core) events
    /// </summary>
    map<T, vector<Func>> m_listeners;

    /// <summary>
    /// Map to handle listeners for generic (custom) events
    /// </summary>
    unordered_map<T, vector<FuncArgs>> m_genericListeners;

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
    void AddListener(T type, const Func& callback){

        m_listeners[type].push_back(callback);
    }

    /// <summary>
    /// Add a listener to the type of event
    /// </summary>
    /// <param name="type">Event type</param>
    /// <param name="callback">Callback listener callback with an event type and a vector args as parameters</param>
    void AddListener(T type, const FuncArgs& callback) {

        m_genericListeners[type].push_back(callback);
    }

    /// <summary>
    /// Removes a listener based on its type and callback
    /// </summary>
    /// <param name="type">Key of the map to search</param>
    /// <param name="callback">Value to remove from the map[key]</param>
    void RemoveListener(T type, const Func& callback){

        auto& vec = m_listeners[type];
        auto it = find(vec.begin(), vec.end(), callback);
        if (it != vec.end()) {
            vec.erase(callback);
        }
    }

    /// <summary>
    /// Removes a listener based on its type and callback
    /// </summary>
    /// <param name="type">Key of the map to search</param>
    /// <param name="callback">Value to remove from the map[key]</param>
    void RemoveListener(T type, const FuncArgs& callback) {

        auto& vec = m_listeners[type];
        auto it = find(vec.begin(), vec.end(), callback);
        if (it != vec.end()) {
            vec.erase(callback);
        }
    }

    /// <summary>
    /// Dispatch the event to all its listeners
    /// </summary>
    /// <param name="event">Event to be dispatched</param>
    void DispatchEvent(const Event<T>& event){

        auto it = m_listeners.find(event.GetType());
        if (it != m_listeners.end())
        {
            for (const auto& listener : it->second)
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
            for (const auto& listener : it->second)
            {
                listener(event, args); // Call the registered callbacks with arguments
            }
        }
    }
};

#endif //__EVENT_HANDLER__
