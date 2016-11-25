#include "BossManager.h"
#include "bossAttack/BossAttack.h"
#include "bossAttack/importBossAttack.h"

BossManager::BossManager() : 
	attackNumber_(0),
	bossPosition_(Vector2::Zero),
	playerPosition_(Vector2::Zero)
	/*timer_(0.0f),
	isAttackEnd_(false),
	movePosition_(Vector2::Zero)*/
{
}

BossManager::BossManager(const Vector2 & position) : 
	attackNumber_(0), 
	bossPosition_(position),
	playerPosition_(Vector2::Zero)
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
void BossManager::attackRefresh()
{
	bossAttackContainer_[attackNumber_]->Refresh();
}

// �s���ɂ���Ĉړ������ʒu��Ԃ��܂�
Vector2 BossManager::getMovePosition()
{
	return bossAttackContainer_[attackNumber_]->getMovePosition();
}

// �U�����I����������Ԃ��܂�
bool BossManager::isAttackEnd()
{
	return bossAttackContainer_[attackNumber_]->isAttackEnd();
}

// �{�X�̈ʒu��ݒ肵�܂�
void BossManager::setPosition(const Vector2& position)
{
	bossPosition_ = position;
}

// �v���C���[�̈ʒu��ݒ肵�܂�
void BossManager::setPlayerPosition(const Vector2 & position)
{
	playerPosition_ = position;
}

// �U���O�̈ʒu�����肵�܂�
void BossManager::prevPosition()
{
	bossAttackContainer_[attackNumber_]->setPosition(bossPosition_);
}

Vector2 BossManager::getDirection(const Vector2 & otherPosition)
{
	// �����̌v�Z(�{�X�̈ʒu���厲�ɂ���)
	// auto pos = bossAttackContainer_[attackNumber_]->getMovePosition();
	auto distance = otherPosition - bossPosition_;
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
	// bossAttack�ɕ�����ݒ肷��
	auto direction = getDirection(playerPosition_);
	bossAttackContainer_[attackNumber_]->setDirection(direction);
	return direction;
}

void BossManager::setIsGround(bool isGround)
{
	bossAttackContainer_[attackNumber_]->setIsGround(isGround);
}

// �{�X���ǂ̉����ɓ�����������ݒ肵�܂�
void BossManager::setIsBottom(bool isBottom)
{
	bossAttackContainer_[attackNumber_]->setIsBottom(isBottom);
}
