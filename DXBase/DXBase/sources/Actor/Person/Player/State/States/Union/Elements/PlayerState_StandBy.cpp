#include "PlayerState_StandBy.h"

PlayerState_StandBy::PlayerState_StandBy(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : PlayerState_Union(butty, retty) {}

void PlayerState_StandBy::unique_init(){
	butty_->change_state(PlayerState_Enum_Single::STAND_BY);
	retty_->change_state(PlayerState_Enum_Single::STAND_BY);

	change(PlayerState_Enum_Union::IDLE);
}

void PlayerState_StandBy::update(float deltaTime){}

void PlayerState_StandBy::end(){}
