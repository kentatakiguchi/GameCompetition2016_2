#include "PlayerState_Single_Jump.h"

#include <algorithm>

PlayerState_Single_Jump::PlayerState_Single_Jump(const Keys& keys) : PlayerState_Single(keys) {}

void PlayerState_Single_Jump::unique_init(){
	body_->reset_opponent();

	dir_ = Vector2::Down;
	power_ = PLAYER_JUMP_POWER;
	gra_easeing_ = 0;
	body_->launch(dir_ * power_);
}

void PlayerState_Single_Jump::update(float deltaTime){
	body_->count_dead_limit(deltaTime);

	//timer_ += deltaTime;

	//gra_easeing_ = EasingInExpo(timer_);
	dir_.y = std::min<float>(dir_.y + 0.1f, 1)/* * gra_easeing_*/;

	body_->launch(dir_ * power_);

	if (body_->able_to_jump()) change((unsigned int)PlayerState_Enum_Single::IDLE);
}

void PlayerState_Single_Jump::end(){}

void PlayerState_Single_Jump::key_input(){
	body_->move(InputMgr::GetInstance().KeyVector(keys_.right, keys_.left, keys_.up, keys_.down).Horizontal());
}

void PlayerState_Single_Jump::pad_input(){
	Vector2 vector = Vector2::Zero;
	if (is_butty())vector = InputMgr::GetInstance().AnalogPadVectorR();
	if (is_retty())vector = InputMgr::GetInstance().AnalogPadVectorL();
	body_->move(vector.Horizontal());
}

void PlayerState_Single_Jump::move() {}

