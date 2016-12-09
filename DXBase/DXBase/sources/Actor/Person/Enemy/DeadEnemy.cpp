#include "DeadEnemy.h"

DeadEnemy::DeadEnemy(IWorld * world, const Vector2 & position, const Vector2 & bodyScale, const Vector2 & direction) : 
	Actor(world_, "DeadEnemy", position, 
		CollisionBase(CollisionBase(
			Vector2(position.x + bodyScale.x / 2.0f, position.y + bodyScale.y / 2.0f),
			Vector2(position.x - bodyScale.x / 2.0f, position.y + bodyScale.y / 2.0f),
			Vector2(position.x + bodyScale.x / 2.0f, position.y - bodyScale.y / 2.0f),
			Vector2(position.x - bodyScale.x / 2.0f, position.y - bodyScale.y / 2.0f)
			)))
{
}
