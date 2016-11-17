#include "PlayerState_Split.h"

PlayerState_Split::PlayerState_Split()
{
}

void PlayerState_Split::unique_init(Actor & actor){
	main_body_->reset_dead_limit();
	sub_body_->reset_dead_limit();
}

void PlayerState_Split::update(Actor & actor, float deltaTime){
	time_ += deltaTime;

	main_body_->single_action(deltaTime);
	sub_body_->single_action(deltaTime);

	main_body_->count_dead_limit(deltaTime);
	sub_body_->count_dead_limit(deltaTime);

	if (main_body_->isDead() && sub_body_->isDead())change(StateElement((unsigned int)PlayerState_Enum_Union::DEAD));
}

void PlayerState_Split::end(){
}

