#include "PlayerState_Hold.h"
#include "../Player_EnumState.h"

const float MAX_STRETCH_LENGTH = 150.0f;

PlayerState_Hold::PlayerState_Hold(){}

void PlayerState_Hold::unique_init(Actor & actor){

	if (element_.action_type_ == ActionType::None) {
		main_body_ = player_->getMainBody();
		sub_body_ = player_->getSubBody();
	}
	else if (element_.action_type_ == ActionType::Right) {
		main_body_ = compareMax(player_->getMainBody(), player_->getSubBody());
		sub_body_ = compareMin(player_->getMainBody(), player_->getSubBody());
	}
	else if (element_.action_type_ == ActionType::Left) {
		main_body_ = compareMin(player_->getMainBody(), player_->getSubBody());
		sub_body_ = compareMax(player_->getMainBody(), player_->getSubBody());
	}

	player_->setBody(main_body_, sub_body_);
}

void PlayerState_Hold::update(Actor & actor, float deltaTime) {
	move();

	if (sub_body_->distance() >= MAX_STRETCH_LENGTH) {

	}

	if (InputMgr::GetInstance().IsKeyUp(KeyCode::R_SHIFT) && element_.action_type_ == ActionType::Right) {
		if (sub_body_->distance() >= MAX_STRETCH_LENGTH) {
			change((unsigned int)Player_EnumState::ATTACK);
		}
		else {
			change((unsigned int)Player_EnumState::IDLE);
		}
	}
	if (InputMgr::GetInstance().IsKeyUp(KeyCode::L_SHIFT) && element_.action_type_ == ActionType::Left) {
		if (sub_body_->distance() >= MAX_STRETCH_LENGTH) {
			change((unsigned int)Player_EnumState::ATTACK);
		}
		else {
			change((unsigned int)Player_EnumState::IDLE);
		}
	}
}

void PlayerState_Hold::end(){

}

bool PlayerState_Hold::isReady(){

	return false;
}

void PlayerState_Hold::move(){
	sub_body_->move();
	sub_body_->circleClamp();
}
