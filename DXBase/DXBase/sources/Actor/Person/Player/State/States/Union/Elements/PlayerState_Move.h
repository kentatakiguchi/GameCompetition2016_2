#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Move : public PlayerState_Union {
public:
	PlayerState_Move();

	virtual void unique_init() override;

	virtual void update(float deltaTime) override;

	virtual void end() override;
private:
	void move(float deltaTime);
private:
	void key_update();
	void pad_update();

};