#include "PlayerState_Jump.h"
#include "../Player_EnumState.h"

PlayerState_Jump::PlayerState_Jump(){}

void PlayerState_Jump::init(Actor & actor){
	isEndRequest = false;
	actor.setMotion(4);
}

void PlayerState_Jump::update(Actor & actor, float deltaTime){

	if (actor.getAnim().isAnimEnd()) {
		change((unsigned int)Player_EnumState::IDLE);
	}
}

void PlayerState_Jump::change(unsigned int nextState) {
	nextState_ = nextState;
	isEndRequest = true;
}

bool PlayerState_Jump::isEnd(){
	return isEndRequest;
}

unsigned int PlayerState_Jump::next() const{
	return (unsigned int)nextState_;
}

void PlayerState_Jump::end(){

}



