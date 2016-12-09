#include "BossAttack.h"

BossAttack::BossAttack() :
	hp_(0),
	flinchCount_(0),
	timer_(0.0f),
	floorName_(""),
	isAttackStart_(false),
	isAttackEnd_(true),
	isGround_(false),
	isBottom_(false),
	isUseGravity_(false),
	isWspHit_(false),
	isPrevWspHit_(false),
	isBodyHit_(true),
	isAttackHit_(true),
	isMove_(true),
	position_(Vector2::Zero),
	direction_(Vector2::Zero),
	pPosition_(Vector2::Zero),
	pDirection_(Vector2::Zero),
	pNormDirection_(Vector2::Zero)
{
}

BossAttack::BossAttack(const Vector2 & position) : 
	hp_(100),
	flinchCount_(3),
	timer_(0.0f),
	angle_(0.0f),
	floorName_("a"),
	isAttackStart_(false),
	isAttackEnd_(false),
	isGround_(false),
	isUseGravity_(true),
	isWspHit_(false),
	isPrevWspHit_(false),
	isAttackHit_(false),
	isMove_(false),
	position_(position),
	direction_(Vector2::Left),
	pPosition_(Vector2::One),
	pDirection_(Vector2::One),
	pNormDirection_(Vector2::One)
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
	floorName_ = "";
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
	isAttackStart_ = false;
	isAttackEnd_ = false;
	isUseGravity_ = true;
	//direction_ = Vector2::One;
}

// �U�����J�n��������Ԃ��܂�
bool BossAttack::isAttackStart()
{
	return isAttackStart_;
}

// �U�����I����������Ԃ��܂�
bool BossAttack::isAttackEnd()
{
	return isAttackEnd_;
}

// �{�X�̐S���̗̑͂�ݒ肵�܂�
void BossAttack::setHeartHP(const int hp)
{
	hp_ = hp;
}

// �ʒu��ݒ肵�܂�
void BossAttack::setPosition(const Vector2 & position)
{
	position_ = position;
}

// �v���C���[�̈ʒu��ݒ肵�܂�
void BossAttack::setPlayerPosition(const Vector2 & position)
{
	pPosition_ = position;
}

// �v���C���[�Ƃ̕�����ݒ肵�܂�
void BossAttack::setPlayerDirection(const Vector2 & direction)
{
	pDirection_ = direction;
}

// �v���C���[�Ƃ̐��K�����ꂽ������ݒ肵�܂�
void BossAttack::setPlayerNormalizeDirection(const Vector2 & direction)
{
	pNormDirection_ = direction;
}

// �Ǒ{���I�u�W�F�N�g��������������ݒ肵�܂�
void BossAttack::setIsWallHit(bool isHit)
{
	isWspHit_ = isHit;
}

//void BossAttack::setDirection(const Vector2 & direction)
//{
//
//}

// �ǈړ��̕������擾���܂�
Vector2 BossAttack::getMoveDirection()
{
	return direction_;
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

// �G��Ă��鏰�̖��O��ݒ肵�܂�
void BossAttack::setFloorName(const char * name)
{
	floorName_ = name;
}

// �U���\��Ԃ���ݒ肵�܂�
void BossAttack::setIsMove(bool isMove)
{
	isMove_ = isMove;
}

// �Ђ�݃J�E���g��Ԃ��܂�
int BossAttack::getFlinchCount()
{
	return flinchCount_;
}

// �p�x��Ԃ��܂�
float BossAttack::getAngle()
{
	return angle_;
}

// �d�͂��g�p���邩��Ԃ��܂�
bool BossAttack::isUseGravity()
{
	return isUseGravity_;
}

// �v���C���[�̍U���ɓ����邩��Ԃ��܂�
bool BossAttack::isBodyHit()
{
	return isBodyHit_;
}

// �v���C���[�ɓ����邩��Ԃ��܂�
bool BossAttack::isAttackHit()
{
	return isAttackHit_;
}
