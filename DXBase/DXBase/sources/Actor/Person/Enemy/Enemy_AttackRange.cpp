#include "Enemy_AttackRange.h"
#include"../../Body/CollisionBase.h"

Enemy_AttackRange::Enemy_AttackRange(IWorld * world, const Vector3 & position) :
	Actor(world, "Enemy_AttackRange", position, CollisionBase()),
	lifeTimer_(0) {

}

void Enemy_AttackRange::onUpdate(float deltaTime){
	lifeTimer_ += deltaTime;
	if (lifeTimer_ >= LIFE_TIME) dead();
}
