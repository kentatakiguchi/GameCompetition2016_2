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
class PlayerBody : public Actor {
public:
	PlayerBody(IWorld* world, const std::string name, const Vector3& position);
	~PlayerBody();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void changeMotion(float deltaTime);
	void move(KeyCode up = KeyCode::UP, KeyCode down = KeyCode::DOWN, KeyCode right = KeyCode::RIGHT, KeyCode left = KeyCode::LEFT);
	void move_ver(KeyCode up = KeyCode::UP, KeyCode down = KeyCode::DOWN, KeyCode right = KeyCode::RIGHT, KeyCode left = KeyCode::LEFT);
	void chase();
	void gravity();
	void circleClamp();
	void launch(Vector3 dir);
	float distance();
	void target(std::shared_ptr<PlayerBody> target);
private:
	Vector3 velocity_;
	Vector3 lastPos_;
	std::shared_ptr<PlayerBody> target_;
	
	bool selected_;
};

