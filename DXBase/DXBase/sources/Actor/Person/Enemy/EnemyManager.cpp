#include "EnemyManager.h"

EnemyManager::EnemyManager() : 
	timer_(0.0f),
	deltaTimer_(0.0f),
	boxMoveCount(0.0f),
	enemyPosition_(Vector3(0.0f, 0.0f, 0.0f)),
	playerPosition_(Vector3(0.0f, 0.0f,0.0f))
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
	auto posi = enemyPosition_;
	posi = Vector3(
		boxMoveConteiner_[(int)boxMoveCount % 4] * 3.0f,
		boxMoveConteiner_[((int)boxMoveCount + 3) % 4] * 1.0f,
		0.0f
		);
	//if((int)timer_ %  1 * 60.0f >= 0)
	return posi;
}

// �ǂɉ������������i�܂��j
Vector3 EnemyManager::wallMove()
{
	// �G�̎l���ɓ����蔻��̂���I�u�W�F�N�g��z�u
	// ���������I�u�W�F�N�g�̖��O�Ȃǂ��Q�Ƃ��āA�����̒l�����肷��
	return Vector3();
}

// �R������铮����
Vector3 EnemyManager::cliffMove()
{
	// �G�̑O�������ɓ����蔻��̂���I�u�W�F�N�g��z�u
	// �����Ă�������ɂ���āA�I�u�W�F�N�g�̈ʒu��ς���
	return Vector3();
}

// �����g����������
Vector3 EnemyManager::threadMove()
{
	return Vector3();
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
	else if (distance.x > 0)
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
