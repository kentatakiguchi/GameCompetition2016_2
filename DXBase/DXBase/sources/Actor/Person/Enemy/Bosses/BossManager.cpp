#include "BossManager.h"
#include "bossAttack/BossAttack.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"

BossManager::BossManager() : 
	attackNumber_(0),
	bossPosition_(Vector2::Zero),
	playerPosition_(Vector2::Zero)
{}

BossManager::BossManager(IWorld* world, const Vector2 & position) :
	attackNumber_(0), 
	bossPosition_(position),
	playerPosition_(Vector2::Zero)
{}

// �f�X�g���N�^
BossManager::~BossManager()
{
	bossAttackContainer_.clear();
}

// �U���R���e�i�ɍU����ǉ����܂�
void BossManager::addAttack(std::shared_ptr<BossAttack> attack)
{
	bossAttackContainer_.push_back(attack);
}

// �U���̔ԍ���ύX���܂�
void BossManager::changeAttackNumber(const int number)
{
	// �ԍ��̕ύX
	attackNumber_ = number;
}

// �w�肵���ԍ��̍U���s�����s���܂�
void BossManager::attackMove(const float deltaTime)
{
	// �U��
	bossAttackContainer_[attackNumber_]->update(deltaTime);
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

// �U���������擾���܂�
Vector2 BossManager::getAttackDirection()
{
	return bossAttackContainer_[attackNumber_]->getDirection();
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
	return bossAttackContainer_[attackNumber_]->isBodyHit();
}

// �v���C���[�ɓ����邩��Ԃ��܂�
bool BossManager::IsAttackHit()
{
	return bossAttackContainer_[attackNumber_]->isAttackHit();
}

// ���ނ���Ԃ��܂�
bool BossManager::isFlinch()
{
	return bossAttackContainer_[attackNumber_]->isFlinch();
}

// �Ђ�݃J�E���g��Ԃ��܂�
int BossManager::getFlinchCount()
{
	return bossAttackContainer_[attackNumber_]->getFlinchCount();
}

// �p�x��Ԃ��܂�
float BossManager::getAngle()
{
	return bossAttackContainer_[attackNumber_]->getAngle();
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
bool BossManager::isUseGravity()
{
	return bossAttackContainer_[attackNumber_]->isUseGravity();
}

// �U�����\�ȏ�Ԃ���ݒ肵�܂�
void BossManager::setIsAttackMove(bool isMove)
{
	bossAttackContainer_[attackNumber_]->setIsMove(isMove);
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

// �Փ˂����I�u�W�F�N�g��ݒ肵�܂�
void BossManager::setCollideObj(Actor & actor)
{
	bossAttackContainer_[attackNumber_]->setCollideObj(actor);
}

// �A�j���[�V�����ԍ���Ԃ��܂�
int BossManager::getAnimaNum()
{
	return bossAttackContainer_[attackNumber_]->getAnimaNum();
}

// �A�j���[�V�����̊p�x��Ԃ��܂�
int BossManager::getAnimeAngle()
{
	return bossAttackContainer_[attackNumber_]->getAnimeAngle();
}

// �A�j���[�V���������[�v���邩��Ԃ��܂�
bool BossManager::isAnimeLoop()
{
	return bossAttackContainer_[attackNumber_]->isLoop();
}

// �A�j���[�V�������t�Đ����邩��Ԃ��܂�
bool BossManager::isAnimeReverse()
{
	return bossAttackContainer_[attackNumber_]->isReverse();
}
