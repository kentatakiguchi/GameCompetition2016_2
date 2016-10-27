#include "FloorSearchPoint.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"

FloorSearchPoint::FloorSearchPoint(IWorld * world, const Vector3& pointPosition, const Vector3&  collidePosition) :
	pointPosition_(pointPosition),
	Actor(world, "FSP", collidePosition, 
		CollisionBase(Vector2(collidePosition.x, collidePosition.y), 1.0f)),
	turnCount_(0),
	isFloor_(false),
	isGround_(false),
	direction_(1.0f, 1.0f),
	enemyScale_(Vector2::Zero)
{
}

void FloorSearchPoint::onUpdate(float deltaTime)
{
	auto pos = position_;
	auto pointPos = Vector3(
		pointPosition_.x * direction_.x, pointPosition_.y * direction_.y, 0.0f);
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
void FloorSearchPoint::setPosition(Vector3 position)
{
	position_ = position;
}

// �����̐ݒ�
void FloorSearchPoint::setDirectionX(int direction)
{
	direction_.x = direction;
}

void FloorSearchPoint::setDirectionY(int direction)
{
	direction_.y = direction;
}

// �G�̑傫�������܂�
void FloorSearchPoint::setEnemyScale(const Vector2 scale)
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
