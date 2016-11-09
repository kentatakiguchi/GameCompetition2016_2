#include "BaseBoss.h"

BaseBoss::BaseBoss(IWorld * world, const Vector2 & position, const float bodyScale) : 
	Actor(world, "BaseEnemy", position,
		CollisionBase(
			Vector2(position.x + bodyScale / 2.0f, position.y + bodyScale / 2.0f),
			Vector2(position.x - bodyScale / 2.0f, position.y + bodyScale / 2.0f),
			Vector2(position.x + bodyScale / 2.0f, position.y - bodyScale / 2.0f),
			Vector2(position.x - bodyScale / 2.0f, position.y - bodyScale / 2.0f)
			)),
	damageResult_(20),
	initDamageResult_(damageResult_),
	hp_(100)
{
}

BaseBoss::~BaseBoss()
{
}

void BaseBoss::Initialize()
{
}

void BaseBoss::onUpdate(float deltaTime)
{
}

void BaseBoss::onDraw() const
{
	// デバッグ
	body_.draw();
}

void BaseBoss::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	if (actorName == "" || actorName == "") {
		//dead();
		hp_ -= 10;
		damageResult_ = 10;
		// 体力が0になったら死亡
		if (hp_ <= 0) {
			dead();
		}
		// 耐久値が0になったら、ひるむ
		if (damageResult_ <= 0) {
			damageResult_ = initDamageResult_;
		}
	}
}

void BaseBoss::onMessage(EventMessage event, void *)
{
}
