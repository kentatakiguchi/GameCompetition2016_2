#include "PlayerState_Single_StandBy.h"

PlayerState_Single_StandBy::PlayerState_Single_StandBy(){}

void PlayerState_Single_StandBy::unique_init(Actor & actor){}

void PlayerState_Single_StandBy::update(Actor & actor, float deltaTime){
	change(StateElement((unsigned int)PlayerState_Enum_Single::IDLE));
}

void PlayerState_Single_StandBy::end(){
}