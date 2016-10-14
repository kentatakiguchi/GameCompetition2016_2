#include "PlayerState_Damage.h"

#include "../Player_EnumState.h"

PlayerState_Damage::PlayerState_Damage(){
}

void PlayerState_Damage::unique_init(Actor & actor){
	actor.setMotion(6);
}

void PlayerState_Damage::update(Actor & actor, float deltaTime){
	if (actor.getAnim().isAnimEnd()) {
		change((unsigned int)Player_EnumState::IDLE);
	}
}

void PlayerState_Damage::end(){
}
