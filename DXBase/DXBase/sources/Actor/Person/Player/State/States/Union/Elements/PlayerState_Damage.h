#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Damage : public PlayerState_Union {
public:
	PlayerState_Damage();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
};