#include "FloorSearchPoint.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"

FloorSearchPoint::FloorSearchPoint(
	IWorld * world, 
	const Vector2& enemyPosition,
	const Vector2& addPosition,
	const Vector2& bodyScale
	) :
	Actor(world, "FSP", enemyPosition + addPosition,
		CollisionBase(
			Vector2((enemyPosition.x + addPosition.x) + bodyScale.x / 2.0f, (enemyPosition.y + addPosition.y) + bodyScale.y / 2.0f),
			Vector2((enemyPosition.x + addPosition.x) - bodyScale.x / 2.0f, (enemyPosition.y + addPosition.y) + bodyScale.y / 2.0f),
			Vector2((enemyPosition.x + addPosition.x) + bodyScale.x / 2.0f, (enemyPosition.y + addPosition.y) - bodyScale.y / 2.0f),
			Vector2((enemyPosition.x + addPosition.x) - bodyScale.x / 2.0f, (enemyPosition.y + addPosition.y) - bodyScale.y / 2.0f)
			)
		),
	turnCount_(0),
	isFloor_(false),
	isGround_(false),
	direction_(1.0f, 1.0f),
	enemyPosition_(enemyPosition),
	addPosition_(addPosition),
	floorPosition_(Vector2::Zero)
{
}

FloorSearchPoint::FloorSearchPoint(
	IWorld * world, 
	const Vector2 & enemyPosition,
	const Vector2 & addPosition,
	const float radius) : 
	Actor(world, "FSP", enemyPosition + addPosition,
		CollisionBase(position_, radius)),
	turnCount_(0),
	isFloor_(false),
	isGround_(false),
	direction_(1.0f, 1.0f),
	enemyPosition_(enemyPosition),
	addPosition_(addPosition),
	floorPosition_(Vector2::Zero)
{
}

void FloorSearchPoint::onUpdate(float deltaTime)
{
	auto addPos = Vector2(
		addPosition_.x * direction_.x,
		addPosition_.y * direction_.y);
	position_ = enemyPosition_ + addPos;

	isFloor_ = false;
	isGround_ = false;
}

void FloorSearchPoint::onDraw() const
{
	body_.draw(inv_);
}

void FloorSearchPoint::onCollide(Actor & actor)
{
	// ���ɓ������Ă����A�U������񐔂����Z�b�g
	if (actor.getName() == "MovelessFloor") {
		turnCount_ = 0;
		isGround_ = true;
		isFloor_ = true;
		// �ʒu���u���b�N�̏�ʂɏC������
		// clampPosition(position_, actor.position_);
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
}

void FloorSearchPoint::onMessage(EventMessage event, void *)
{
}

// �ʒu�̐ݒ�
void FloorSearchPoint::setPosition(const Vector2& position)
{
	//position_ = position;
	enemyPosition_ = position;
}

// �����̐ݒ�
void FloorSearchPoint::setDirection(const Vector2& direction)
{
	direction_ = direction;
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
