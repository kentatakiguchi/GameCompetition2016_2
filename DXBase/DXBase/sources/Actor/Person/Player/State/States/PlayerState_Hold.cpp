#include "PlayerState_Hold.h"
#include "../Player_EnumState.h"

PlayerState_Hold::PlayerState_Hold(){}

void PlayerState_Hold::unique_init(Actor & actor){

	if (element_.action_type_ == ActionType::None) {
		main_body_ = player_->getMainBody();
		sub_body_ = player_->getSubBody();
	}
	else if (element_.action_type_ == ActionType::Right) {
		main_body_ = compareMax(player_->getMainBody(), player_->getSubBody());
		sub_body_ = compareMin(player_->getSubBody(), player_->getMainBody());
	}
	else if (element_.action_type_ == ActionType::Left) {
		main_body_ = compareMin(player_->getMainBody(), player_->getSubBody());
		sub_body_ = compareMax(player_->getSubBody(), player_->getMainBody());
	}

	player_->setBody(main_body_, sub_body_);

	if (main_body_->hitOpponent() != PlayerBody::Opponent::FLOOR)change((unsigned int)Player_EnumState::IDLE);
}

void PlayerState_Hold::update(Actor & actor, float deltaTime) {
	move();

	if (InputMgr::GetInstance().IsKeyUp(KeyCode::R_SHIFT) && element_.action_type_ == ActionType::Right || 
		InputMgr::GetInstance().IsKeyUp(KeyCode::L_SHIFT) && element_.action_type_ == ActionType::Left) {
		if (sub_body_->distance() >= MAX_STRETCH_LENGTH - 5)change((unsigned int)Player_EnumState::ATTACK);
		else change((unsigned int)Player_EnumState::IDLE);
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && element_.action_type_ == ActionType::Left ||
		InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && element_.action_type_ == ActionType::Right) {
		if(sub_body_->hitOpponent() == PlayerBody::Opponent::FLOOR)	change((unsigned int)Player_EnumState::HOLD_BOTH);
	}
}

void PlayerState_Hold::end(){

}

void PlayerState_Hold::move(){
	sub_body_->move();
	sub_body_->hold_gravity();
	sub_body_->circleClamp();
}
