#ifndef __EVENT_H__
#define __EVENT_H__ 

#include <string>

using namespace std;

template <typename T>
class Event
{

protected:
    T m_type;
    bool m_handled = false;

public:
    Event() = default;
    Event(const T& type) : m_type(type){}
    virtual ~Event() {}
    inline const T GetType() const { return m_type; }
    virtual bool Handled() const { return m_handled; }
};


class GanericEvent : Event
{

public:
    GanericEvent() = default;
    GenericEvent(const std::string& type) : Event<std::string>(m_type) {}
    virtual ~GanericEvent() {}
    inline const string GetType() const { return m_type; }
};

#endif //__EVENT_H__