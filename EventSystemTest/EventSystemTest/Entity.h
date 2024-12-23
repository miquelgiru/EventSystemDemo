#ifndef __ENTITY__
#define __ENTITY__

#include <string>

class Entity 
{	

public: 
	Entity() = default;
	Entity(std::string name) : m_name(name) {}
	std::string GetName() { return m_name; }

private:
	std::string m_name;
};


#endif //__ENTITY__
