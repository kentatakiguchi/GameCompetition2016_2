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
	// �f�o�b�O
	body_.draw();
}

void BaseBoss::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	if (actorName == "" || actorName == "") {
		//dead();
		hp_ -= 10;
		damageResult_ = 10;
		// �̗͂�0�ɂȂ����玀�S
		if (hp_ <= 0) {
			dead();
		}
		// �ϋv�l��0�ɂȂ�����A�Ђ��
		if (damageResult_ <= 0) {
			damageResult_ = initDamageResult_;
		}
	}
}

void BaseBoss::onMessage(EventMessage event, void *)
{
}
