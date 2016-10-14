#include "PlayerState_Jump.h"
#include "../Player_EnumState.h"

PlayerState_Jump::PlayerState_Jump() {}

void PlayerState_Jump::unique_init(Actor & actor){
	actor.setMotion(4);
}

void PlayerState_Jump::update(Actor & actor, float deltaTime){

	if (actor.getAnim().isAnimEnd()) {
		change((unsigned int)Player_EnumState::IDLE);
	}
}

void PlayerState_Jump::end(){

}



