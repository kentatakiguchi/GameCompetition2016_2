#pragma once

#include "../PlayerState_Single.h"

class PlayerState_Single_Jump : public PlayerState_Single {
public:
	PlayerState_Single_Jump();
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
	virtual void key_input() override;
	virtual void pad_input() override;
private:
	void move();
private:
	Vector2 dir_;
	float power_;
	float gra_easeing_;
};