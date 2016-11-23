#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Damage : public PlayerState_Union {
public:
	PlayerState_Damage();

	virtual void unique_init() override;

	virtual void update(float deltaTime) override;

	virtual void end() override;
};