#include "PlayerState_Damage.h"

#include "../Player_EnumState.h"

PlayerState_Damage::PlayerState_Damage(){
}

void PlayerState_Damage::init(Actor & actor){
	isEndRequest = false;
	actor.setMotion(6);
}

void PlayerState_Damage::update(Actor & actor, float deltaTime){
	if (actor.getAnim().isAnimEnd()) {
		change((unsigned int)Player_EnumState::IDLE);
	}
}

void PlayerState_Damage::change(unsigned int nextState){
	nextState_ = nextState;
	isEndRequest = true;
}

bool PlayerState_Damage::isEnd(){
	return isEndRequest;
}

unsigned int PlayerState_Damage::next() const{
	return (unsigned int)nextState_;
}

void PlayerState_Damage::end()
{
}
