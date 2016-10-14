#pragma once

#include "../Base/PlayerState.h"

#include "../../PlayerBody.h"

class PlayerState_MoveL : public PlayerState {
public:
	PlayerState_MoveL();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
private:
	void move(Actor & actor, float deltaTime);
};