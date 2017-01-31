#pragma once

#include "../../PlayerState_Union.h"

class PlayerState_HoldBoth : public PlayerState_Union {
public:
	PlayerState_HoldBoth(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
	virtual void key_input(float deltaTime) override;
	virtual void pad_input(float deltaTime) override;
};