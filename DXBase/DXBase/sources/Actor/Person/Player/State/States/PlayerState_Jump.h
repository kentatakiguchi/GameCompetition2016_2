#pragma once

#include "../PlayerState.h"

class PlayerState_Jump : public PlayerState {
public:
	PlayerState_Jump();

	// IState ����Čp������܂���
	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
};