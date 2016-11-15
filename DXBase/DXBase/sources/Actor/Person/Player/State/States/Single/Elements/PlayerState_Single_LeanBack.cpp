#include "PlayerState_Single_LeanBack.h"

PlayerState_Single_LeanBack::PlayerState_Single_LeanBack(){
}

void PlayerState_Single_LeanBack::unique_init(Actor & actor){
	player_body_->reset_opponent();

	dir_ = Vector2(player_body_->get_partner_vector().x, 1) * -1;
	power_ = PLAYER_LEANBACK_POWER;
	player_body_->launch(dir_ * power_);
}

void PlayerState_Single_LeanBack::update(Actor & actor, float deltaTime){

	dir_.y += 0.2f;

	player_body_->launch(dir_ * power_);

	if (player_body_->is_hit()) {
		change(StateElement((unsigned int)PlayerState_Enum_Single::IDLE));
	}
}

void PlayerState_Single_LeanBack::end(){
}

void PlayerState_Single_LeanBack::move(){

}
