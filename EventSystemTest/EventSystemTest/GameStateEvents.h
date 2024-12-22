#ifndef __GAME_STATE_EVENTS_H__
#define __GAME_STATE_EVENTS_H__

#include "Event.h"

enum class GameStateEvents {

    START, PAUSE, GAME_OVER, EXIT
};


class StartGameEvent : public Event<GameStateEvents>
{
public:
    StartGameEvent() : Event<GameStateEvents>(GameStateEvents::START) {}
    virtual ~StartGameEvent() = default;
};

class PauseGameEvent : public Event<GameStateEvents>
{
public:
    PauseGameEvent() : Event<GameStateEvents>(GameStateEvents::PAUSE) {}
    virtual ~PauseGameEvent() = default;
};

class GameOverEvent : public Event<GameStateEvents>
{
public:
    GameOverEvent() : Event<GameStateEvents>(GameStateEvents::GAME_OVER) {}
    virtual ~GameOverEvent() = default;
};

class ExitGameEvent : public Event<GameStateEvents>
{
public:
    ExitGameEvent() : Event<GameStateEvents>(GameStateEvents::EXIT) {}
    virtual ~ExitGameEvent() = default;
};

#endif //__GAME_STATE_EVENTS_H__