#pragma once

#include "../PlayerState_Single.h"

class PlayerState_Single_Idle : public PlayerState_Single {
public:
	PlayerState_Single_Idle(const Keys& keys);
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
	virtual void key_input(float deltaTime) override;
	virtual void pad_input(float deltaTime) override;
private:
	void move(float deltaTime);
};

