#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "PlayerPtr.h"

#include "../../../Math/BezierCurve.h"
#include "Player.h"

// ÉvÉåÅ[ÉÑÅ[
class PlayerConnector : public Actor {
public:
	PlayerConnector();
	PlayerConnector(IWorld* world, PlayerBodyPtr main, PlayerBodyPtr sub);
	~PlayerConnector();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void changeMotion(float deltaTime);
	void set_point(PlayerBodyPtr start, PlayerBodyPtr end);
	void create_point(int point_num = 0);
private:

	BezierCurve bezier_;
	
	PlayerBodyPtr start_point_;
	PlayerBodyPtr end_point_;
	std::vector<Vector2> points;

	BoundingBox map_chip_;
};
