#pragma once

#include "../Base/PlayerState.h"
#include "../Player_EnumState.h"

#include "../../PlayerBody.h"

class PlayerState_Idle : public PlayerState {
public:
	PlayerState_Idle();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
};