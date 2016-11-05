#pragma once

#include "../PlayerState_Union.h"

class PlayerState_StandBy : public PlayerState_Union {
public:
	PlayerState_StandBy();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
};