#include "BossManager.h"
#include "bossAttack/BossAttack.h"
#include "bossAttack/importBossAttack.h"

BossManager::BossManager() : 
	attackNumber_(0)//,
	/*timer_(0.0f),
	isAttackEnd_(false),
	movePosition_(Vector2::Zero)*/
{
}

BossManager::BossManager(const Vector2 & position) : 
	attackNumber_(0)//,
	/*timer_(0.0f),
	isAttackEnd_(false),
	movePosition_(position)*/
{
	// bossAttackContainer_.clear();
	// �U���s���̒ǉ�
	// bossAttackContainer_.push_back(std::make_shared<JumpAttack>(position));
	bossAttackContainer_.push_back(std::make_shared<ThreeJumpAttack>(position));
}

// �w�肵���ԍ��̍U���s�����s���܂�
void BossManager::attackMove(const float number, const float deltaTime)
{
	// �U��
	attackNumber_ = number;
	bossAttackContainer_[attackNumber_]->update(deltaTime);

	// �U�����I�������̏������A�l��Ԃ����Ƃ��ɍs��
}

// �s���̃��t���b�V�����s���܂�
void BossManager::moveRefresh()
{
	/*timer_ = 0.0f;
	isAttackEnd_ = false;*/
}

// �s���ɂ���Ĉړ������ʒu��Ԃ��܂�
Vector2 BossManager::getMovePosition()
{
	return bossAttackContainer_[attackNumber_]->getMovePosition();
	// return bossAttackContainer_[attackNumber_].getMovePosition();

	// return jumpAttack_.getMovePosition();
	// return movePosition_;
}

// �U�����I����������Ԃ��܂�
bool BossManager::isAttackEnd()
{
	return bossAttackContainer_[attackNumber_]->isAttackEnd();
}

Vector2 BossManager::getDirection(const Vector2 & otherPosition)
{
	// �����̌v�Z
	auto pos = bossAttackContainer_[attackNumber_]->getMovePosition();
	auto distance = pos - otherPosition;
	auto direction = Vector2().Zero;
	// �����̒l����
	// X
	if (distance.x < 0)
		direction.x = -1;
	else if (distance.x > 0)
		direction.x = 1;
	else direction.x = 0;
	// Y
	if (distance.y < 0)
		direction.y = 1;
	else if (distance.y > 0)
		direction.y = -1;
	else direction.y = 0;

	return direction;
}

Vector2 BossManager::getPlayerDirection()
{
	return Vector2();
}
