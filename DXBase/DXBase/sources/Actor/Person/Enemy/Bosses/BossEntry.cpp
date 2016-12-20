#include "BossEntry.h"
#include "Effect/ImportEffects.h"
#include "../../../../World/IWorld.h"
#include "../../../Base/ActorGroup.h"

BossEntry::BossEntry(
	IWorld * world,
	const Vector2 & position,
	const Vector2 & addPosition,
	const float bodyScale) :
	Actor(world, "BossEntry", position + addPosition,
		std::make_shared<BoundingCircle>(
			const_cast<Vector2&>(position) + 
			const_cast<Vector2&>(addPosition),Matrix::Identity,
			bodyScale,true)),
	blockTimer_(0.0f),
	isEntry_(false),
	isEntered_(false),
	isBlock_(false),
	direction_(1.0f, -1.0f),
	bossPosition_(position),
	addPosition_(addPosition)
{
}

void BossEntry::onUpdate(float deltaTime)
{
	auto addPos = Vector2(
		addPosition_.x * direction_.x,
		addPosition_.y * direction_.y);
	position_ = bossPosition_ + addPos;

	if (isBlock_)
		blockTimer_ += deltaTime;
	else blockTimer_ = 0.0f;

	// bool�n�̍X�V
	isBlock_ = false;
}

void BossEntry::onDraw() const
{
	body_->draw(-1,inv_);
	// �\��
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	DrawString(
		vec3Pos.x, vec3Pos.y,
		"�{�X�̌��ł�", GetColor(255, 255, 255));
}

void BossEntry::onCollide(Actor & actor)
{
	// �v���C���[���Ȃ��ł�����ɓ���������(�����h���ꂽ��)
	if (actor.getName() == "BodyPoint") {
		isBlock_ = true;
	}

	// ���ɓ�����Ԃ̂݁A�v���C���[�̖{�̂ɓ�����
	if (!isEntry_) return;
	if (actor.getName() == "PlayerBody1" || actor.getName() == "PlayerBody2") {
		// �v���C���[�̈ʒu��ύX
		//world_->addActor(ActorGroup::Effect, star);
		world_->addActor(ActorGroup::Effect,
			std::make_shared<BokoEffect>(world_, position_));
		isEntered_ = true;
	}
}

void BossEntry::onMessage(EventMessage event, void *)
{
}

// �ʒu�̐ݒ�����܂�
void BossEntry::setBossPosition(const Vector2 & position)
{
	bossPosition_ = position;
}

// ������ݒ肵�܂�
void BossEntry::setDirection(const Vector2 & direction)
{
	direction_ = direction;
}

// �{�X�̑̓��ɓ���邩��ݒ肵�܂�
void BossEntry::setIsEntry(bool isEntry)
{
	isEntry_ = isEntry;
}

// �{�X�̑̓��ɓ���������Ԃ��܂�
bool BossEntry::isEntered()
{
	return isEntered_;
}

// �v���C���[���Ȃ����ɐG��Ă��邩��Ԃ��܂�
bool BossEntry::isBlock()
{
	return isBlock_;
}

// �v���C���[���{�X�̑̓��ɏo�����Ƃɂ��܂�
void BossEntry::letOut()
{
	isEntry_ = false;
	isEntered_ = false;
}
