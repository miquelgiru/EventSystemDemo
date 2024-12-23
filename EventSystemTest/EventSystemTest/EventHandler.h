#ifndef __EVENT_HANDLER__
#define __EVENT_HANDLER__

#include <string>
#include <map>
#include <functional>
#include <vector>

#include "Event.h"

using namespace std;

template<typename T>
class EventHandler
{
private:
    using Func = function<void(const Event<T>&)>;
    map<T, vector<Func>> m_listeners;

public:
    /// @brief Add an Listener to the type of event.
    /// @param type Event Type
    /// @param func Listener Function
    void AddListener(T type, const Func& callback){

        m_listeners[type].push_back(callback);
    }

    /// @brief Removes a listener based on its handle/ID.
    /// @param handle The handle/ID of the listener to remove
    void RemoveListener(T type, const Func& callback){

        auto& vec = m_listeners[type];
        auto it = find(vec.begin(), vec.end(), callback);
        if (it != vec.end()) {
            vec.erase(callback);
        }
    }

    /// @brief Executes the event to all its listeners.
    /// @param event Event callback to invoke.
    void DispatchEvent(const Event<T>& event){

        if (m_listeners.find(event.GetType()) == m_listeners.end())
            return; // Return if no Listner is there for this event.

        // Loop through all Listeners. If the event is not handled yet, we continue to process it.
        for (auto&& listener : m_listeners.at(event.GetType())) {
            if (!event.Handled()) listener(event);
        }
    }
};

#endif //__EVENT_HANDLER__
