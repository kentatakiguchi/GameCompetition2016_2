#include "PlayerState_Single_StandBy.h"

PlayerState_Single_StandBy::PlayerState_Single_StandBy(const Keys& keys) : PlayerState_Single(keys) {}

void PlayerState_Single_StandBy::unique_init() {
	//butty_->init_state();
	body_->reset_enemy();
	body_->reset_dead_limit();
	body_->reset_partner();
}

void PlayerState_Single_StandBy::update(float deltaTime){
	change(StateElement((unsigned int)PlayerState_Enum_Single::LEAN_BACK));
}

void PlayerState_Single_StandBy::end(){}
