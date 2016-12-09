#include "PlayerState_StandBy.h"

PlayerState_StandBy::PlayerState_StandBy() {}

void PlayerState_StandBy::unique_init(){}

void PlayerState_StandBy::update(float deltaTime){
	butty_->gravity();
	retty_->gravity();

	change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
}

void PlayerState_StandBy::end(){}
