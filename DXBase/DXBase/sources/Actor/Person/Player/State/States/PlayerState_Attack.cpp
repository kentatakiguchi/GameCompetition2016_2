#include "PlayerState_Attack.h"
#include "../Player_EnumState.h"

#include "../../Player_AttackRange.h"

PlayerState_Attack::PlayerState_Attack() {}

void PlayerState_Attack::unique_init(Actor & actor){
	main_body_ = player_->getMainBody();
	sub_body_ = player_->getSubBody();

	dir_ = Vector3::Normalize(sub_body_->getPosition() - main_body_->getPosition());
	power_ = 20;
	main_body_->launch(dir_ * power_);
	sub_body_->launch(dir_ * power_);
}

void PlayerState_Attack::update(Actor & actor, float deltaTime) {
	dir_ += Vector3(0, 1, 0) * 0.02f;
	main_body_->launch(dir_ * power_);
	sub_body_->launch(dir_ * power_);
	main_body_->gravity();
	sub_body_->gravity();

	if (std::abs(dir_.y) <= 0) {
		change((unsigned int)Player_EnumState::IDLE);
	}
}

void PlayerState_Attack::end(){

}



