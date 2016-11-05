#pragma once

#include "../PlayerState_Single.h"

class PlayerState_Single_StandBy : public PlayerState_Single {
public:
	PlayerState_Single_StandBy();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
};

