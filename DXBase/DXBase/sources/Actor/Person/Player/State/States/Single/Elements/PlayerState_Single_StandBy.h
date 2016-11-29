#pragma once

#include "../PlayerState_Single.h"

class PlayerState_Single_StandBy : public PlayerState_Single {
public:
	PlayerState_Single_StandBy();
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
};

