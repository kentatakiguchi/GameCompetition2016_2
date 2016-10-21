#pragma once

#include "../PlayerState.h"

class PlayerState_Attack2 : public PlayerState {
public:
	PlayerState_Attack2();

	// IState ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
};