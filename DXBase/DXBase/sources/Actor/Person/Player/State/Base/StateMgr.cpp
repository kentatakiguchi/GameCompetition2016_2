#include "StateMgr.h"

StateMgr::StateMgr() {}

void StateMgr::action(Actor & actor, float deltaTime) {
	currentState_->update(actor, deltaTime);
	if (currentState_->isEnd()) changeState(actor, currentState_->next());
}

void StateMgr::changeState(Actor & actor, unsigned int nextState) {
	currentStateName_ = nextState;
	currentState_ = states_[currentStateName_];
	currentState_->init(actor);
}

void StateMgr::add(unsigned int state, const IStatePtr& scene) {
	states_[(unsigned int)state] = scene;
}

unsigned int StateMgr::currentState()
{
	return currentStateName_;
}

