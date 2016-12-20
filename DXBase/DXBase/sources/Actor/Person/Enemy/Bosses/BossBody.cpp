#include "BossBody.h"

BossBody::BossBody(IWorld * world, const Vector2 & position) : 
	Actor(world, "BossBody", position,
		CollisionBase(const_cast<Vector2&>(position), 1.0f))
{
}

void BossBody::onUpdate(float deltaTime)
{
}

void BossBody::onDraw() const
{
}

void BossBody::onCollide(Actor & actor)
{
}

void BossBody::onMessage(EventMessage event, void *)
{
}
