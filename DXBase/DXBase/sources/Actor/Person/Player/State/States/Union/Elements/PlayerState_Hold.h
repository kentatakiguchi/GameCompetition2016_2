#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Hold : public PlayerState_Union {
public:
	PlayerState_Hold();
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
	virtual void key_input() override;
	virtual void pad_input() override;
private:
	void move();
}; 
