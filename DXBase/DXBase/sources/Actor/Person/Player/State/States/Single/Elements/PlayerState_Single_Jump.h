#pragma once

#include "../PlayerState_Single.h"

class PlayerState_Single_Jump : public PlayerState_Single {
public:
	PlayerState_Single_Jump();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
private:
	void move(Actor & actor, float deltaTime);
private:
	Vector2 dir_;
	float dump_;
	float power_;

	float dir_easeing_;
	float gra_easeing_;
};