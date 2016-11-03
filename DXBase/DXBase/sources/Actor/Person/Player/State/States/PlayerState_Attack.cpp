#include "PlayerState_Attack.h"
#include "../Player_EnumState.h"

#include <algorithm>

PlayerState_Attack::PlayerState_Attack() {}

void PlayerState_Attack::unique_init(Actor & actor){
	main_body_ = player_->getMainBody();
	sub_body_ = player_->getSubBody();

	main_body_->reset_velocity();
	sub_body_->reset_velocity();

	main_body_->reset_opponent();
	sub_body_->reset_opponent();

	dump_ = 0;
	dir_ = Vector2::Normalize(sub_body_->getPosition() - main_body_->getPosition());
	power_ = PLAYER_LAUNCH_POWER;
	dir_easeing_ = 0;
	gra_easeing_ = 0;
	main_body_->launch(dir_ * power_);
}

void PlayerState_Attack::update(Actor & actor, float deltaTime) {
	timer_ += deltaTime;
	//timer_ = std::min<float>(timer_ + deltaTime, 60);

	dir_easeing_ = gsEasingOutExpo(timer_ * 0.5f);
	gra_easeing_ = gsEasingInExpo(timer_ * 0.5f);

	dir_ *= -dir_easeing_ + 1;

	dir_.y += 0.001f * gra_easeing_;
	
	main_body_->launch(dir_ * power_);

	sub_body_->chase();

	main_body_->gravity();
	sub_body_->gravity();

	if (main_body_->hitOpponent() == PlayerBody::Opponent::FLOOR ||
		sub_body_->hitOpponent() == PlayerBody::Opponent::FLOOR) {
		power_ = 0;
	}

	if (main_body_->hitOpponent() == PlayerBody::Opponent::FLOOR &&
		sub_body_->hitOpponent() == PlayerBody::Opponent::FLOOR) {
		change((unsigned int)Player_EnumState::IDLE);
	}
}

void PlayerState_Attack::end(){

}

float PlayerState_Attack::gsEasingInExpo(float t){
	return (t == 0) ? 0.0f : std::pow(2.0f, 10.0f * (t - 1.0f));
}

float PlayerState_Attack::gsEasingOutExpo(float t){
	return (t == 1.0f) ? 1.0f : (-std::pow(2.0f, -10.0f * t) + 1.0f);
}




