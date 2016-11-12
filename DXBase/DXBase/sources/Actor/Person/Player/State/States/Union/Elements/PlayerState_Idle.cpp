#include "PlayerState_Idle.h"

#include <algorithm>

PlayerState_Idle::PlayerState_Idle(){
}

void PlayerState_Idle::unique_init(Actor & actor){
	main_body_->init_state();
	sub_body_->init_state();
}

void PlayerState_Idle::update(Actor & actor, float deltaTime) {
	key_update();
	//pad_update();

	main_body_->gravity();
	sub_body_->gravity();
	main_body_->chase();
	sub_body_->chase();
	main_body_->circleClamp();
	sub_body_->circleClamp();
}

void PlayerState_Idle::end(){
}

void PlayerState_Idle::key_update(){
	if (InputMgr::GetInstance().KeyVector_L().Length() > 0 || InputMgr::GetInstance().KeyVector_R().Length() > 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE));
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

void PlayerState_Idle::pad_update(){
	if (InputMgr::GetInstance().AnalogPadVectorL().Length() > 0 || InputMgr::GetInstance().AnalogPadVectorR().Length() > 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE));
	}

	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1)) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	}
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1)) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
	}
}
