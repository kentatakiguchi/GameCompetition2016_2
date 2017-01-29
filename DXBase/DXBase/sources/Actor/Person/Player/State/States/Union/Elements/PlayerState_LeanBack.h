#pragma once

#include "../PlayerState_Union.h"

class PlayerState_LeanBack : public PlayerState_Union {
public:
	PlayerState_LeanBack(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
	virtual void key_input(float deltaTime) override;
	virtual void pad_input(float deltaTime) override;
private:
	float timer_;
	Vector2 dir_;
	float power_;

};