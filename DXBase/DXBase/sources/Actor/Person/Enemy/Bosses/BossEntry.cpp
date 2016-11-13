#include "BossEntry.h"

BossEntry::BossEntry(
	IWorld * world,
	const Vector2 & position,
	const Vector2 & addPosition,
	const float bodyScale) :
	Actor(world, "BossEntry", position + addPosition,
		CollisionBase(
			const_cast<Vector2&>(position) + 
			const_cast<Vector2&>(addPosition),
			bodyScale)),
	isEntry_(false),
	isEntered_(false),
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
}

void BossEntry::onDraw() const
{
	body_.draw(inv_);
	// �\��
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	DrawString(
		vec3Pos.x, vec3Pos.y,
		"�{�X�̌��ł�", GetColor(255, 255, 255));
}

void BossEntry::onCollide(Actor & actor)
{
	// ���ɓ�����Ԃ̂ݓ�����
	if (!isEntry_) return;
	if (actor.getName() == "PlayerBody1" || actor.getName() == "PlayerBody2") {
		// �v���C���[�̈ʒu��ύX

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

// �v���C���[���{�X�̑̓��ɏo�����Ƃɂ��܂�
void BossEntry::letOut()
{
	isEntry_ = false;
	isEntered_ = false;
}
