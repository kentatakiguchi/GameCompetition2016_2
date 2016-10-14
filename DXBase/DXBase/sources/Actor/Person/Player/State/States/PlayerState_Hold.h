#pragma once

#include "../Base/PlayerState.h"

#include "../../PlayerBody.h"

class PlayerState_Hold : public PlayerState {
public:
	PlayerState_Hold();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
private:
	bool isReady();
	void move();
}; 
