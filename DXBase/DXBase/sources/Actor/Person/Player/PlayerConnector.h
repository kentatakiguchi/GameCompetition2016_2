#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "../../../Math/Vector3.h"
#include "State/Base/StateMgr.h"
#include "../../../Math/BezierCurve.h"

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
	void set_point(const Vector2 & start, const Vector2 & end);
private:
	StateMgr stateMgr_;

	BezierCurve bezier_;
	
	Vector2 start_point_;
	Vector2 end_point_;
	std::vector<Vector2> points;


};