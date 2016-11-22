#include "PlayerState_Single_StandBy.h"

PlayerState_Single_StandBy::PlayerState_Single_StandBy(const PlayerBodyPtr& player_body) : PlayerState_Single(player_body) {}

void PlayerState_Single_StandBy::unique_init(){}

void PlayerState_Single_StandBy::update(float deltaTime){
	change(StateElement((unsigned int)PlayerState_Enum_Single::LEAN_BACK));
}

void PlayerState_Single_StandBy::end(){
}
