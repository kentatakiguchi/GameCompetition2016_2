#include "BossAttack.h"

BossAttack::BossAttack() :
	hp_(0),
	flinchCount_(0),
	timer_(0.0f),
	animeAngle_(0.0f),
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
	isMove_(false),
	isFlinch_(true),
	isAnimaLoop_(false),
	isAnimaReverse_(false),
	position_(Vector2::Zero),
	direction_(Vector2::Zero),
	wsDirection_(Vector2::Zero),
	pPosition_(Vector2::Zero),
	pDirection_(Vector2::Zero),
	pNormDirection_(Vector2::Zero),
	animeNum_(WAIT_NUMBER),
	collideObj_(nullptr),
	mt_(std::mt19937())
{}

BossAttack::BossAttack(IWorld* world, const Vector2 & position) :
	hp_(100),
	flinchCount_(1),
	timer_(0.0f),
	angle_(0.0f),
	animeAngle_(0.0f),
	floorName_("a"),
	isAttackStart_(false),
	isAttackEnd_(false),
	isGround_(false),
	isUseGravity_(true),
	isWspHit_(false),
	isPrevWspHit_(false),
	isAttackHit_(false),
	isMove_(true),
	isFlinch_(false),
	isAnimaLoop_(true),
	isAnimaReverse_(false),
	position_(position),
	direction_(Vector2::Left),
	pPosition_(Vector2::One),
	pDirection_(Vector2::One),
	wsDirection_(Vector2::One),
	pNormDirection_(Vector2::One),
	world_(world),
	animeNum_(WAIT_NUMBER),
	collideObj_(nullptr),
	mt_(std::mt19937())
{
	// �����̎擾
	std::random_device random;
	// �����Z���k�c�C�X�^�[�@ ��Œ��ׂ�
	// ����Seed�l��n��
	std::mt19937 mt(random());
	mt_ = mt;
}

BossAttack::~BossAttack(){}

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
{}

// �ړ������ʒu���擾���܂�
Vector2 BossAttack::getMovePosition()
{
	return position_;
}

// �������擾���܂�
Vector2 BossAttack::getDirection()
{
	return direction_;
}

// �U���s���̃��t���b�V�����s���܂�
void BossAttack::Refresh()
{
	timer_ = 0.0f;
	animeAngle_ = 0.0f;
	isAttackStart_ = false;
	isAttackEnd_ = false;
	isUseGravity_ = true;
	isAnimaLoop_ = true;
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

// �ǈړ��̕������擾���܂�
Vector2 BossAttack::getMoveDirection()
{
	return wsDirection_;
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

// ���ނ���Ԃ��܂�
bool BossAttack::isFlinch()
{
	return isFlinch_;
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

// �Փ˂����I�u�W�F�N�g��ݒ肵�܂�
void BossAttack::setCollideObj(Actor & actor)
{
	collideObj_ = &actor;
}

// �A�j���[�V�����ԍ���Ԃ��܂�
int BossAttack::getAnimaNum()
{
	return animeNum_;
}

// �A�j���[�V�����̊p�x��Ԃ��܂�
int BossAttack::getAnimeAngle()
{
	return (int)animeAngle_;
}

// �A�j���[�V���������[�v���邩��Ԃ��܂�
bool BossAttack::isLoop()
{
	return isAnimaLoop_;
}

// �A�j���[�V�������t�Đ����邩��Ԃ��܂�
bool BossAttack::isReverse()
{
	return isAnimaReverse_;
}

// �����_���̒l���擾���܂�
int BossAttack::getRandomInt(int min, int max)
{
	// �͈͂̎w��(int�^)
	std::uniform_int_distribution<> value(min, max);
	return value(mt_);
}
