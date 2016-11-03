#pragma once

#include "../PlayerState.h"

#include "../../PlayerBody.h"

class PlayerState_HoldBoth : public PlayerState {
public:
	PlayerState_HoldBoth();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
};