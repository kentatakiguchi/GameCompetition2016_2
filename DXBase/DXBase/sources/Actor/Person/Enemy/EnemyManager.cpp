#include "EnemyManager.h"
#include "FloorSearchPoint.h"
#include "PlayerSearchObj.h"
#include "../../Base/ActorGroup.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"

EnemyManager::EnemyManager(
	IWorld * world, 
	const Vector2 position, 
	const Vector2& direction) :
	distance_(1),
	wspResult_(0),
	wCollideCount_(0),
	wCollidePastCount_(wCollideCount_),
	timer_(0.0f),
	deltaTimer_(0.0f),
	boxMoveCount(0.0f),
	isDirection_(true),
	enemyPosition_(position),
	threadPosition_(position + Vector2::Left * 100.0f),
	enemyDirection_(Vector2::Zero),
	wsDirection_(Vector2(-1.0f, 0.0f)),
	animaDirection_(wsDirection_),
	world_(world)
{
	animaDirectionMap_.clear();
	wspDirectionMap_.clear();
	wallMoveConteiner_.push_back(0.0f);
	wallMoveConteiner_.push_back(1.0f);
	wallMoveConteiner_.push_back(0.0f);
	wallMoveConteiner_.push_back(-1.0f);
	// �f����ǉ�(3�`4��)
	primeContainer_.push_back(200);
	primeContainer_.push_back(300);
	primeContainer_.push_back(500);
	primeContainer_.push_back(700);
	primeContainer_.push_back(1100);
	primeContainer_.push_back(1300);
	primeContainer_.push_back(1700);
	primeContainer_.push_back(1900);
	// �ǈړ��̕������}�b�v�ɒǉ�
	addWSPDirection(direction);
	// �ʒu�R���e�i�̏�����
	positiones_.clear();
	psObjs.clear();
}

EnemyManager::~EnemyManager(){}

// �X�V
void EnemyManager::update(float deltaTime)
{
	deltaTimer_ = deltaTime;
	timer_ += deltaTimer_;
}

// �ǂɉ�����������
Vector2 EnemyManager::wallMove()
{
	// �G�̎l���ɓ����蔻��̂���I�u�W�F�N�g��z�u
	// ���������I�u�W�F�N�g�̖��O�Ȃǂ��Q�Ƃ��āA�����̒l�����肷��
	return wsDirection_;
}

// �R������铮����
Vector2 EnemyManager::cliffMove(bool isFloor)
{
	auto posi = enemyPosition_;
	posi = posi.Left * (float)distance_;
	// �G�̑O�������ɓ����蔻��̂���I�u�W�F�N�g��z�u
	// �����Ă�������ɂ���āA�I�u�W�F�N�g�̈ʒu��ς���
	return posi;
}

// �v���C���[�̈ʒu���擾���܂�
Vector2 EnemyManager::getPlayerPosition(const int number)
{
	return positiones_[number];
}

// �w�肵���I�u�W�F�N�g�Ƃ̋�����Ԃ��܂�
float EnemyManager::getLength(const Vector2 & otherPosition)
{
	auto length = otherPosition - enemyPosition_;
	return length.Length();
}

// �v���C���[�Ƃ̋�����Ԃ��܂�
float EnemyManager::getPlayerLength(const int number)
{
	// �v���C���[�̈ʒu���擾
	return getLength(positiones_[number]);
}

// �G����v���C���[�ɐL�΂����x�N�g����Ԃ��܂�
Vector2 EnemyManager::getPlayerVector(const int number)
{
	auto vector = positiones_[number] - enemyPosition_;
	return Vector2(std::abs(vector.x), std::abs(vector.y));
}

