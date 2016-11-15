#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "State/Base/StateMgr.h"
#include "PlayerBody.h"
#include "PlayerConnector.h"

#include "HitOpponent.h"

// ÉvÉåÅ[ÉÑÅ[
class PlayerBase : public Actor {
public:
	PlayerBase(IWorld* world, const Vector2& position);
	~PlayerBase();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void setBody(PlayerBodyPtr main, PlayerBodyPtr sub);
	PlayerBodyPtr getMainBody();
	PlayerBodyPtr getSubBody();
private:
	StateMgr stateMgr_;

	PlayerBodyPtr main_;
	PlayerBodyPtr sub_;
	PlayerCntrPtr cntr_;

	HitOpponent opponent_;
};