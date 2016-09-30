#pragma once

#include "../Base/IState.h"

class State_Dammy : public IState {
public:
	State_Dammy(){}

	// IState ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void init(Actor & actor) override{}
	virtual void update(Actor & actor, float deltaTime) override{}
	virtual void change(unsigned int nextState) override{}
	virtual bool isEnd() override { return false; }
	virtual unsigned int next() const override { return 0; }
	virtual void end() override{}
};