// �w�肵���I�u�W�F�N�g�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
Vector2 EnemyManager::getDirection(const Vector2& otherPosition)
{
	// �����̌v�Z
	auto distance = enemyPosition_ - otherPosition;
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

// �v���C���[�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
Vector2 EnemyManager::getPlayerDirection(const int number)
{
	return getDirection(positiones_[number]);
}

// �w�肵���I�u�W�F�N�g�Ƃ̕������A���K�����ꂽ�x�N�g���Ŏ擾���܂�
Vector2 EnemyManager::getNormalizeDirection(const Vector2 & otherPosition)
{
	// �����̌v�Z
	auto distance = otherPosition - enemyPosition_;
	return Vector2::Normalize(distance);
}

// �v���C���[�Ƃ̕����𐳋K�����ꂽ�x�N�g���Ŏ擾���܂�
Vector2 EnemyManager::getPlayerNormalizeDirection(const int number)
{
	// �����̌v�Z
	return getNormalizeDirection(positiones_[number]);
}

//�@�G���g�ƃv���C���[�̈ʒu�����܂�
void EnemyManager::setEMPosition(
	const Vector2& enemyPosition,  
	const Vector2& direction)
{
	enemyPosition_ = enemyPosition;
	enemyDirection_ = direction;
}

// ���̎x�_�̈ʒu�擾
Vector2 EnemyManager::getThreadPoint()
{
	return threadPosition_;
}

// �{���I�u�W�F�N�g�̐ݒ�
void EnemyManager::addFSP(FloorSearchPoint * fsp)
{
	wspContainer_.push_back(fsp);
}

// �ǂɉ�����������
Vector2 EnemyManager::getWallDirection()
{
	eachWSPObj();
	// �S���̒l�Ɋ���U���Ă���Εs�v
	for (auto i = wspDirectionMap_.begin(); i != wspDirectionMap_.end(); i++) {
		// ���������߂���ꍇ���A�q�b�g����1�̏ꍇ�@����
		// �}�b�v�ɓ���Ă���l�Ɠ���Ȃ�΁A���������߂�
		if (isDirecion() && i->first == wspResult_) {
			animaDirection_ = animaDirectionMap_[wspResult_];
			wsDirection_ = wspDirectionMap_[wspResult_];
			// ���������߂���false�ɂ���
			isDirection_ = false;
			break;
		}
	}
	// �ߋ��̃J�E���g���X�V
	wCollidePastCount_ = wCollideCount_;
	return wsDirection_;
}

// �ǈړ����̃A�j���[�V�����̕������擾���܂�
Vector2 EnemyManager::getWallAnimaDirection()
{
	return animaDirection_;
}

void EnemyManager::setIsDirection(bool isDirection)
{
	isDirection_ = isDirection;
}

int EnemyManager::eachWSPObj()
{
	wspResult_ = 0;
	wCollideCount_ = 0;
	for (int i = 0; i != wspContainer_.size(); i++) {
		// �������Ă���Ȃ�A�R���e�i�̒l�ƃq�b�g�������Z����
		if (wspContainer_[i]->isGround()) {
			wspResult_ += primeContainer_[i];
			wspResult_ += 1;
			wCollideCount_ += 1;
		}
	}
	// �i�s�����ɂ���āA�l�����Z����(2��)
	if (wsDirection_.x != 0)
		wspResult_ += 10;
	else if (wsDirection_.y != 0)
		wspResult_ += 20;

	return wspResult_;
}

FloorSearchPoint* EnemyManager::getWSPObj(const int number)
{
	return wspContainer_[number];
}

bool EnemyManager::isDirecion()
{
	// �J�E���g������Ȃ�Afalse��Ԃ�
	if (wCollidePastCount_ == wCollideCount_) 
		return false;
	return true;
}

// �ǈړ��̕�����ǉ����܂�
void EnemyManager::addWSPDirection(const Vector2 & direction)
{
	// map�ɒǉ�
	// 1�̂�(�l��) 2 5 13 19
	// X �Ɉړ��ʂ�����ꍇ
	wspDirectionMap_[211] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[511] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[1311] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[1911] = Vector2(0.0f, 1.0f);
	// Y �Ɉړ��ʂ�����ꍇ
	wspDirectionMap_[221] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[521] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[1321] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[1921] = Vector2(1.0f, 0.0f);
	// 1�̂�(�㉺���E) 3 7 11 17
	wspDirectionMap_[311] = Vector2(direction.x, 0.0f);
	wspDirectionMap_[721] = Vector2(0.0f, -direction.y);
	wspDirectionMap_[1121] = Vector2(0.0f, direction.y);
	wspDirectionMap_[1711] = Vector2(-direction.x, 0.0f);
	// 2������
	/*wspDirectionMap_[812] = Vector2(wsDirection_.x, 0.0f);
	wspDirectionMap_[822] = Vector2(wsDirection_.x, 0.0f);*/
	/*wspDirectionMap_[812] = Vector2(direction.x, 0.0f);
	wspDirectionMap_[822] = Vector2(direction.x, 0.0f);*/
	// 3������(��) 10 22 35 49
	// X�Ɉړ��ʂ�����
	wspDirectionMap_[1013] = Vector2(-direction.x, 0.0f);
	wspDirectionMap_[2213] = Vector2(0.0f, direction.y);
	wspDirectionMap_[3513] = Vector2(0.0f, -direction.y);
	wspDirectionMap_[4913] = Vector2(direction.x, 0.0f);
	// Y�Ɉړ��ʂ�����
	wspDirectionMap_[1023] = Vector2(-direction.x, 0.0f);
	wspDirectionMap_[2223] = Vector2(0.0f, direction.y);
	wspDirectionMap_[3523] = Vector2(0.0f, -direction.y);
	wspDirectionMap_[4923] = Vector2(direction.x, 0.0f);
	// 3������(���̋ߕ�) 12 19 27 47
	// X �Ɉړ��ʂ�����ꍇ
	wspDirectionMap_[1213] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[1913] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[2713] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[4713] = Vector2(0.0f, -1.0f);
	// Y �Ɉړ��ʂ�����ꍇ
	wspDirectionMap_[1223] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[1923] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[2723] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[4723] = Vector2(-1.0f, 0.0f);
	// 3��(�l���̑g�ݍ��킹)������ 20 28 34 37
	// X �Ɉړ��ʂ�����ꍇ
	wspDirectionMap_[2013] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[2813] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[3413] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[3713] = Vector2(0.0f, -1.0f);
	// Y �Ɉړ��ʂ�����ꍇ
	wspDirectionMap_[2023] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[2823] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[3423] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[3723] = Vector2(-1.0f, 0.0f);
	// 4������(��) (0135) (0356) (2147) (2467) 
	// X �Ɉړ��ʂ�����ꍇ
	wspDirectionMap_[2514] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[3814] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[3914] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[5214] = Vector2(0.0f, -1.0f);
	// Y �Ɉړ��ʂ�����ꍇ
	wspDirectionMap_[2524] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[3824] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[3924] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[5224] = Vector2(-1.0f, 0.0f);
	// 5�_������(��) 30 40 58 65
	// X �Ɉړ��ʂ�����ꍇ
	wspDirectionMap_[3015] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[4015] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[5815] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[6515] = Vector2(0.0f, -1.0f);
	//wspDirectionMap_[5515] = Vector2(0.0f, -1.0f);
	/*wspDirectionMap_[5515] = Vector2(0.0f, direction.y);*/
	// Y �Ɉړ��ʂ�����ꍇ
	wspDirectionMap_[3025] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[4025] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[5825] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[6525] = Vector2(-1.0f, 0.0f);
	// 1�̂ݓ�����Ȃ� 74 70 66 60
	wspDirectionMap_[7417] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[7017] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[6617] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[6017] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[7427] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[7027] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[6627] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[6027] = Vector2(0.0f, 1.0f);
	// �S���������Ă���
	//wspDirectionMap_[7718] = Vector2::Zero;
	//wspDirectionMap_[7728] = Vector2::Zero;

	// �A�j���[�V�����̕���
	animaDirectionMap_[211] = Vector2(0.0f, -1.0f);
	animaDirectionMap_[511] = Vector2(0.0f, 1.0f);
	animaDirectionMap_[1311] = Vector2(0.0f, 1.0f);
	animaDirectionMap_[1911] = Vector2(0.0f, -1.0f);
	// Y �Ɉړ��ʂ�����ꍇ
	animaDirectionMap_[221] = Vector2(1.0f, 0.0f);
	animaDirectionMap_[521] = Vector2(-1.0f, 0.0f);
	animaDirectionMap_[1321] = Vector2(-1.0f, 0.0f);
	animaDirectionMap_[1921] = Vector2(1.0f, 0.0f);
	// 1�̂�(�㉺���E) 3 7 11 17
	animaDirectionMap_[311] = Vector2(direction.x, 0.0f);
	animaDirectionMap_[721] = Vector2(0.0f, -direction.y);
	animaDirectionMap_[1121] = Vector2(0.0f, direction.y);
	animaDirectionMap_[1711] = Vector2(-direction.x, 0.0f);
	// 3������(��) 10 22 35 49
	// X�Ɉړ��ʂ�����
	animaDirectionMap_[1013] = Vector2(direction.x, 0.0f);
	animaDirectionMap_[2213] = Vector2(0.0f, direction.y);
	animaDirectionMap_[3513] = Vector2(0.0f, direction.y);
	animaDirectionMap_[4913] = Vector2(direction.x, 0.0f);
	// Y�Ɉړ��ʂ�����
	animaDirectionMap_[1023] = Vector2(direction.x, 0.0f);
	animaDirectionMap_[2223] = Vector2(0.0f, direction.y);
	animaDirectionMap_[3523] = Vector2(0.0f, direction.y);
	animaDirectionMap_[4923] = Vector2(direction.x, 0.0f);
	// 3������(���̋ߕ�) 12 19 27 47
	// X �Ɉړ��ʂ�����ꍇ
	animaDirectionMap_[1213] = Vector2(0.0f, 1.0f);
	animaDirectionMap_[1913] = Vector2(0.0f, -1.0f);
	animaDirectionMap_[2713] = Vector2(0.0f, -1.0f);
	animaDirectionMap_[4713] = Vector2(0.0f, 1.0f);
	// Y �Ɉړ��ʂ�����ꍇ
	animaDirectionMap_[1223] = Vector2(-1.0f, 0.0f);
	animaDirectionMap_[1923] = Vector2(1.0f, 0.0f);
	animaDirectionMap_[2723] = Vector2(1.0f, 0.0f);
	animaDirectionMap_[4723] = Vector2(-1.0f, 0.0f);
	// 3��(�l���̑g�ݍ��킹)������ 20 28 34 37
	// X �Ɉړ��ʂ�����ꍇ
	animaDirectionMap_[2013] = Vector2(0.0f, 1.0f);
	animaDirectionMap_[2813] = Vector2(0.0f, -1.0f);
	animaDirectionMap_[3413] = Vector2(0.0f, -1.0f);
	animaDirectionMap_[3713] = Vector2(0.0f, 1.0f);
	// Y �Ɉړ��ʂ�����ꍇ
	animaDirectionMap_[2023] = Vector2(-1.0f, 0.0f);
	animaDirectionMap_[2823] = Vector2(1.0f, 0.0f);
	animaDirectionMap_[3423] = Vector2(1.0f, 0.0f);
	animaDirectionMap_[3723] = Vector2(-1.0f, 0.0f);
	// 4������(��) (0135) (0356) (2147) (2467) 
	// X �Ɉړ��ʂ�����ꍇ
	animaDirectionMap_[2514] = Vector2(0.0f, 1.0f);
	animaDirectionMap_[3814] = Vector2(0.0f, -1.0f);
	animaDirectionMap_[3914] = Vector2(0.0f, -1.0f);
	animaDirectionMap_[5214] = Vector2(0.0f, 1.0f);
	// Y �Ɉړ��ʂ�����ꍇ
	animaDirectionMap_[2524] = Vector2(-1.0f, 0.0f);
	animaDirectionMap_[3824] = Vector2(1.0f, 0.0f);
	animaDirectionMap_[3924] = Vector2(1.0f, 0.0f);
	animaDirectionMap_[5224] = Vector2(-1.0f, 0.0f);
	// 5�_������(��) 30 40 58 65
	// X �Ɉړ��ʂ�����ꍇ
	animaDirectionMap_[3015] = Vector2(0.0f, 1.0f);
	animaDirectionMap_[4015] = Vector2(0.0f, -1.0f);
	animaDirectionMap_[5815] = Vector2(0.0f, -1.0f);
	animaDirectionMap_[6515] = Vector2(0.0f, 1.0f);
	// Y �Ɉړ��ʂ�����ꍇ
	animaDirectionMap_[3025] = Vector2(-1.0f, 0.0f);
	animaDirectionMap_[4025] = Vector2(1.0f, 0.0f);
	animaDirectionMap_[5825] = Vector2(1.0f, 0.0f);
	animaDirectionMap_[6525] = Vector2(-1.0f, 0.0f);
	// 1�̂ݓ�����Ȃ� 74 70 66 60
	animaDirectionMap_[7417] = Vector2(0.0f, -1.0f);
	animaDirectionMap_[7017] = Vector2(-1.0f, 0.0f);
	animaDirectionMap_[6617] = Vector2(1.0f, 0.0f);
	animaDirectionMap_[6017] = Vector2(0.0f, 1.0f);
	animaDirectionMap_[7427] = Vector2(0.0f, -1.0f);
	animaDirectionMap_[7027] = Vector2(-1.0f, 0.0f);
	animaDirectionMap_[6627] = Vector2(1.0f, 0.0f);
	animaDirectionMap_[6027] = Vector2(0.0f, 1.0f);
}

// �v���C���[�̈ʒu��ݒ肵�܂�
void EnemyManager::setPlayerPosition(const int number, const Vector2& position)
{
	positiones_[number] = position;
	psObjs[number]->setPosition(enemyPosition_, position);
}

// �v���C���[�{���I�u�W�F�N�g�̒ǉ����s���܂�
void EnemyManager::setPSObj(const int number, const Vector2 & position)
{
	auto psObj = std::make_shared<PlayerSearchObj>(
		world_, position, positiones_[number]);
	world_->addActor(ActorGroup::EnemyBullet, psObj);
	psObjs[number] = psObj.get();
}

// �v���C���[�{���I�u�W�F�N�g�̎擾
PlayerSearchObj * EnemyManager::getPSObj(const int number)
{
	return psObjs[number];
}

// �������Ă���I�u�W�F�N�g�̍폜���s���܂�
void EnemyManager::deleteObj()
{
	for (auto i = psObjs.begin(); i != psObjs.end(); i++) {
		auto a = *i;
		a.second->dead();
		psObjs[i->first] = nullptr;
	}
	psObjs.clear();
}
