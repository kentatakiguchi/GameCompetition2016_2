#pragma once

#include "../Base/PlayerState.h"

class PlayerState_Damage : public PlayerState {
public:
	PlayerState_Damage();

	// IState ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
};