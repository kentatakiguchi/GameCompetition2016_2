#include "PlayerState_HoldBoth.h"
#include "../Player_EnumState.h"

PlayerState_HoldBoth::PlayerState_HoldBoth() {}

void PlayerState_HoldBoth::unique_init(Actor & actor) {

}

void PlayerState_HoldBoth::update(Actor & actor, float deltaTime) {

	if (InputMgr::GetInstance().IsKeyUp(KeyCode::R_SHIFT)) {
		change(StateElement((unsigned int)Player_EnumState::HOLD, ActionType::Left));
	}
	if (InputMgr::GetInstance().IsKeyUp(KeyCode::L_SHIFT)) {
		change(StateElement((unsigned int)Player_EnumState::HOLD, ActionType::Right));
	}
}

void PlayerState_HoldBoth::end() {

}
