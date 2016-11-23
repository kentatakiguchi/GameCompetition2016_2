#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Idle : public PlayerState_Union {
public:
	PlayerState_Idle();

	virtual void unique_init() override;

	virtual void update(float deltaTime) override;

	virtual void end() override;
private:
	void key_update();
	void pad_update();
};