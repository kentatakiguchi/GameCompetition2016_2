#include "EnemyManager.h"

EnemyManager::EnemyManager(const Vector3 position) :
	distance_(1),
	timer_(0.0f),
	deltaTimer_(0.0f),
	boxMoveCount(0.0f),
	enemyPosition_(position),
	playerPosition_(Vector3::Zero),
	threadPosition_(position + Vector3::Left * 100.0f),
	threadLength_(Vector3::Distance(enemyPosition_, threadPosition_)),
	rotate_(0.0f),
	rotateSpeed_(10.0f),
	threadGravity_(0.5f)
{
	boxMoveConteiner_.push_back(0);
	boxMoveConteiner_.push_back(1);
	boxMoveConteiner_.push_back(0);
	boxMoveConteiner_.push_back(-1);
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
Vector3 EnemyManager::boxMove()
{
	boxMoveCount += deltaTimer_ / 2.0f;
	auto direction = enemyPosition_;
	direction = Vector3(
		boxMoveConteiner_[(int)boxMoveCount % 4] * 3.0f,
		boxMoveConteiner_[((int)boxMoveCount + 3) % 4] * 1.0f,
		0.0f
		);
	//if((int)timer_ %  1 * 60.0f >= 0)
	return direction;
}

// �ǂɉ������������i�܂��j
Vector3 EnemyManager::wallMove()
{
	auto directionX = 0;
	auto directionY = 0;
	auto count = 1;
	// X
	if (count == 1 || count == 4)
		directionX = 1;
	// Y
	if (count == 2 || count == 3)
		directionY = 1;

	if (count == 4 && (count == 2 || count == 3))
		directionY = 1;
	// �G�̎l���ɓ����蔻��̂���I�u�W�F�N�g��z�u
	// ���������I�u�W�F�N�g�̖��O�Ȃǂ��Q�Ƃ��āA�����̒l�����肷��
	return Vector3();
}

// �R������铮����
Vector3 EnemyManager::cliffMove(bool isFloor)
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
Vector3 EnemyManager::threadMove()
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
		threadPosition_ = enemyPosition_ + Vector3::Left * 100.0f;
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

	return Vector3(px, py, 0.0f);
}

// �v���C���[�Ƃ̋�����Ԃ��܂�
float EnemyManager::getPlayerLength()
{
	// �v���C���[�̈ʒu���擾
	Vector2 vec2PlayerPosition = Vector2(playerPosition_.x, playerPosition_.y);
	Vector2 vec2EnemyPosition = Vector2(enemyPosition_.x, enemyPosition_.y);
	Vector2 length = vec2PlayerPosition - vec2EnemyPosition;
	return length.Length();
}

// �v���C���[�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
Vector2 EnemyManager::getPlayerDirection()
{
	// �����̌v�Z
	auto distance = enemyPosition_ - playerPosition_;
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

// �v���C���[�Ƃ̕����𐳋K�����ꂽ�x�N�g���Ŏ擾���܂�
Vector3 EnemyManager::getPlayerNormalizeDirection()
{
	// �����̌v�Z
	auto distance = enemyPosition_ - playerPosition_;
	//// �ϊ�
	//auto nomaDistance = Vector2(distance.x, distance.y);
	//// ���K��
	//nomaDistance = nomaDistance.Normalize(nomaDistance);
	//auto distance3 = Vector3(nomaDistance.x, nomaDistance.y, 0.0f);
	distance = distance.Normalize(distance);
	return distance;
}

//�@�G���g�ƃv���C���[�̈ʒu�����܂�
void EnemyManager::setEMPosition(const Vector3& enemyPosition, const Vector3& playerPosition)
{
	enemyPosition_ = enemyPosition;
	playerPosition_ = playerPosition;
}

// ���̎x�_�̈ʒu�擾
Vector3 EnemyManager::getThreadPoint()
{
	return threadPosition_;
}

// �{���I�u�W�F�N�g�̐ݒ�
void EnemyManager::addFSP(FloorSearchPoint * fsp)
{
	fspContainer_.push_back(fsp);
}

// �ǂɉ�����������
Vector3 EnemyManager::getWallDirection()
{
	return Vector3();
}
