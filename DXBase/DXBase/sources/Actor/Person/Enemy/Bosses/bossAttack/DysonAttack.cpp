#include "DysonAttack.h"
#include "../../Rock.h"
#include "./../../../../Base/ActorGroup.h"
#include "../../../../../World/IWorld.h"
#include "../Tornado.h"

DysonAttack::DysonAttack() : 
	BossAttack(Vector2::Zero),
	addAngle_(0.0f),
	world_(nullptr),
	tornadoObj_(nullptr)
{
}

DysonAttack::DysonAttack(IWorld * world, const Vector2 & position) :
	BossAttack(position),
	addAngle_(2.0f),
	world_(world),
	tornadoObj_(nullptr)
{
	angle_ = 70.0f;
	/*auto tornado = std::make_shared<Tornado>(
		world_, Vector2(-1000.0f, 0.0f), Vector2(CHIPSIZE * 10, 32.0f * 3));
	world_->addActor(ActorGroup::Enemy, tornado);
	tornadoObj_ = tornado.get();*/
}

void DysonAttack::attack(float deltaTime)
{
	// ��̐���
	/*if (timer_ <= 0.2f)
		world_->addActor(ActorGroup::Enemy,
			std::make_shared<Rock>(world_, Vector2(200.0f, 200.0f)));*/
	// �{�X�̗����U��(��)
	if (tornadoObj_ == nullptr) {
		auto tornado = std::make_shared<Tornado>(
			world_, position_, Vector2(CHIPSIZE * 10, 32.0f * 3));
		world_->addActor(ActorGroup::Enemy, tornado);
		tornadoObj_ = tornado.get();
	}
	// �����I�u�W�F�N�g�̈ʒu�X�V
	if (tornadoObj_ != nullptr)
		tornadoObj_->position_ = position_;

	if (isWspHit_ && isPrevWspHit_ != isWspHit_) {
		direction_.x *= -1;
	}
	// �p�x�����l�𒴂�����A���Z������ς���
	if (angle_ >= 90.0f + 40.0f || angle_ <= 90.0f - 40.0f)
		addAngle_ *= -1;
	// �p�x�̉��Z
	angle_ += addAngle_;
	tornadoObj_->setAngle(angle_);

	isPrevWspHit_ = isWspHit_;

	position_.x += 4.0f * direction_.x * (deltaTime * 60.0f);

	// ��莞�Ԍo�߂ōU���I��
	if (timer_ <= 7.0f) return;
	tornadoObj_->dead();
	tornadoObj_->initPosition();
	isAttackEnd_ = true;
}

void DysonAttack::Refresh()
{
	BossAttack::Refresh();
	tornadoObj_ = nullptr;
}
