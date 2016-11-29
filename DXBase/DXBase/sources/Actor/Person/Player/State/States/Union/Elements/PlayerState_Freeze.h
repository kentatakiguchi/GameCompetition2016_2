#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Freeze : public PlayerState_Union {
public:
	PlayerState_Freeze();
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
	virtual void key_input() override;
	virtual void pad_input() override;
private:
	float timer_;
};