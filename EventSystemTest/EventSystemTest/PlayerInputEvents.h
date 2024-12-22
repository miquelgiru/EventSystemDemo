#ifndef __PLAYER_INPUT_EVENTS_H__
#define __PLAYER_INPUT_EVENTS_H__

#include "Event.h"

enum class PlayerInputEvents {

	MOVE, JUMP, ATTACK, DIE
};


class PlayerMoveEvent : public Event<PlayerInputEvents>
{
public:
    PlayerMoveEvent() : Event<PlayerInputEvents>(PlayerInputEvents::MOVE) {}
    virtual ~PlayerMoveEvent() = default;
};

class PlayerJumpEvent : public Event<PlayerInputEvents>
{
public:
    PlayerJumpEvent() : Event<PlayerInputEvents>(PlayerInputEvents::JUMP) {}
    virtual ~PlayerJumpEvent() = default;
};

class PlayerAttackEvent : public Event<PlayerInputEvents>
{
public:
    PlayerAttackEvent() : Event<PlayerInputEvents>(PlayerInputEvents::ATTACK) {}
    virtual ~PlayerAttackEvent() = default;
    float damage = -1;
};

class PlayerDieEvent : public Event<PlayerInputEvents>
{
public:
    PlayerDieEvent() : Event<PlayerInputEvents>(PlayerInputEvents::DIE) {}
    virtual ~PlayerDieEvent() = default;
};

#endif //__PLAYER_INPUT_EVENTS_H__
