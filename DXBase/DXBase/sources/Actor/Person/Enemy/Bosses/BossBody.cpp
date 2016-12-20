#include "BossBody.h"

BossBody::BossBody(IWorld * world, const Vector2 & position) : 
	Actor(world, "BossBody", position,
		std::make_shared<BoundingCircle>(const_cast<Vector2&>(position),Matrix::Identity, 1.0f,true))
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
