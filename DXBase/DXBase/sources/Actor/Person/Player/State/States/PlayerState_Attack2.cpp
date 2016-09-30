#include "PlayerState_Attack2.h"
#include "../Player_EnumState.h"

#include "../../Player_AttackRange.h"

PlayerState_Attack2::PlayerState_Attack2() {}

void PlayerState_Attack2::init(Actor & actor) {
	isEndRequest = false;
	actor.getWorld()->addActor(ActorGroup::Player_AttackRange, std::make_shared<Player_AttackRange>(actor.getWorld(), actor.getPosition()));
	actor.setMotion(1);
}

void PlayerState_Attack2::update(Actor & actor, float deltaTime) {
	if (actor.getAnim().isAnimEnd()) {
		change((unsigned int)Player_EnumState::IDLE);
	}
}

void PlayerState_Attack2::change(unsigned int nextState) {
	nextState_ = nextState;
	isEndRequest = true;
}

bool PlayerState_Attack2::isEnd() {
	return isEndRequest;
}

unsigned int PlayerState_Attack2::next() const {
	return (unsigned int)nextState_;
}

void PlayerState_Attack2::end() {

}



