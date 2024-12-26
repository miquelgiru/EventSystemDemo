#include "Tester.h"


#define CUSTOM_EVENT_1 "CustomEvent1"
#define CUSTOM_EVENT_2 "CustomEvent2"
#define CUSTOM_EVENT_3 "CustomEvent3"


Tester::Tester() {

	//Core events subscriptions using definitions
	coreEventToRemove  = AddPlayerInputEventListener(PlayerInputEvents::MOVE, Tester::OnPlayerInputEvent, this);
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

	//Example of a generic event subscription with a lamda
	EventManager::AddEventListener(CUSTOM_EVENT_1, [](const Event<string>& e, const vector<any>& args) {
		try
		{
			int code = any_cast<int>(args[0]);
			auto message = any_cast<string>(args[1]);
			cout << "Event received: " << e.GetType() << ", Code: " << code << ", Message: " << message << endl;
		}
		catch (const bad_any_cast& ex)
		{
			cerr << "Error: " << ex.what() << endl;
		}
	});

	//Example of a generic event subscription with a new method
	genericEventToRemove = AddGenericEventListener(CUSTOM_EVENT_2, Tester::OnGenericEvent, this)
}


void Tester::RunTest() {

#pragma region Player_Input_Events_Test
	//Test Player Input Events
	PlayerMoveEvent evMove;
	SendPlayerInputEvent(evMove);

	PlayerJumpEvent evJump;
	SendPlayerInputEvent(evJump);

	PlayerAttackEvent evAttack;
	evAttack.damage = 10;
	SendPlayerInputEvent(evAttack);

	bool removed = RemovePlayerInputEventListener(evMove.GetType(), coreEventToRemove);
	cout << "Event removed " << removed << endl;



#pragma endregion Player_Input_Events_Test

#pragma region Game_State_Events_Test
	//Test Game State Events
	StartGameEvent evStart;
	SendGameStateEvent(evStart);

	PauseGameEvent evPause;
	SendGameStateEvent(evPause);

	GameOverEvent evGameOver;
	SendGameStateEvent(evGameOver);
#pragma endregion Game_State_Events_Test

#pragma region Test_Entity_Events_Test
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
#pragma endregion Entity_Events_Test

#pragma region Generic_Events_Test

	Event<string> genericEv1(CUSTOM_EVENT_1);
	vector<any> data1{ 1, string("data")};
	SendGenericEvent(genericEv1, data1);

	Event<string> genericEv2(CUSTOM_EVENT_2);
	vector<any> data2{ 2, string("data"), true };
	SendGenericEvent(genericEv2, data2);

	removed = RemoveGenericEventListener(genericEv2.GetType(), genericEventToRemove);
	cout << "Event removed " << removed << endl;


#pragma endregion Generic_Events_Test

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

void Tester::OnGenericEvent(const Event<string>& e, const vector<any>& args)
{
	try
	{
		int code = any_cast<int>(args[0]);
		string message = any_cast<string>(args[1]);
		bool check = any_cast<bool>(args[2]);
		cout << "Event received: " << e.GetType() << ", Code: " << code << ", Message: " << message  << ". Checked: " << check << endl;
	}
	catch (const bad_any_cast& ex)
	{
		cerr << "Error: " << ex.what() << endl;
	}
}
