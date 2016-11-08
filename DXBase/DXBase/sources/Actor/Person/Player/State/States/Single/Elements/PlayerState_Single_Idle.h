#pragma once

#include "../PlayerState_Single.h"

class PlayerState_Single_Idle : public PlayerState_Single {
public:
	PlayerState_Single_Idle();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
private:
	void move(Actor & actor, float deltaTime);
private:
	Vector2 dir_;
	float dump_;
	float power_;

	float gra_easeing_;
};

