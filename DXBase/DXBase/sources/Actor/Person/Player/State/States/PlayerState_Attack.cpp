#include "PlayerState_Attack.h"
#include "../Player_EnumState.h"

#include "../../Player_AttackRange.h"

PlayerState_Attack::PlayerState_Attack(){}

void PlayerState_Attack::init(Actor & actor){
	isEndRequest = false;
	actor.getWorld()->addActor(ActorGroup::Player_AttackRange, std::make_shared<Player_AttackRange>(actor.getWorld(), actor.getPosition()));
	actor.setMotion(0);
}

void PlayerState_Attack::update(Actor & actor, float deltaTime) {
	if (actor.getAnim().isAnimEnd()) {
		change((unsigned int)Player_EnumState::IDLE);
	}
}

void PlayerState_Attack::change(unsigned int nextState) {
	nextState_ = nextState;
	isEndRequest = true;
}

bool PlayerState_Attack::isEnd(){
	return isEndRequest;
}

unsigned int PlayerState_Attack::next() const{
	return (unsigned int)nextState_;
}

void PlayerState_Attack::end(){

}



