#include "PlayerState_Single_StandBy.h"

PlayerState_Single_StandBy::PlayerState_Single_StandBy() {}

void PlayerState_Single_StandBy::unique_init(){}

void PlayerState_Single_StandBy::update(float deltaTime){
	change(StateElement((unsigned int)PlayerState_Enum_Single::LEAN_BACK));
}

void PlayerState_Single_StandBy::end(){}
