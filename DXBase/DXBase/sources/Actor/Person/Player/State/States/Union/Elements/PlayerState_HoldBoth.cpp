#include "PlayerState_HoldBoth.h"

PlayerState_HoldBoth::PlayerState_HoldBoth() {}

void PlayerState_HoldBoth::unique_init() {

}

void PlayerState_HoldBoth::update(float deltaTime) {
}

void PlayerState_HoldBoth::end() {}

void PlayerState_HoldBoth::key_input(){

	if (InputMgr::GetInstance().IsKeyUp(KeyCode::R_SHIFT)) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
	}
	if (InputMgr::GetInstance().IsKeyUp(KeyCode::L_SHIFT)) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	}
}

void PlayerState_HoldBoth::pad_input(){

	if (InputMgr::GetInstance().IsButtonUp(Buttons::BUTTON_R1)) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
	}
	if (InputMgr::GetInstance().IsButtonUp(Buttons::BUTTON_L1)) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	}
}

