#include "StateMgr.h"

StateMgr::StateMgr() {}

void StateMgr::action(Actor & actor, float deltaTime) {
	currentState_->update(actor, deltaTime);
	if (currentState_->isEnd()) changeState(actor, currentState_->next());
}

void StateMgr::changeState(Actor & actor, IState::StateElement element) {
	currentStateName_ = element.state_;
	currentState_ = states_[currentStateName_];
	currentState_->common_init(actor, element.action_type_);
	currentState_->unique_init(actor);
}

void StateMgr::add(unsigned int state, const IStatePtr& scene) {
	states_[(unsigned int)state] = scene;
}

unsigned int StateMgr::currentState()
{
	return currentStateName_;
}

