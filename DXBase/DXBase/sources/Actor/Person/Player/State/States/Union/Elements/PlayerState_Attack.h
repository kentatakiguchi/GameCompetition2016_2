#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Attack : public PlayerState_Union {
public:
	PlayerState_Attack();

	virtual void unique_init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void end() override;
private:
	int compare_V();
	int compare_H();
private:
	Vector2 dir_;
	float dump_;
	float power_;

	float dir_easeing_;
	float gra_easeing_;

};