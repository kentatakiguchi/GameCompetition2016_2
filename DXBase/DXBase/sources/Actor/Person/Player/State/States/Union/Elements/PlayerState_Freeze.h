#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Freeze : public PlayerState_Union {
public:
	PlayerState_Freeze(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void collide(const Actor & other) override {}
	virtual void end() override;
	virtual void key_input(float deltaTime) override;
	virtual void pad_input(float deltaTime) override;
};