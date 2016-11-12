#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Split : public PlayerState_Union {
public:
	PlayerState_Split();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
private:
	float time_;
};