#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Vector3.h"

// ÉvÉåÅ[ÉÑÅ[
class TestColl : public Actor {
public:
	TestColl(IWorld* world, const Vector3& position);
	~TestColl();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
};