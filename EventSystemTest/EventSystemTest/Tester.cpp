#include "Tester.h"


#define CUSTOM_EVENT_1 "CustomEvent1"
#define CUSTOM_EVENT_2 "CustomEvent2"
#define CUSTOM_EVENT_3 "CustomEvent3"


Tester::Tester() {

	events = EventManager::getInstance();
	AddPlayerInputEventListener(PlayerInputEvents::MOVE, Tester::OnPlayerInputEvent, this);
	AddPlayerInputEventListener(PlayerInputEvents::JUMP, Tester::OnPlayerInputEvent, this);
	AddPlayerInputEventListener(PlayerInputEvents::ATTACK, Tester::OnPlayerInputEvent, this);
	AddPlayerInputEventListener(PlayerInputEvents::DIE, Tester::OnPlayerInputEvent, this);

	AddGameStateEventListener(GameStateEvents::START, Tester::OnGameStateEvent, this);
	AddGameStateEventListener(GameStateEvents::PAUSE, Tester::OnGameStateEvent, this);
	AddGameStateEventListener(GameStateEvents::GAME_OVER, Tester::OnGameStateEvent, this);
	AddGameStateEventListener(GameStateEvents::EXIT, Tester::OnGameStateEvent, this);

	AddEntityInteractionsEventListener(EntityInteractionsEvents::COLLISSION, Tester::OnEntityInteractionsEvent, this);
	AddEntityInteractionsEventListener(EntityInteractionsEvents::PICKUP, Tester::OnEntityInteractionsEvent, this);
	AddEntityInteractionsEventListener(EntityInteractionsEvents::TRIGGER, Tester::OnEntityInteractionsEvent, this);

	AddGenericEventListener(CUSTOM_EVENT_1, Tester::OnGenericEvent, this);
	AddGenericEventListener(CUSTOM_EVENT_2, Tester::OnGenericEvent, this);

	//Another example to handle event directly with a lambda
	Tester* tester = this;
	EventManager::AddEventListener(CUSTOM_EVENT_3,
		[&tester](const Event<string>& e) { tester->OnGenericEvent(e); });

}


void Tester::RunTest() {

#pragma region Player_Input_Events
	//Test Player Input Events
	PlayerMoveEvent evMove;
	SendPlayerInputEvent(evMove);

	PlayerJumpEvent evJump;
	SendPlayerInputEvent(evJump);

	PlayerAttackEvent evAttack;
	evAttack.damage = 10;
	SendPlayerInputEvent(evAttack);
#pragma endregion Player_Input_Events

#pragma region Game_State_Events
	//Test Game State Events
	StartGameEvent evStart;
	SendGameStateEvent(evStart);

	PauseGameEvent evPause;
	SendGameStateEvent(evPause);

	GameOverEvent evGameOver;
	SendGameStateEvent(evGameOver);
#pragma endregion Game_State_Events

#pragma region Test_Entity_Events
	//Test Entity Interactions Events
	Entity player("Player");
	Entity enemy("Enemy");
	Entity trap("Trap");
	Entity item("Item");

	CollissionEvent evCol;
	evCol.collider1 = player;
	evCol.collider2 = enemy;
	SendEntityInteractionsEvent(evCol);

	TriggerEvent evTrig;
	evTrig.trigger = trap;
	SendEntityInteractionsEvent(evTrig);

	PickUpEvent evPick;
	evPick.pick = item;
	SendEntityInteractionsEvent(evPick);
#pragma endregion Entity_Events

#pragma region Generic_Events

	Event<string> genericEv1(CUSTOM_EVENT_1);
	SendGenericEvent(genericEv1);

	Event<string> genericEv2(CUSTOM_EVENT_2);
	SendGenericEvent(genericEv2);

	Event<string> genericEv3(CUSTOM_EVENT_3);
	SendGenericEvent(genericEv3);
#pragma endregion Generic_Events

}

void Tester::OnPlayerInputEvent(const Event<PlayerInputEvents>& e) 
{

	if (e.GetType() == PlayerInputEvents::MOVE) {
		std::cout << "Player has moved\n";
	}
	else if (e.GetType() == PlayerInputEvents::JUMP) {
		std::cout << "Player has jumped\n";
	}
	else if (e.GetType() == PlayerInputEvents::ATTACK) {

		auto attackEvent = static_cast<const PlayerAttackEvent&>(e);
		std::cout << "Player has attacked. Damage dealt:" << attackEvent.damage << " \n";
	}
	else if (e.GetType() == PlayerInputEvents::DIE) {
		std::cout << "Player has died\n";
	}
}

void Tester::OnGameStateEvent(const Event<GameStateEvents>& e) 
{

	if (e.GetType() == GameStateEvents::START) {
		std::cout << "Game started\n";
	}
	else if (e.GetType() == GameStateEvents::PAUSE) {
		std::cout << "Game paused\n";
	}
	else if (e.GetType() == GameStateEvents::GAME_OVER) {

		std::cout << "Game over\n";
	}
	else if (e.GetType() == GameStateEvents::EXIT) {
		std::cout << "Game exit\n";
	}
}

void Tester::OnEntityInteractionsEvent(const Event<EntityInteractionsEvents>& e) 
{

	if (e.GetType() == EntityInteractionsEvents::COLLISSION) {
		auto colEvent = static_cast<const CollissionEvent&>(e);
		std::cout << "Entity: " << colEvent.collider1.GetName() << " collided with Entity: " << colEvent.collider2.GetName() <<"\n";
	}
	else if (e.GetType() == EntityInteractionsEvents::PICKUP) {
		auto pickEvent = static_cast<const PickUpEvent&>(e);
		std::cout << "Item picked: " << pickEvent.pick.GetName() << "\n";
	}
	else if (e.GetType() == EntityInteractionsEvents::TRIGGER) {
		auto trigEvent = static_cast<const TriggerEvent&>(e);
		std::cout << "Item triggered: " << trigEvent.trigger.GetName() << "\n";
	}
}

void Tester::OnGenericEvent(const Event<string>& e) 
{
	if (e.GetType()._Equal(CUSTOM_EVENT_1)) {
		std::cout << "Custom event 1 received\n";
	}
	else if (e.GetType()._Equal(CUSTOM_EVENT_2)) {
		std::cout << "Custom event 2 received\n";
	}
	else if (e.GetType()._Equal(CUSTOM_EVENT_3)) {
		std::cout << "Custom event 3 received\n";
	}
}
