#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Jump : public PlayerState_Union {
public:
	PlayerState_Jump();

	virtual void unique_init() override;

	virtual void update(float deltaTime) override;

	virtual void end() override;
private:
	void key_update();
	void pad_update();
private:
private:
	Vector2 dir_;
	float power_;
	float gra_easeing_;
};