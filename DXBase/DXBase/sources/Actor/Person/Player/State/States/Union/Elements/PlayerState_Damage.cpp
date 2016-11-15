#include "PlayerState_Damage.h"

PlayerState_Damage::PlayerState_Damage(){
}

void PlayerState_Damage::unique_init(Actor & actor){
	actor.setMotion(6);
}

void PlayerState_Damage::update(Actor & actor, float deltaTime){
	if (actor.getAnim().isAnimEnd()) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
	}
}

void PlayerState_Damage::end(){
}
