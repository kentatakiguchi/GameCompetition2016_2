#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Move : public PlayerState_Union {
public:
	PlayerState_Move();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
private:
	void move(Actor & actor, float deltaTime);
private:
	void key_update();
	void pad_update();

};