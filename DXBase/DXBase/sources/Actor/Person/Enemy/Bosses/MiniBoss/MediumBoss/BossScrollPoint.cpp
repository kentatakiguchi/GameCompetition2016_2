#include "BossScrollPoint.h"
#include "../../../../../../World/IWorld.h"
#include "../../../../../../Define.h"

BossScrollPoint::BossScrollPoint(IWorld * world, const Vector2 & position) : 
	Actor(world, "BossScrollPoint", 
		position + Vector2::Right * (CHIPSIZE / 3.0f), 
		CollisionBase())
{
}

void BossScrollPoint::onUpdate(float deltaTime)
{
	// �v���C���[���͈͓��ɂ��邩
	auto player = world_->findActor("PlayerBody1");
	if (player != nullptr) {
		auto distance = Vector2(position_ - player->getPosition());
		if (std::abs(distance.x) > CHIPSIZE * 9.5f || 
			std::abs(distance.y) > CHIPSIZE * 5.5f) return;
		// �͈͓��ɂ���
		world_->setIsMBossStage(true);
	}
	else return;

	auto boss = world_->findActor("Boss");
	// ���{�X�����Ȃ��Ȃ�A�폜����
	if (boss == nullptr) {
		world_->setIsMBossStage(false);
		dead();
	}
}
