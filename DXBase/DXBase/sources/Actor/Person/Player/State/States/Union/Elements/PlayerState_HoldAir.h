#pragma once

#include "../PlayerState_Union.h"

class PlayerState_HoldAir : public PlayerState_Union {
public:
	PlayerState_HoldAir(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
	virtual void key_input(float deltaTime) override;
	virtual void pad_input(float deltaTime) override;
private:
	void move(float deltaTime);
private:
	bool flag1_;
	bool flag2_;
};
