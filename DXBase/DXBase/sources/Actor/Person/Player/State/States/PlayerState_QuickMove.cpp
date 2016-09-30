#include "PlayerState_QuickMove.h"
#include "../Player_EnumState.h"

#include "../../Player_AttackRange.h"

PlayerState_QuickMove::PlayerState_QuickMove() {}

void PlayerState_QuickMove::init(Actor & actor) {
	isEndRequest = false;
	actor.setMotion(2);
}

void PlayerState_QuickMove::update(Actor & actor, float deltaTime) {
	if (actor.getAnim().isAnimEnd()) {
		change((unsigned int)Player_EnumState::IDLE);
	}
}

void PlayerState_QuickMove::change(unsigned int nextState) {
	nextState_ = nextState;
	isEndRequest = true;
}

bool PlayerState_QuickMove::isEnd() {
	return isEndRequest;
}

unsigned int PlayerState_QuickMove::next() const {
	return (unsigned int)nextState_;
}

void PlayerState_QuickMove::end() {

}
