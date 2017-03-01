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
	// プレイヤーが範囲内にいるか
	auto player = world_->findActor("PlayerBody1");
	if (player != nullptr) {
		auto distance = Vector2(position_ - player->getPosition());
		if (std::abs(distance.x) > CHIPSIZE * 9.5f || 
			std::abs(distance.y) > CHIPSIZE * 5.5f) return;
		// 範囲内にいる
		world_->setIsMBossStage(true);
	}
	else return;

	auto boss = world_->findActor("Boss");
	// 中ボスがいないなら、削除する
	if (boss == nullptr) {
		world_->setIsMBossStage(false);
		dead();
	}
}
