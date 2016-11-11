#include "BossAttack.h"

BossAttack::BossAttack() : 
	timer_(0.0f),
	position_(Vector2::Zero)
{
}

BossAttack::BossAttack(const Vector2 & position) : 
	position_(position)
{
}

BossAttack::~BossAttack()
{
}

// �X�V
void BossAttack::update(float deltaTime)
{
	// �U��
	timer_ += deltaTime;
	attack(deltaTime);
}

// �U��(�f�t�H���g)
void BossAttack::attack(float deltaTime)
{

}

// �ړ������ʒu���擾���܂�
Vector2 BossAttack::getMovePosition()
{
	return Vector2();
}

// �U���s���̃��t���b�V�����s���܂�
void BossAttack::Refresh()
{
	timer_ = 0.0f;
	isAttackEnd_ = false;
}

// �U�����I����������Ԃ��܂�
bool BossAttack::isAttackEnd()
{
	return isAttackEnd_;
}
