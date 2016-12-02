#include "Tornado.h"

Tornado::Tornado(IWorld * world, const Vector2 & position, const float bodyScale) : 
	Actor(world, "Tornado", position,
		CollisionBase(
			Vector2(position.x + bodyScale, position.y + bodyScale / 2.0f),
			Vector2(position.x, position.y + bodyScale / 2.0f),
			Vector2(position.x + bodyScale, position.y - bodyScale / 2.0f),
			Vector2(position.x, position.y - bodyScale / 2.0f)
			))
{
}

void Tornado::onUpdate(float deltaTime)
{
}

void Tornado::onDraw() const
{
	/*auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;*/
	// デバッグ
	body_.draw(inv_);
}

void Tornado::onCollide(Actor & actor)
{
}

void Tornado::onMessage(EventMessage event, void *)
{
}
