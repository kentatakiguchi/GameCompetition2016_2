#include "PlayerState_Attack.h"

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

	dir_easeing_ = EasingOutExpo(timer_ * 0.2f);
	gra_easeing_ = EasingInExpo(timer_ * 0.2f);

	dir_ *= -dir_easeing_ + 1;

	dir_.y += 0.1f * gra_easeing_;
	
	main_body_->launch(dir_ * power_);

	sub_body_->chase();

	main_body_->gravity();
	sub_body_->gravity();

	if (main_body_->isOnFloor() ||	sub_body_->isOnFloor()) {
		power_ = 0;
	}

	if (main_body_->isOnFloor() &&	sub_body_->isOnFloor()) {
		change((unsigned int)PlayerState_Enum_Union::IDLE);
	}
}

void PlayerState_Attack::end(){

}





