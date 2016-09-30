#pragma once

#include "IStatePtr.h"
#include "IState.h"
#include "../../../../Base/Actor.h"
#include <unordered_map>

class StateMgr{
public:
	StateMgr();
public:
	void action(Actor & actor, float deltaTime) ;
	void changeState(Actor & actor, unsigned int nextState);
	// シーンの追加
	void add(unsigned int state, const IStatePtr& scene);
	unsigned int currentState();
private:
	// コピー禁止
	StateMgr(const StateMgr& other) = delete;
	StateMgr& operator = (const StateMgr& other) = delete;
protected:
	std::unordered_map<unsigned int, IStatePtr> states_;
	IStatePtr currentState_;
	unsigned int currentStateName_;
	Actor actor_;
};