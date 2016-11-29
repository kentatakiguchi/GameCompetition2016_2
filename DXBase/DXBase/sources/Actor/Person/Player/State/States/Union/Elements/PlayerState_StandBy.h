#pragma once

#include "../PlayerState_Union.h"

class PlayerState_StandBy : public PlayerState_Union {
public:
	PlayerState_StandBy();
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
};