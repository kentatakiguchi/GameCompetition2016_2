#include "PlayerState_Freeze.h"

PlayerState_Freeze::PlayerState_Freeze(){}

void PlayerState_Freeze::unique_init(){
	butty_->animation().change(PlayerAnimID::IDLE);
	retty_->animation().change(PlayerAnimID::IDLE);

	timer_ = 0;

	PlaySound("./resources/sounds/syoutotu.mp3", DX_PLAYTYPE_BACK);
}

void PlayerState_Freeze::update(float deltaTime){
	timer_ += deltaTime;

	//butty_->clamp();
	//retty_->clamp();

	if (timer_ >= PLAYER_FREEZE_TIME) change(PlayerState_Enum_Union::IDLE);
}

void PlayerState_Freeze::end(){}

void PlayerState_Freeze::key_input(){
	if (move_keyR()) change(PlayerState_Enum_Union::MOVE, ActionType::Right);
	if (move_keyL()) change(PlayerState_Enum_Union::MOVE, ActionType::Left);

	if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

void PlayerState_Freeze::pad_input(){
	if (move_padR()) change(PlayerState_Enum_Union::MOVE, ActionType::Right);
	if (move_padL()) change(PlayerState_Enum_Union::MOVE, ActionType::Left);

	if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

