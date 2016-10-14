#include "Player_AttackRange.h"
#include"../../Body/CollisionBase.h"

Player_AttackRange::Player_AttackRange(IWorld * world, const Vector3 & position) :
	Actor(world, "Player_AttackRange", position, CollisionBase()),
	lifeTimer_(0){
	
}

void Player_AttackRange::onUpdate(float deltaTime){
	lifeTimer_ += deltaTime;
	if (lifeTimer_ >= LIFE_TIME) dead();
}
