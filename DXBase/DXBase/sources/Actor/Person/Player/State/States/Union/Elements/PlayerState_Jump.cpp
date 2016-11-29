#include "PlayerState_Jump.h"

PlayerState_Jump::PlayerState_Jump()
{
}

void PlayerState_Jump::unique_init(){
	butty_->reset_velocity();
	retty_->reset_velocity();

	butty_->reset_opponent();
	retty_->reset_opponent();

	dir_ = Vector2::Down;
	power_ = PLAYER_JUMP_POWER;
	gra_easeing_ = 0;
	butty_->launch(dir_ * power_);
	retty_->launch(dir_ * power_);
}

void PlayerState_Jump::update(float deltaTime){
	//InputMgr::GetInstance().isConnectGamePad() ? pad_update() : key_update();

	timer_ += deltaTime;

	//gra_easeing_ = EasingInExpo(timer_);
	dir_.y += 0.1f/* * gra_easeing_*/;

	butty_->launch(dir_ * power_);
	retty_->launch(dir_ * power_);

	if (butty_->able_to_jump() || retty_->able_to_jump()) change((unsigned int)PlayerState_Enum_Union::IDLE);
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

