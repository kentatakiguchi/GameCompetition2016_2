#include "PlayerState_StandBy.h"

PlayerState_StandBy::PlayerState_StandBy(){}

void PlayerState_StandBy::unique_init(Actor & actor){}

void PlayerState_StandBy::update(Actor & actor, float deltaTime){
	main_body_->gravity();
	sub_body_->gravity();

	change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
}

void PlayerState_StandBy::end(){

}
