#include "EnemyManager.h"
#include "FloorSearchPoint.h"

EnemyManager::EnemyManager(const Vector2 position) :
	distance_(1),
	timer_(0.0f),
	deltaTimer_(0.0f),
	boxMoveCount(0.0f),
	wspResult_(0.0f),
	enemyPosition_(position),
	playerPosition_(Vector2::Zero),
	threadPosition_(position + Vector2::Left * 100.0f),
	threadLength_(Vector2::Distance(enemyPosition_, threadPosition_)),
	enemyDirection_(Vector2::Zero),
	wsDirection_(1.0f, 0.0f),
	rotate_(0.0f),
	rotateSpeed_(10.0f),
	threadGravity_(0.5f)
{
	wallMoveConteiner_.push_back(0);
	wallMoveConteiner_.push_back(1);
	wallMoveConteiner_.push_back(0);
	wallMoveConteiner_.push_back(-1);
	// map�ɒǉ�


	// 1�̂ݓ�����Ȃ�
	wspDirectionMap_[74] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[70] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[66] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[60] = Vector2(0.0f, 1.0f);
	// �S���������Ă���
	wspDirectionMap_[77] = Vector2::Zero;
}

EnemyManager::~EnemyManager()
{
}

// �X�V
void EnemyManager::update(float deltaTime)
{
	deltaTimer_ = deltaTime;
	timer_ += deltaTimer_;
}

// ���̓�����(�ǂȂ�)
Vector2 EnemyManager::boxMove()
{
	boxMoveCount += deltaTimer_ / 2.0f;
	auto direction = enemyPosition_;
	direction = Vector2(
		wallMoveConteiner_[(int)boxMoveCount % 4] * 3.0f,
		wallMoveConteiner_[((int)boxMoveCount + 3) % 4] * 1.0f
		);
	//if((int)timer_ %  1 * 60.0f >= 0)
	return direction;
}

// �ǂɉ������������i�܂��j
Vector2 EnemyManager::wallMove()
{
	//auto direction = Vector2::Zero;
	// �ǂɓ������Ă��邩������
	//if (wspContainer_[0]->isGround()) {
	//	if (wspContainer_[1]->isGround()) {
	//		wsDirection_.x = 1;
	//		wsDirection_.y = 0;
	//	}
	//	else if (wspContainer_[3]->isGround()) {
	//		wsDirection_.x = 0;
	//		//wsDirection_.y = 1;
	//	}
	//	else if (!wspContainer_[1]->isGround()) {
	//		if (wsDirection_.x == 1)
	//			wsDirection_.y = -1;
	//		else if (wsDirection_.y == 1)
	//			wsDirection_.x = -1;
	//	}
	//}
	//else if (wspContainer_[5]->isGround()) {
	//	if (wsDirection_.x == 1)
	//		wsDirection_.y = 1;
	//	else if (wsDirection_.y == -1)
	//		wsDirection_.x = -1;
	//}

	/*else if (wspContainer_[2]->isGround()) {
		if (enemyDirection_.x == -1)
			direction.y = -1;
		else if (enemyDirection_.y == 1)
			direction.x = 1;
	}
	else if (wspContainer_[7]->isGround()) {
		if (enemyDirection_.x == -1)
			direction.y = 1;
		else if (enemyDirection_.y == -1)
			direction.x = 1;
	}*/

	// �G�̎l���ɓ����蔻��̂���I�u�W�F�N�g��z�u
	// ���������I�u�W�F�N�g�̖��O�Ȃǂ��Q�Ƃ��āA�����̒l�����肷��
	return wsDirection_;
}

// �R������铮����
Vector2 EnemyManager::cliffMove(bool isFloor)
{
	auto posi = enemyPosition_;
	// ���ɓ������Ă��Ȃ�����������]��
	/*if (!isFloor)
		distance_ *= -1;*/

	// ��
	/*boxMoveCount += deltaTimer_ / 2.0f;
	if ((int)boxMoveCount % 2 == 0)
		distance_ = -1;
	else distance_ = 1;*/
	// ��

	posi = posi.Left * distance_;
	// �G�̑O�������ɓ����蔻��̂���I�u�W�F�N�g��z�u
	// �����Ă�������ɂ���āA�I�u�W�F�N�g�̈ʒu��ς���
	return posi;
}

