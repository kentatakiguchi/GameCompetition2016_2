#include "PlayerState_Idle.h"

#include <algorithm>

PlayerState_Idle::PlayerState_Idle(const PlayerPtr& player) : PlayerState_Union(player) {}

void PlayerState_Idle::unique_init(){
}

void PlayerState_Idle::update(float deltaTime) {
	InputMgr::GetInstance().isConnectGamePad() ? pad_update() : key_update();

	player_->body_chase();
	player_->body_clamp();
	player_->body_gravity();
}

void PlayerState_Idle::end(){}

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

	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}
