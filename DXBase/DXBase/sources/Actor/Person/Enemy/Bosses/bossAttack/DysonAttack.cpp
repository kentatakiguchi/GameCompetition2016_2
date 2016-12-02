#include "DysonAttack.h"
#include "../../Rock.h"
#include "./../../../../Base/ActorGroup.h"
#include "../../../../../World/IWorld.h"
#include "../Tornado.h"

DysonAttack::DysonAttack() : 
	BossAttack(Vector2::Zero),
	world_(nullptr),
	tornadoObj_(nullptr)
{
}

DysonAttack::DysonAttack(IWorld * world, const Vector2 & position) :
	BossAttack(position),
	world_(world),
	tornadoObj_(nullptr)
{
	/*auto tornado = std::make_shared<Tornado>(
		world_, Vector2(-1000.0f, 0.0f), Vector2(CHIPSIZE * 10, 32.0f * 3));
	world_->addActor(ActorGroup::Enemy, tornado);
	tornadoObj_ = tornado.get();*/
}

void DysonAttack::attack(float deltaTime)
{
	// 岩の生成
	/*if (timer_ <= 0.2f)
		world_->addActor(ActorGroup::Enemy,
			std::make_shared<Rock>(world_, Vector2(200.0f, 200.0f)));*/
	// ボスの竜巻攻撃(仮)
	if (tornadoObj_ == nullptr) {
		auto tornado = std::make_shared<Tornado>(
			world_, position_, Vector2(CHIPSIZE * 10, 32.0f * 3));
		world_->addActor(ActorGroup::Enemy, tornado);
		tornadoObj_ = tornado.get();
	}
	// 竜巻オブジェクトの位置更新
	if (tornadoObj_ != nullptr)
		tornadoObj_->position_ = position_;

	if (isWspHit_ && isPrevWspHit_ != isWspHit_) {
		direction_.x *= -1;
	}

	position_.x += 4.0f * direction_.x * (deltaTime * 60.0f);

	// 一定時間経過で攻撃終了
	if (timer_ <= 5.0f) return;
	tornadoObj_->dead();
	tornadoObj_->initPosition();
	isAttackEnd_ = true;
}

void DysonAttack::Refresh()
{
	BossAttack::Refresh();
	tornadoObj_ = nullptr;
}
