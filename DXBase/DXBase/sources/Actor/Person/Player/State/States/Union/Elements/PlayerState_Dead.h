#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Dead : public PlayerState_Union {
public:
	PlayerState_Dead();

	virtual void unique_init() override;

	virtual void update(float deltaTime) override;

	virtual void end() override;
};