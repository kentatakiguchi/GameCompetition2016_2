#include "BossManager.h"
#include "bossAttack/BossAttack.h"

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
	//bossAttackContainer_.push_back(std::make_shared<ThreeJumpAttack>(position));
	//bossAttackContainer_.push_back(std::make_shared<WallAttack>(position));
	////bossAttackContainer_.push_back(std::make_shared<PluralWallAttack>(position));
	//bossAttackContainer_.push_back(std::make_shared<DysonAttack>(, position));
}

// �U���R���e�i�ɍU����ǉ����܂�
void BossManager::addAttack(std::shared_ptr<BossAttack> attack)
{
	bossAttackContainer_.push_back(attack);
}

// �U���̔ԍ���ύX���܂�
void BossManager::changeAttackNumber(const float number)
{
	// �ԍ��̕ύX
	attackNumber_ = number;
}

// �w�肵���ԍ��̍U���s�����s���܂�
void BossManager::attackMove(const float deltaTime)
{
	// �U��
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

// �U�����J�n��������Ԃ��܂�
bool BossManager::isAttackStart()
{
	return bossAttackContainer_[attackNumber_]->isAttackStart();
}

// �U�����I����������Ԃ��܂�
bool BossManager::isAttackEnd()
{
	return bossAttackContainer_[attackNumber_]->isAttackEnd();
}

// �v���C���[�̍U���ɓ����邩��Ԃ��܂�
bool BossManager::IsBodyHit()
{
	return false;
}

// �v���C���[�ɓ����邩��Ԃ��܂�
bool BossManager::IsAttackHit()
{
	return false;
}

// �Ђ�݃J�E���g��Ԃ��܂�
int BossManager::getFlinchCount()
{
	return bossAttackContainer_[attackNumber_]->getFlinchCount();
}

// �{�X�̐S���̗̑͂�ݒ肵�܂�
void BossManager::setHeartHP(const int hp)
{
	bossAttackContainer_[attackNumber_]->setHeartHP(hp);
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
	bossAttackContainer_[attackNumber_]->setPlayerPosition(position);
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
		direction.y = -1;
	else if (distance.y > 0)
		direction.y = 1;
	else direction.y = 0;

	return direction;
}

Vector2 BossManager::getPlayerDirection()
{
	// bossAttack�ɕ�����ݒ肷��
	auto direction = getDirection(playerPosition_);
	bossAttackContainer_[attackNumber_]->setPlayerDirection(direction);
	return direction;
}

// �w�肵���I�u�W�F�N�g�Ƃ̕����𐳋K���x�N�g���Ŏ擾���܂�
Vector2 BossManager::getNormalizeDirection(const Vector2 & otherPosition)
{
	auto distance = otherPosition - bossPosition_;
	auto direction = distance.Normalize();
	return direction;
}

// �v���C���[�Ƃ̕����𐳋K���x�N�g���Ŏ擾���܂�
Vector2 BossManager::getPlayerNormalizeDirection()
{
	auto direction = getNormalizeDirection(playerPosition_);
	bossAttackContainer_[attackNumber_]->setPlayerNormalizeDirection(direction);
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

// �{�X�������������̖��O��Ԃ��܂�
void BossManager::setFloorName(const char * name)
{
	bossAttackContainer_[attackNumber_]->setFloorName(name);
}

// �U�����ɏd�͂��g�p���邩��Ԃ��܂�
bool BossManager::IsUseGravity()
{
	return bossAttackContainer_[attackNumber_]->IsUseGravity();
}

// �Ǒ{���I�u�W�F�N�g��������������ݒ肵�܂�
void BossManager::setIsWallHit(bool isHit)
{
	bossAttackContainer_[attackNumber_]->setIsWallHit(isHit);
}

Vector2 BossManager::getWallMoveDirection()
{
	return bossAttackContainer_[attackNumber_]->getMoveDirection();
}
