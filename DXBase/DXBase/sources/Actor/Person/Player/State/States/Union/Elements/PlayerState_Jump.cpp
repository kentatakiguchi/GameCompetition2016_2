#include "PlayerState_Jump.h"

#include "../../../../../../../Define.h"
#include "../../../../../../../Input/InputMgr.h"

#include <algorithm>

PlayerState_Jump::PlayerState_Jump(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

void PlayerState_Jump::unique_init(){
	butty_->reset_opponent();
	retty_->reset_opponent();

	dir_ = Vector2::Down;
	power_ = PLAYER_JUMP_POWER;
	gra_easeing_ = 0;
}

void PlayerState_Jump::update(float deltaTime) {
	timer_ = std::min<float>(timer_ + deltaTime, 60);

	//gra_easeing_ = EasingInExpo(timer_);
	dir_.y = std::min<float>(dir_.y + 0.1f, 1)/* * gra_easeing_*/;

	butty_->position() += dir_ * power_ * deltaTime * static_cast<float>(GetRefreshRate());
	retty_->position() += dir_ * power_ * deltaTime * static_cast<float>(GetRefreshRate());

	if (butty_->able_to_jump() || retty_->able_to_jump()) {
		change(PlayerState_Enum_Union::IDLE);
	}

	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);
}

void PlayerState_Jump::end(){
	butty_->reset_slope();
	retty_->reset_slope();
}

void PlayerState_Jump::key_input(float deltaTime){
	butty_->position() += InputMgr::GetInstance().KeyVector_R().Horizontal() / 2 * speed_b(deltaTime);
	retty_->position() += InputMgr::GetInstance().KeyVector_L().Horizontal() / 2 * speed_r(deltaTime);
}

void PlayerState_Jump::pad_input(float deltaTime){
	butty_->position() += InputMgr::GetInstance().AnalogPadVectorR().Horizontal() / 2 * speed_b(deltaTime);
	retty_->position() += InputMgr::GetInstance().AnalogPadVectorL().Horizontal() / 2 * speed_r(deltaTime);
}

