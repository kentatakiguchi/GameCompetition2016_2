#pragma once

#include "../PlayerState.h"

class PlayerState_Attack : public PlayerState {
public:
	PlayerState_Attack();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
private:
	Vector3 dir_;
	float power_;
};