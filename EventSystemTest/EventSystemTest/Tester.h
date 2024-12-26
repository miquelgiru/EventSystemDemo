#ifndef __TESTER_H__
#define __TESTER_H__

#include<iostream>
#include "EventManager.h"

class Tester
{
public:
	Tester();
	virtual ~Tester() = default;

	void RunTest();

	//function Callbacks
	void OnPlayerInputEvent(const Event<PlayerInputEvents>& e);
	void OnGameStateEvent(const Event<GameStateEvents>& e);
	void OnEntityInteractionsEvent(const Event<EntityInteractionsEvents>& e);
	void OnGenericEvent(const Event<string>& e, const vector<any>& args);
};

#endif