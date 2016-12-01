#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "PlayerPtr.h"

#include "Player.h"

// ÉvÉåÅ[ÉÑÅ[
class PlayerBodyPoint : public Actor {
public:
	enum class Opponent {
		NONE,
		FLOOR,
		ITEM,
		TEST
	};
public:
	PlayerBodyPoint(IWorld* world, const Vector2 & position, const int& point_index/*, PlayerConnector& cntr*/);
	~PlayerBodyPoint();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onCollide(Actor& other) override;
	void compose_pos();
private:
	int index_;
};
