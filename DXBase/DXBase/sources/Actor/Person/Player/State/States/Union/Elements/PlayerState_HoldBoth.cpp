#include "PlayerState_HoldBoth.h"

PlayerState_HoldBoth::PlayerState_HoldBoth() {}

void PlayerState_HoldBoth::unique_init() {

}

void PlayerState_HoldBoth::update(float deltaTime) {

	InputMgr::GetInstance().isConnectGamePad() ? pad_update() : key_update();
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
