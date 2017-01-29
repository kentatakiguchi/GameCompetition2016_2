#include "PlayerState_LeanBack.h"

PlayerState_LeanBack::PlayerState_LeanBack(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

void PlayerState_LeanBack::unique_init(){
	dir_ = Vector2(-1, -1);
	power_ = PLAYER_LEANBACK_POWER;

	butty_->reset_opponent();
	retty_->reset_opponent();
}

void PlayerState_LeanBack::update(float deltaTime){
	dir_.y += 0.1f;

	butty_->position() += dir_ * power_ * deltaTime * static_cast<float>(GetRefreshRate());
	retty_->position() += dir_ * power_ * deltaTime * static_cast<float>(GetRefreshRate());

	if (butty_->is_hit() && retty_->is_hit()) {
		change(PlayerState_Enum_Union::IDLE);
	}
}

void PlayerState_LeanBack::end(){
	butty_->reset_enemy();
	retty_->reset_enemy();
}

void PlayerState_LeanBack::key_input(float deltaTime){}

void PlayerState_LeanBack::pad_input(float deltaTime){}
