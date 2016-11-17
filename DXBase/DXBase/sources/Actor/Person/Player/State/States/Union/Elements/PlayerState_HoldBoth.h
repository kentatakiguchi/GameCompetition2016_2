#pragma once

#include "../PlayerState_Union.h"

class PlayerState_HoldBoth : public PlayerState_Union {
public:
	PlayerState_HoldBoth();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
private:
	void key_update();
	void pad_update();
};