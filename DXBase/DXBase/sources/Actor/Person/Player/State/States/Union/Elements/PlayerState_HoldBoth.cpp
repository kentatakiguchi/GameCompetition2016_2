#include "PlayerState_HoldBoth.h"

PlayerState_HoldBoth::PlayerState_HoldBoth() {}

void PlayerState_HoldBoth::unique_init(Actor & actor) {

}

void PlayerState_HoldBoth::update(Actor & actor, float deltaTime) {

	//key_update();

	pad_update();
}

void PlayerState_HoldBoth::end() {

}

void PlayerState_HoldBoth::key_update(){
	if (InputMgr::GetInstance().IsKeyUp(KeyCode::R_SHIFT)) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
	}
	if (InputMgr::GetInstance().IsKeyUp(KeyCode::L_SHIFT)) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	}
}

void PlayerState_HoldBoth::pad_update(){
	if (InputMgr::GetInstance().IsButtonUp(Buttons::BUTTON_R1)) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
	}
	if (InputMgr::GetInstance().IsButtonUp(Buttons::BUTTON_L1)) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	}
}
