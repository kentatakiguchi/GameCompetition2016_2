#pragma once

#include "../PlayerState.h"

class PlayerState_Damage : public PlayerState {
public:
	PlayerState_Damage();

	// IState を介して継承されました
	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
};