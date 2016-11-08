#include "PlayerState_Single_Jump.h"

PlayerState_Single_Jump::PlayerState_Single_Jump(){}

void PlayerState_Single_Jump::unique_init(Actor & actor){
	player_body_->reset_velocity();
	player_body_->reset_opponent();

	dump_ = 0;
	dir_ = Vector2(0, -1);
	power_ = PLAYER_JUMP_POWER;
	dir_easeing_ = 0;
	gra_easeing_ = 0;
	player_body_->launch(dir_ * power_);
}

void PlayerState_Single_Jump::update(Actor & actor, float deltaTime){
	timer_ += deltaTime;

	//dir_easeing_ = EasingOutExpo(timer_);
	//gra_easeing_ = EasingInExpo(timer_);

	//dir_ *= -dir_easeing_ + 1;

	dir_.y += 0.1f/* * gra_easeing_*/;

	player_body_->launch(dir_ * power_);

	if (player_body_->hitOpponent() == PlayerBody::Opponent::FLOOR) {
		change((unsigned int)PlayerState_Enum_Single::IDLE);
	}
}

void PlayerState_Single_Jump::end()
{
}

void PlayerState_Single_Jump::move(Actor & actor, float deltaTime)
{
}
