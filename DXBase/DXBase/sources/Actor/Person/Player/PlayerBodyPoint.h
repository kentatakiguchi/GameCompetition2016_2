#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"

// ÉvÉåÅ[ÉÑÅ[
class PlayerBodyPoint : public Actor {
public:
	PlayerBodyPoint(IWorld* world, const Vector2 & position, const int& point_index);
	~PlayerBodyPoint();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onCollide(Actor& other) override;
	// à¯óÕ
	void attraction(const int index, Vector2& velocity);
private:
	int index_;

	Vector2 v1_;
	Vector2 v2_;

	float stiffness_;
	float friction_;
	float mass_;
};
