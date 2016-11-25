#include "BossAttack.h"

BossAttack::BossAttack() : 
	timer_(0.0f),
	isAttackEnd_(true),
	isGround_(false),
	isBottom_(false),
	position_(Vector2::Zero),
	direction_(Vector2::Zero)
{
}

BossAttack::BossAttack(const Vector2 & position) : 
	timer_(0.0f),
	isAttackEnd_(false),
	isGround_(false),
	position_(position),
	direction_(Vector2::One)
{
}

BossAttack::~BossAttack()
{
}

// �X�V
void BossAttack::update(float deltaTime)
{
	// �U��
	attack(deltaTime);
	// ���Ԃ̉��Z
	timer_ += deltaTime;
}

// �U��(�f�t�H���g)
void BossAttack::attack(float deltaTime)
{
}

// �ړ������ʒu���擾���܂�
Vector2 BossAttack::getMovePosition()
{
	return position_;
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

// �ʒu��ݒ肵�܂�
void BossAttack::setPosition(const Vector2 & position)
{
	position_ = position;
}

// �v���C���[�Ƃ̕�����ݒ肵�܂�
void BossAttack::setDirection(const Vector2 & direction)
{
	direction_ = direction;
}

// ���ɐG��Ă��邩��ݒ肵�܂�
void BossAttack::setIsGround(bool isGround)
{
	isGround_ = isGround;
}

// �ǂ̉����ɓ�����������ݒ肵�܂�
void BossAttack::setIsBottom(bool isBottom)
{
	isBottom_ = isBottom;
}
