#include "WallAttack.h"
#include "../Effect/ImportEffects.h"

WallAttack::WallAttack() :
	BossAttack(nullptr, Vector2::Zero),
	count_(0),
	aSecond_(0),
	createCount_(0),
	speed_(0.0f),
	isWallAttackEnd_(true),
	state_(State::FloorSearch),
	prevPlayerDistance_(Vector2::Zero)
{}

WallAttack::WallAttack(IWorld* world, const Vector2 & position) :
	BossAttack(world, position),
	count_(0),
	aSecond_(5),
	speed_(4.0f),
	isWallAttackEnd_(false),
	state_(State::WallMove),
	prevPlayerDistance_(Vector2::One)
{
	moveTimes_.clear();
	moveDirections_.clear();
	// �ǈړ����ԃR���e�i�ɒǉ�
	moveTimes_.push_back(5);
	moveTimes_.push_back(10);
	moveTimes_.push_back(3);
	moveTimes_.push_back(8);
	moveTimes_.push_back(1);
	moveTimes_.push_back(6);
	// �����R���e�i�ɒǉ�
	moveDirections_.push_back(0.0f);
	moveDirections_.push_back(-1.0f);
	moveDirections_.push_back(0.0f);
	moveDirections_.push_back(1.0f);
	moveDirections_.push_back(0.0f);
	// �����̐ݒ�
	auto direction = Vector2(
		moveDirections_[(count_ + 1) % 4],
		moveDirections_[count_ % 4]
		);
	direction_ = direction;
	wsDirection_ = direction_;
	animeNum_ = WALLATTACK_DASH_NUMBER;
}

void WallAttack::attack(float deltaTime)
{
	switch (state_)
	{
	case State::FloorSearch: floorSearch(deltaTime); break;
	case State::FloorGetOff: floorGetOff(deltaTime); break;
	case State::WallMove: wallMove(deltaTime); break;
	case State::WallAttackMove: wallAttackMove(deltaTime); break;
	}
}

void WallAttack::Refresh()
{
	BossAttack::Refresh();
	flinchCount_ = 0;
	createCount_ = 0;
	isWallAttackEnd_ = false;
	changeState(State::FloorSearch, WALLATTACK_DASH_NUMBER);
	count_ = 0;
	auto direction = Vector2(
		moveDirections_[(count_ + 1) % 4],
		moveDirections_[count_ % 4]
		);
	direction_ = direction;
	wsDirection_ = direction_;
}

// ���{����Ԃł�
void WallAttack::floorSearch(float deltaTime)
{
	//// �����Ă��鏰�ɐڒn���Ă���΁A�����~���	
	//if (floorName_ == "BossAreaFloor") {
	//	// �v�Z���ďo�Ă��������������Ĉړ�����
	//	auto direction = 1.0f;
	//	// �X�e�[�W�̑傫���̔������ȉ��Ȃ�A���Ɉړ�����
	//	if (position_.x <= CHIPSIZE * 20 / 2)
	//		direction = -1.0f;
	//	direction_.x = direction;
	//	wsDirection_.x = direction_.x;
	//	changeState(State::FloorGetOff, WAIT_NUMBER);
	//}
	//// �����łȂ���΁A�ǈړ��ɑJ��
	//if (floorName_ == "MovelessFloor") {
	//	changeState(State::WallMove, WALLATTACK_DASH_NUMBER);
	//	setAttackSecond();
	//}
	changeState(State::WallMove, WALLATTACK_DASH_NUMBER);
	setAttackSecond();
}

// ������~����Ԃł�
void WallAttack::floorGetOff(float deltaTime)
{
	// �{�X�̈ʒu�Ƌ󒆂̏��̒��S�ʒu���Q�Ƃ��āA�n�ʂɖ߂�
	position_.x += speed_ * direction_.x * (deltaTime * 60.0f);
	// �d��
	if(!isGround_)
		position_.y += 9.8f * (deltaTime* 60.0f);
	// �n�ʂɐڒn������ǈړ���ԂɑJ��
	if (floorName_ == "MovelessFloor") {
		changeState(State::WallMove, WALLATTACK_DASH_NUMBER);
		setAttackSecond();
	}
}

// �ǈړ���Ԃł�
void WallAttack::wallMove(float deltaTime)
{
	isUseGravity_ = false;
	isAttackStart_ = true;
	isBodyHit_ = false;
	isAttackHit_ = false;
	animeNum_ = WALLATTACK_DASH_NUMBER;
	// ���v����ňړ�
	auto speed = speed_ * 3.0f;
	if (isWspHit_ && isPrevWspHit_ != isWspHit_) count_++;
	isPrevWspHit_ = isWspHit_;
	auto direction = Vector2(
		moveDirections_[(count_ + 1) % 4],
		moveDirections_[(int)(count_ % 4)]
		);
	direction_ = direction;
	wsDirection_ = direction_;
	animeAngle_ = (float)((count_ * 90) % 360);
	auto pos = direction * speed * (deltaTime * 60.0f);
	position_ += pos;
	// �U���ԋ߂ɃA�j���[�V������ύX����
	if (timer_ >= aSecond_ - 0.2f) {
		animeNum_ = WALLATTACK_DASHJUMP_STOP_NUMBER;
		isAnimaLoop_ = false;
	}
	// ��莞�Ԍo�߂ŁA�ǍU���ɑJ��
	if (timer_ >= aSecond_) {
		changeState(State::WallAttackMove, WALLATTACK_DASHJUMP_NUMBER);
		isAnimaLoop_ = false;
		prevPlayerDistance_ = pNormDirection_;
		// �v���C���[�̕���������
		direction = prevPlayerDistance_;
		auto angle = std::atan2(direction.y, direction.x) * 180.0f / MathHelper::Pi;
		animeAngle_ = angle + 90.0f;
		direction_ = direction;
		wsDirection_ = direction;
		// SE�̍Đ�
		PlaySoundMem(
			ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_WALLATTACK),
			DX_PLAYTYPE_BACK);
	}
}

// �ǍU����Ԃł�
void WallAttack::wallAttackMove(float deltaTime)
{
	auto speed = speed_ * 7.0f;
	isAnimaLoop_ = false;
	// �v���C���[�̋����ʒu�Ɍ������Ĕ��
	position_ += prevPlayerDistance_ * speed * (deltaTime * 60.0f);
	// �ی�(�����ɏՓ˂������ƂɂȂ�)
	if (timer_ <= 0.2f) return;
	if (floorName_ == "BossAreaFloor" || floorName_ == "MovelessFloor" ||
		floorName_ == "Door") {
		isAnimaLoop_ = true;
		isBodyHit_ = true;
		isAttackHit_ = true;
		isWallAttackEnd_ = true;
		isAttackEnd_ = true;
	}
}

// �ǈړ����鎞�Ԃ����肵�܂�
void WallAttack::setAttackSecond()
{
	// �R���e�i�̗v�f���̎w��
	int aCount = 0;
	auto hp = (hp_ % 100) + 1;
	flinchCount_ = 1;
	// �̗͂�70�����̏ꍇ�A�J�E���g�̒l��ς���
	if (hp < 70 && hp >= 30) {
		aCount = 2;
		flinchCount_ = 2;
	}
	else if (hp < 30) {
		aCount = 4;
		flinchCount_ = 3;
	}
	// �ړ��b��������
	aSecond_ = getRandomInt(moveTimes_[aCount], moveTimes_[aCount + 1]);
}

// ��Ԃ̕ύX���s���܂�
void WallAttack::changeState(State state, int number)
{
	state_ = state;
	animeNum_ = number;
	timer_ = 0.0f;
}
