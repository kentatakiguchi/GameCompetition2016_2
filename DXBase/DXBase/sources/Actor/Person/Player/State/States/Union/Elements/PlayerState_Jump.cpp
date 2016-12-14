#include "PlayerState_Jump.h"

#include <algorithm>

PlayerState_Jump::PlayerState_Jump(){}

void PlayerState_Jump::unique_init(){
	butty_->reset_opponent();
	retty_->reset_opponent();

	dir_ = Vector2::Down;
	power_ = PLAYER_JUMP_POWER;
	gra_easeing_ = 0;
	butty_->launch(dir_ * power_);
	retty_->launch(dir_ * power_);
}

void PlayerState_Jump::update(float deltaTime) {
	timer_ = std::min<float>(timer_ + deltaTime, 60);

	//gra_easeing_ = EasingInExpo(timer_);
	dir_.y = std::min<float>(dir_.y + 0.1f, 60 * 100)/* * gra_easeing_*/;

	butty_->launch(dir_ * power_);
	retty_->launch(dir_ * power_);

	if (butty_->able_to_jump() || retty_->able_to_jump()) {
		change(PlayerState_Enum_Union::IDLE);
	}
}

void PlayerState_Jump::end(){}

void PlayerState_Jump::key_input(){
	butty_->move(InputMgr::GetInstance().KeyVector_R().Horizontal() / 2);
	retty_->move(InputMgr::GetInstance().KeyVector_L().Horizontal() / 2);
}

void PlayerState_Jump::pad_input(){
	butty_->move(InputMgr::GetInstance().AnalogPadVectorR().Horizontal() / 2);
	retty_->move(InputMgr::GetInstance().AnalogPadVectorL().Horizontal() / 2);
}

