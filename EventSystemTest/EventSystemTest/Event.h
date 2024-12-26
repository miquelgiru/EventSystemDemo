#ifndef __EVENT_H__
#define __EVENT_H__ 

#include <string>

using namespace std;

template <typename T>
class Event
{
protected:
    T m_type;

public:

    /// <summary>
    /// Default constructor
    /// </summary>
    Event() = default;
  
    /// <summary>
    /// Constructor. Create new event with type T
    /// </summary>
    /// <param name="type">Event type</param>
    Event(const T& type) : m_type(type){}

    /// <summary>
    /// Default destructor
    /// </summary>
    virtual ~Event() = default;

    /// <summary>
    /// Get event type
    /// </summary>
    /// <returns>Event type</returns>
    const T GetType() const { return m_type; }
};

#endif //__EVENT_H__