#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Attack : public PlayerState_Union {
public:
	PlayerState_Attack();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
//private:
//	float gsEasingInExpo(float t);
//	float gsEasingOutExpo(float t);

private:
	Vector2 dir_;
	float dump_;
	float power_;

	float dir_easeing_;
	float gra_easeing_;

};