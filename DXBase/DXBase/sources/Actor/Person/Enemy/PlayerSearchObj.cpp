#include "PlayerSearchObj.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"

PlayerSearchObj::PlayerSearchObj(
	IWorld * world,
	const Vector2& enemyPosition,
	const Vector2& playerPosition) :
	Actor(world, "BaseEnemy",
		Vector2(
			std::abs(enemyPosition.x + playerPosition.x) / 2,
			std::abs(enemyPosition.y + playerPosition.y) / 2),
		CollisionBase(
			const_cast<Vector2&>(enemyPosition),
			const_cast<Vector2&>(playerPosition)
			)
		),
	enemyPosition_(enemyPosition),
	playerPosition_(playerPosition),
	blockPosition_(Vector2::Zero),
	isBlockHit_(false)
{
}

void PlayerSearchObj::onUpdate(float deltaTime)
{
	position_ = body_.setSegmentPoint(
		position_, enemyPosition_, playerPosition_);
	isBlockHit_ = false;
}

void PlayerSearchObj::onDraw() const{}

void PlayerSearchObj::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	// �v���C���[�֘A�̃I�u�W�F�N�g�ɓ������Ă���Ȃ�
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	// ���ɓ������Ă�����A�ʒu����
	if (getFloorName != NULL) {
		blockPosition_ = actor.position_;
		isBlockHit_ = true;
		return;
	}
}

// �G�ƃv���C���[�̈ʒu��ݒ肵�܂�
void PlayerSearchObj::setPosition(const Vector2 & enemyPosition, const Vector2 & playerPosition)
{
	enemyPosition_ = enemyPosition;
	playerPosition_ = playerPosition;
}

// �v���C���[�������Ă��邩��Ԃ��܂�
bool PlayerSearchObj::isPlayerLook()
{
	//auto blockLen = (enemyPosition_ - blockPosition_).Length();
	//auto playerLen = (enemyPosition_ - playerPosition_).Length();
	//// �v���C���[�Ƃ̋����Ƃ̋������Z��������Atrue��Ԃ�
	//if (playerLen < blockLen)
	//	return true;
	//return false;

	return !isBlockHit_;
}
