#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Split : public PlayerState_Union {
public:
	PlayerState_Split();
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
private:
	float time_;
};