#ifndef __ENTITY_INTERACTIONS_EVENTS_H__
#define __ENTITY_INTERACTIONS_EVENTS_H__

#include "Event.h"
#include "Entity.h"

enum class EntityInteractionsEvents {

    COLLISSION, TRIGGER, PICKUP
};


class CollissionEvent : public Event<EntityInteractionsEvents>
{
public:
    CollissionEvent() : Event<EntityInteractionsEvents>(EntityInteractionsEvents::COLLISSION) {}
    virtual ~CollissionEvent() = default;
    Entity collider1,  collider2;
};

class TriggerEvent : public Event<EntityInteractionsEvents>
{
public:
    TriggerEvent() : Event<EntityInteractionsEvents>(EntityInteractionsEvents::TRIGGER) {}
    virtual ~TriggerEvent() = default;
    Entity trigger;
};

class PickUpEvent : public Event<EntityInteractionsEvents>
{
public:
    PickUpEvent() : Event<EntityInteractionsEvents>(EntityInteractionsEvents::PICKUP) {}
    virtual ~PickUpEvent() = default;
    Entity pick;
};


#endif //__ENTITY_INTERACTIONS_EVENTS_H__