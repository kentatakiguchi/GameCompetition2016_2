#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "Field.h"
//#include "Ray.h"
//#include "Bullet.h"
//#include "EventMessage.h"
#include "../../../Math/Vector3.h"
#include "State/Base/StateMgr.h"

// ÉvÉåÅ[ÉÑÅ[
class PlayerConnector : public Actor {
public:
	enum class MOTION {
		WALK1,
		WALK2
	};
public:
	PlayerConnector(IWorld* world);
	~PlayerConnector();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void changeMotion(float deltaTime);
private:
	StateMgr stateMgr_;
};