// �����g����������
Vector2 EnemyManager::threadMove()
{
	// ������̈ʒu
	auto radius = rotate_ * MathHelper::Pi / 180.0f;
	auto px = threadPosition_.x + MathHelper::Cos(radius) * threadLength_;
	auto py = threadPosition_.y + MathHelper::Sin(radius) * threadLength_;
	// �d�͈ړ�������������̈ʒu
	auto vx = px - threadPosition_.x;
	auto vy = py - threadPosition_.y;
	auto t = -(vy * threadGravity_) / (vx * vx + vy * vy);
	auto gx = px + t * vx;
	auto gy = py + threadGravity_ + t * vy;
	// ��̂�����̊p�x�̍�
	auto r = 
		MathHelper::ATan(
			gy - threadPosition_.y,
			gx - threadPosition_.x
			) * 180.0f / MathHelper::Pi;
	// �p�x�����p���x�ɉ��Z
	auto sub = r - rotate_;
	sub -= (int)sub / 360.0f * 360.0f;
	//// �l�������Ȃ��悤�ɕ␳
	//if (sub <= -180.0f) sub += 360.0f;
	//else if (sub > 180.0f) sub -= 360.0f;

	// �����ɂȂ�����|�C���g���ړ�
	if (rotate_ >= 100.0f * 100.0f) {
		threadPosition_ = enemyPosition_ + Vector2::Left * 100.0f;
		rotate_ = 0.0f;
	}
	rotateSpeed_ += sub;
	// �p�x�Ɋp���x�����Z
	rotate_ += rotateSpeed_;
	// �Čv�Z
	radius = rotate_ * MathHelper::Pi / 180.0f;
	px = threadPosition_.x + MathHelper::Cos(radius) * threadLength_;
	py = threadPosition_.y + MathHelper::Sin(radius) * threadLength_;
	// ���K��
	auto posi = Vector3(px, py, 0.0f);
	//auto nomaPosi = Vector3::Normalize(posi);

	return Vector2(px, py);
}

// �w�肵���I�u�W�F�N�g�Ƃ̋�����Ԃ��܂�
float EnemyManager::getLength(const Vector2 & otherPosition)
{
	auto length = otherPosition - enemyPosition_;
	return length.Length();
}

// �v���C���[�Ƃ̋�����Ԃ��܂�
float EnemyManager::getPlayerLength()
{
	// �v���C���[�̈ʒu���擾
	return getLength(playerPosition_);
}

// �w�肵���I�u�W�F�N�g�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
Vector2 EnemyManager::getDirection(const Vector2& otherPosition)
{
	// �����̌v�Z
	auto distance = enemyPosition_ - otherPosition;
	auto direction = Vector2().Zero;
	//auto direction = 1.0f;
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
Vector2 EnemyManager::getPlayerDirection()
{
	return getDirection(playerPosition_);
}

// �v���C���[�Ƃ̕����𐳋K�����ꂽ�x�N�g���Ŏ擾���܂�
Vector2 EnemyManager::getPlayerNormalizeDirection()
{
	// �����̌v�Z
	auto distance = enemyPosition_ - playerPosition_;
	return distance.Normalize(distance);
}

//�@�G���g�ƃv���C���[�̈ʒu�����܂�
void EnemyManager::setEMPosition(const Vector2& enemyPosition, const Vector2& playerPosition, const Vector2 direction)
{
	enemyPosition_ = enemyPosition;
	playerPosition_ = playerPosition;
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
	auto direction = Vector2::Zero;
	// 
	for (auto i = wspDirectionMap_.begin(); i != wspDirectionMap_.end(); i++) {
		// �}�b�v�ɓ���Ă���l�Ɠ���Ȃ�΁A���������߂�
		if (i->first == wspResult_)
			direction = wspDirectionMap_[wspResult_];
	}
	return direction;
	//return Vector2();
}

float EnemyManager::eachWSPObj()
{
	//for (auto i = wspDirectionMap_.begin(); i != wspDirectionMap_.end(); i++) {
	//	// �}�b�v�ɓ���Ă���l�Ɠ���Ȃ�΁A���������߂�
	//	if (i->first == wspResult_)
	//}
	return 0.0f;
}

FloorSearchPoint* EnemyManager::getWSPObj(const int number)
{
	return wspContainer_[number];
}
