#pragma once

#include "../PlayerState_Single.h"

class PlayerState_Single_Jump : public PlayerState_Single {
public:
	PlayerState_Single_Jump();

	virtual void unique_init() override;

	virtual void update(float deltaTime) override;

	virtual void end() override;
private:
	void move();
private:
	void key_update();
	void pad_update();

private:
	Vector2 dir_;
	float power_;
	float gra_easeing_;
};