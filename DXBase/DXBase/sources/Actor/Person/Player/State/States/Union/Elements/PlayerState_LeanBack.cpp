#include "PlayerState_LeanBack.h"

PlayerState_LeanBack::PlayerState_LeanBack(){}

void PlayerState_LeanBack::unique_init(){
	dir_ = Vector2(-1, 1);
	power_ = PLAYER_LEANBACK_POWER;
}

void PlayerState_LeanBack::update(float deltaTime){
	dir_.y += 0.1f;

	butty_->launch(dir_ * power_);
	retty_->launch(dir_ * power_);

	if (butty_->able_to_hold() && retty_->able_to_hold()) {
		change(PlayerState_Enum_Union::IDLE);
	}
}

void PlayerState_LeanBack::end(){
	butty_->reset_enemy();
	retty_->reset_enemy();
}

void PlayerState_LeanBack::key_input()
{
}

void PlayerState_LeanBack::pad_input()
{
}