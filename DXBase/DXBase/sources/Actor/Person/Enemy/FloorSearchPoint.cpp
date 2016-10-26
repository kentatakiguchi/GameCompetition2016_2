#include "FloorSearchPoint.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"

FloorSearchPoint::FloorSearchPoint(IWorld * world, const Vector3 & position) :
	vec2Position_(position.x, position.y),
	Actor(world, "BaseEnemy", position, CollisionBase(vec2Position_, 10.0f)),
	direction_(0),
	turnCount_(0),
	isFloor_(false),
	enemyScale_(Vector2::Zero)
{
}

void FloorSearchPoint::onUpdate(float deltaTime)
{

}

void FloorSearchPoint::onDraw() const
{
	body_.draw();
}

void FloorSearchPoint::onCollide(Actor & actor)
{
	// ���ɓ������Ă����A�U������񐔂����Z�b�g
	if (actor.getName() == "Floor") {
		turnCount_ = 0;
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
void FloorSearchPoint::setDirection(int direction)
{
	direction_ = direction;
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
