#include "PlayerState_Single_Jump.h"

PlayerState_Single_Jump::PlayerState_Single_Jump(){}

void PlayerState_Single_Jump::unique_init(Actor & actor){
	player_body_->reset_velocity();
	player_body_->reset_opponent();

	dump_ = 0;
	dir_ = Vector2::Down;
	power_ = PLAYER_JUMP_POWER;
	dir_easeing_ = 0;
	gra_easeing_ = 0;
	player_body_->launch(dir_ * power_);
}

void PlayerState_Single_Jump::update(Actor & actor, float deltaTime){
	timer_ += deltaTime;

	//gra_easeing_ = EasingInExpo(timer_);

	dir_.y += 0.1f/* * gra_easeing_*/;

	player_body_->launch(dir_ * power_);

	Vector2 vector = InputMgr::GetInstance().KeyVector(player_body_->get_keys().right, player_body_->get_keys().left);
	player_body_->move(vector.Horizontal());

	if (player_body_->isOnFloor()) change((unsigned int)PlayerState_Enum_Single::IDLE);
}

void PlayerState_Single_Jump::end(){}

void PlayerState_Single_Jump::move(Actor & actor, float deltaTime){}
