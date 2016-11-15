#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "State/Base/StateMgr.h"
#include "PlayerBody.h"
#include "PlayerConnector.h"

// ÉvÉåÅ[ÉÑÅ[
class Player : public Actor {
public:
	enum class MOTION {};
public:
	Player(IWorld* world, const Vector2& position);
	~Player();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void setBody(PlayerBodyPtr main, PlayerBodyPtr sub);
	void connect(PlayerBodyPtr main, PlayerBodyPtr sub);
	void split_body();
	PlayerBodyPtr getMainBody();
	PlayerBodyPtr getSubBody();

	Vector2 GetSpringVelo()
	{
		return veloPlus;
	}
private:
	StateMgr stateMgr_;

	PlayerBodyPtr main_;
	PlayerBodyPtr sub_;
	PlayerCntrPtr cntr_;
};

