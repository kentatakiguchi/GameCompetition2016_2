#pragma once

#include "../PlayerState.h"

class State_Dammy : public PlayerState {
public:
	State_Dammy(){}

	// IState ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void unique_init(Actor & actor) override{}
	virtual void update(Actor & actor, float deltaTime) override{}
	virtual void change(StateElement element) override{}
	virtual bool isEnd() override { return false; }
	virtual StateElement next() const override { return StateElement(0); }
	virtual void end() override{}
};