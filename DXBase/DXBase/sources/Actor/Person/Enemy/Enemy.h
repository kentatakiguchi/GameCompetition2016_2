#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"
//#include "Field.h"
//#include "Ray.h"
//#include "Explosion.h"
//#include "Fire.h"
//#include "EventMessage.h"
//#include "Asset.h"
//#include "AnimatedMesh.h"

enum {
	ENEMY_IDLE = 0,
	ENEMY_DAMAGE = 1,
	ENEMY_WALK = 2,
	ENEMY_ATTACK = 3
};

// “G
class Enemy : public Actor {
public:
	enum class State {
		INIT,
		IDLE,
		MOVE,
		CHASE,
		ATTACK,
		DAMAGE,
		DEAD
	};
	Enemy(IWorld* world, const Vector3&  position);
	~Enemy();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;
private:
	void updateState(float deltaTime);
	void changeState(State state, unsigned int motion);
	void init();
	void idle(float deltaTime);
	void move(float deltaTime);
	void chase(float deltaTime);
	void attack(float deltaTime);
	void damage(float deltaTime);
	void setPos();
private:
	float timer_;

	State state_;
	float stateTimer_;

	Vector3 target_;
};