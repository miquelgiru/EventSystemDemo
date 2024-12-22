#ifndef __EVENT_H__
#define __EVENT_H__ 

template <typename T>
class Event
{

protected:
    T m_Type;
    bool m_Handled = false;

public:
    Event() = default;
    Event(T type) : m_Type(type){}
    virtual ~Event() {}
    inline const T GetType() const { return m_Type; }
    virtual bool Handled() const { return m_Handled; }
};

#endif //__EVENT_H__