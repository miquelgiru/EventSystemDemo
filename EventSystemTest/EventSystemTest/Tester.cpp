#include "Tester.h"


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
#pragma endregion Test_Entity_Events
}

void Tester::OnPlayerInputEvent(const Event<PlayerInputEvents>& e) {

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

void Tester::OnGameStateEvent(const Event<GameStateEvents>& e) {

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

void Tester::OnEntityInteractionsEvent(const Event<EntityInteractionsEvents>& e) {

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