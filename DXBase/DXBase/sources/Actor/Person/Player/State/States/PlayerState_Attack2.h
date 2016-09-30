#pragma once

#include "../Base/IState.h"

class PlayerState_Attack2 : public IState {
public:
	PlayerState_Attack2();
	//PlayerState_Attack(StateMgr& stateMgr, Actor* actor);

	// IState ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void change(unsigned int nextState) override;

	virtual bool isEnd() override;

	virtual unsigned int next() const override;

	virtual void end() override;
private:
	unsigned int nextState_;
	bool isEndRequest;
};