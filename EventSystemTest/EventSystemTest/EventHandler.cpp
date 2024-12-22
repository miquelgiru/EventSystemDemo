
#include "EventHandler.h"

template<typename T>
void EventHandler<T>::AddListener(T type, const std::function<void(const Event<T>&)>& callback) {

	m_listeners[type].push_back(callback);
}

template<typename T>
void EventHandler<T>::RemoveListener(T type, const std::function<void(const Event<T>&)>& callback) {

    auto& vec = m_listeners[type];
    auto it = std::find(vec.begin(), vec.end(), callback);
    if (it != vec.end()) {
        vec.erase(callback);
    }
}

template<typename T>
void EventHandler<T>::ExecuteEvent(const Event<T>& event) {

    if (m_listeners.find(event.GetType()) == m_listeners.end())
        return; // Return if no Listner is there for this event.

    // Loop through all Listeners. If the event is not handled yet, we continue to process it.
    for (auto&& listener : m_listeners.at(event.GetType())) {
        if (!event.Handled()) listener(event);
    }
}


