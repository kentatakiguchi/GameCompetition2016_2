#include "PlayerState_Idle.h"

#include <algorithm>

PlayerState_Idle::PlayerState_Idle() {}

void PlayerState_Idle::unique_init(){}

void PlayerState_Idle::update(float deltaTime) {
	player_->body_chase();
	//player_->body_clamp();
	player_->body_gravity();
}

void PlayerState_Idle::end(){}

void PlayerState_Idle::key_input(){
	if (InputMgr::GetInstance().KeyVector_R().Length() > 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE, ActionType::Right));
	}
	if (InputMgr::GetInstance().KeyVector_L().Length() > 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE, ActionType::Left));
	}

	if (InputMgr::GetInstance().KeyVector_R().y <= Vector2::Down.y &&
		InputMgr::GetInstance().KeyVector_L().y <= Vector2::Down.y) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::JUMP));
	}

	if (holdable_keyR()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (holdable_keyL()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

void PlayerState_Idle::pad_input(){
	if (InputMgr::GetInstance().AnalogPadVectorR().Length() > 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE, ActionType::Right));
	}
	if (InputMgr::GetInstance().AnalogPadVectorL().Length() > 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE, ActionType::Left));
	}

	if (InputMgr::GetInstance().AnalogPadVectorR().y <= Vector2::Down.y &&
		InputMgr::GetInstance().AnalogPadVectorL().y <= Vector2::Down.y) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::JUMP));
	}

	if (holdable_padR()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (holdable_padL()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

