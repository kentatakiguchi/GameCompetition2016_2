#include "PlayerState_Idle.h"

#include <algorithm>

PlayerState_Idle::PlayerState_Idle() {}

void PlayerState_Idle::unique_init(){
	StopSound();

	butty_->animation().change(PlayerAnimID::IDLE);
	retty_->animation().change(PlayerAnimID::IDLE);
}

void PlayerState_Idle::update(float deltaTime) {
	butty_->chase();
	retty_->chase();
	butty_->clamp();
	retty_->clamp();
	butty_->gravity();
	retty_->gravity();

	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);
}

void PlayerState_Idle::end(){}

void PlayerState_Idle::key_input(){
	if (move_keyR()) change(PlayerState_Enum_Union::MOVE, ActionType::Right);
	if (move_keyL()) change(PlayerState_Enum_Union::MOVE, ActionType::Left );

	if (jump_key()) change(PlayerState_Enum_Union::JUMP);

	if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

void PlayerState_Idle::pad_input(){
	if (move_padR()) change(PlayerState_Enum_Union::MOVE, ActionType::Right);
	if (move_padL()) change(PlayerState_Enum_Union::MOVE, ActionType::Left);

	if (jump_pad()) change(PlayerState_Enum_Union::JUMP);

	if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}


