#pragma once

#include "Base/PlayerState_AttackBase.h"

class PlayerState_AttackR : public PlayerState_AttackBase {
public:
	PlayerState_AttackR(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	virtual void onInit();
	virtual void onUpdate(float deltaTime);
	virtual void onCollide(const Actor & other);
	virtual void onEnd();
	virtual void onKeyInput(float deltaTime);
	virtual void onPadInput(float deltaTime);
};
