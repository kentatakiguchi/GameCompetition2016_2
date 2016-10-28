#include "FloorSearchPoint.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"

FloorSearchPoint::FloorSearchPoint(IWorld * world, const Vector2& pointPosition, const Vector2&  collidePosition) :
	pointPosition_(pointPosition),
	Actor(world, "FSP", collidePosition, 
		CollisionBase(Vector2(collidePosition.x, collidePosition.y), 1.0f)),
	turnCount_(0),
	isFloor_(false),
	isGround_(false),
	direction_(1.0f, 1.0f),
	enemyScale_(Vector2::Zero),
	floorPosition_(Vector2::Zero)
{
}

void FloorSearchPoint::onUpdate(float deltaTime)
{
	auto pos = position_;
	auto pointPos = Vector2(
		pointPosition_.x * direction_.x,
		pointPosition_.y * direction_.y);
	position_ = pos + pointPos;
	isFloor_ = false;
	isGround_ = false;
}

void FloorSearchPoint::onDraw() const
{
	body_.draw();
}

void FloorSearchPoint::onCollide(Actor & actor)
{
	// ���ɓ������Ă����A�U������񐔂����Z�b�g
	if (actor.getName() == "MapChip") {
		turnCount_ = 0;
		isGround_ = true;
		// �ʒu���u���b�N�̏�ʂɏC������
		clampPosition(position_, actor.position_);
		return;
	}
	//// �U������񐔂����Z
	//turnCount_ += 1;
	//// ���[�ɏ�������������A�����Ȃ�
	//if (turnCount_ > 1) {
	//	direction_ = 0;
	//	return;
	//}
	//// �����̕ύX
	//direction_ *= -1;
	//position_.x *= -1;
	isFloor_ = true;
}

void FloorSearchPoint::onMessage(EventMessage event, void *)
{
}

// �ʒu�̐ݒ�
void FloorSearchPoint::setPosition(const Vector2& position)
{
	position_ = position;
}

// �����̐ݒ�
void FloorSearchPoint::setDirection(const Vector2& direction)
{
	direction_ = direction;
}

// �G�̑傫�������܂�
void FloorSearchPoint::setEnemyScale(const Vector2& scale)
{
	//enemyScale_ = scale;
	position_.x += scale.x;
	position_.y += scale.y;
}

// ���Ɠ�����������Ԃ��܂�
bool FloorSearchPoint::isFloor()
{
	return isFloor_;
}

bool FloorSearchPoint::isGround()
{
	return isGround_;
}

// ���Ɠ��������ꏊ��Ԃ��܂�
Vector2 FloorSearchPoint::getFloorPosition()
{
	return floorPosition_;
}

// ���Ƃ̈ʒu���N�����v���܂�
void FloorSearchPoint::clampPosition(const Vector2& thisPosition, const Vector2& otherPosition)
{
	// ���Ƃ̈ʒu���v�Z�@���̒l�̏ꍇ�A���̉��ɂ���
	auto posY = otherPosition.y - thisPosition.y - 32.0f;
	//// ���a�����Z�����ʒu�ɂ���
	if (posY < 0)
		floorPosition_ = position_ + Vector2::Up * posY;
}
