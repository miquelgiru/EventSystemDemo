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

}


void Tester::OnPlayerInputEvent(const Event<PlayerInputEvents>& e) {

	std::cout << "Player Input received\n";

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