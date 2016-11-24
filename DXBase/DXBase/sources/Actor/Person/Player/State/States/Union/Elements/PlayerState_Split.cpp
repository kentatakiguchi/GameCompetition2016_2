#include "PlayerState_Split.h"

PlayerState_Split::PlayerState_Split() {}

void PlayerState_Split::unique_init(){
	butty_->reset_dead_limit();
	retty_->reset_dead_limit();
}

void PlayerState_Split::update(float deltaTime){
	time_ += deltaTime;

	butty_->single_action(deltaTime);
	retty_->single_action(deltaTime);
		 
	butty_->count_dead_limit(deltaTime);
	retty_->count_dead_limit(deltaTime);

	if (butty_->isDead() && retty_->isDead())change(StateElement((unsigned int)PlayerState_Enum_Union::DEAD));
}

void PlayerState_Split::end(){
	butty_->init_state();
	retty_->init_state();
	retty_->reset_enemy();
	butty_->reset_enemy();

	butty_->reset_partner();
	retty_->reset_partner();
}

