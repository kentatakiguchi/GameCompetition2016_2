#pragma once

#include "../PlayerState.h"
#include "../Player_EnumState.h"

#include "../../PlayerBody.h"

class PlayerState_StandBy : public PlayerState {
public:
	PlayerState_StandBy();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
};