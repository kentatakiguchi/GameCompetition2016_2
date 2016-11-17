#pragma once

#include "../PlayerState_Single.h"

class PlayerState_Single_LeanBack : public PlayerState_Single {
public:
	PlayerState_Single_LeanBack();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
private:
	void move();
private:
	Vector2 dir_;
	float power_;
};