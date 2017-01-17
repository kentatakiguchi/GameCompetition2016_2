#include "DysonAttack.h"
#include "../../Rock.h"
#include "../Tornado.h"
#include "../../../../../ResourceLoader/ResourceLoader.h"
#include <random>	// C++11�̋@�\

DysonAttack::DysonAttack() : 
	BossAttack(nullptr, Vector2::Zero),
	windSE_(0),
	addAngle_(0.0f),
	isRockCreate_(true),
	tornadoObj_(nullptr),
	state_(State::Attack)
{}

DysonAttack::DysonAttack(IWorld * world, const Vector2 & position) :
	BossAttack(world, position),
	windSE_(ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_WIND)),
	addAngle_(1.0f),
	isRockCreate_(false),
	tornadoObj_(nullptr),
	state_(State::Attack)
{
	angle_ = 70.0f;
	animeNum_ = BREATH_NUMBER;
}

void DysonAttack::attack(float deltaTime)
{
	switch (state_)
	{
	case State::Attack: dysonAttack(deltaTime); break;
	case State::Flinch: flinch(deltaTime); break;
	case State::Fatigue: fatigue(deltaTime); break;
	}
}

// �U�����
void DysonAttack::dysonAttack(float deltaTime)
{
	// �����Ȃ���ԂȂ�A�Ђ�ݏ�ԂɑJ��
	if (!isMove_) {
		changeState(State::Flinch, BREATH_DYSFUNCTION_NUMBER);
		isAnimaReverse_ = false;
		isAnimaLoop_ = false;
		if (tornadoObj_ != nullptr) {
			tornadoObj_->dead();
			tornadoObj_ = nullptr;
			// SE�̒�~
			StopSoundMem(windSE_);
		}
		return;
	}
	// ��̐���
	if ((int)(timer_ * 10) % 10 == 0 && !isRockCreate_) {
		// �����̎擾
		std::random_device random;
		// �����Z���k�c�C�X�^�[�@ ��Œ��ׂ�
		// ����Seed�l��n��
		std::mt19937 mt(random());
		// �͈͂̎w��(int�^)
		int size = static_cast<int>(CHIPSIZE);
		std::uniform_int_distribution<> aSecond(size * 2, size * 18);
		// ��̐���
		for (int i = 0; i != 3; i++) {
			// X�̐����ʒu������
			world_->addActor(ActorGroup::Enemy,
				std::make_shared<Rock>(world_, Vector2((float)aSecond(mt), 200.0f)));
		}
		isRockCreate_ = true;
	}
	else if ((int)(timer_ * 10) % 10 == 1)
		isRockCreate_ = false;
	// �{�X�̗����U��(��)
	if (tornadoObj_ == nullptr) {
		wsDirection_ = direction_;
		auto tornado = std::make_shared<Tornado>(
			world_, position_ + Vector2(40.0f *  direction_.x, -120.0f),
			Vector2(CHIPSIZE * 4, CHIPSIZE * 1));
		world_->addActor(ActorGroup::Enemy, tornado);
		tornadoObj_ = tornado.get();
		// SE�̍Đ�
		PlaySoundMem(windSE_, DX_PLAYTYPE_LOOP);
	}
	// �����I�u�W�F�N�g�̈ʒu�X�V
	if (tornadoObj_ != nullptr)
		tornadoObj_->position_ = position_ + Vector2(40.0f *  direction_.x, -120.0f);
	// �ǂɓ����������ɔ��]����
	if (isWspHit_ && isPrevWspHit_ != isWspHit_) {
		direction_.x *= -1;
		wsDirection_ = direction_;
		angle_ = 180 - angle_;
		addAngle_ *= -1;
	}
	// �p�x�����l�𒴂�����A���Z������ς���
	if (angle_ >= 90.0f + 30.0f || angle_ <= 90.0f - 30.0f) {
		addAngle_ *= -1;
		if (direction_.x < 0) {
			if (addAngle_ >= 0) {
				isAnimaReverse_ = false;
			}
			else {
				isAnimaReverse_ = true;
			}
		}
		else if (direction_.x >= 0) {
			if (addAngle_ < 0) {
				isAnimaReverse_ = false;
			}
			else {
				isAnimaReverse_ = true;
			}
		}
	}
	// �p�x�̉��Z
	angle_ += addAngle_ * (deltaTime * 60.0f);
	tornadoObj_->setAngle((int)angle_);
	isPrevWspHit_ = isWspHit_;

	position_.x += 4.0f * direction_.x * (deltaTime * 60.0f);

	// �f���^�^�C����0�ȉ��Ȃ�ASE���ꎞ��~����
	if (CheckSoundMem(windSE_) == 1 &&
		deltaTime <= 0) {
		StopSoundMem(windSE_);
	}
	else if (CheckSoundMem(windSE_) == 0 &&	deltaTime > 0) {
		// SE�̍Đ�(��~�����ӏ�����Đ�)
		PlaySoundMem(windSE_, DX_PLAYTYPE_LOOP, false);
	}

	// ��莞�Ԍo�߂ōU���I��
	if (timer_ <= 7.0f) return;
	tornadoObj_->dead();
	// SE�̒�~
	StopSoundMem(windSE_);
	isAttackEnd_ = true;
}

// ���ݏ��
void DysonAttack::flinch(float deltaTime)
{
	isAnimaLoop_ = false;
	// �v���C���[���Ȃ����̂ɓ������Ă��Ȃ��Ȃ�A��J��ԂɑJ��
	if (isMove_) {
		changeState(State::Fatigue, BREATH_LESS_NUMBER);
		isAnimaLoop_ = true;
		return;
	}
	// �G�ꑱ���Ă���Ԃň�莞�Ԍo�߂�����Ђ��
	if (timer_ <= 1.5f) return;
	isFlinch_ = true;
}

// ��J���
void DysonAttack::fatigue(float deltaTime)
{
	//isAnimaLoop_ = true;
	if (timer_ <= 5.0f) return;
	// �U����ԂɑJ��
	changeState(State::Attack, BREATH_NUMBER);
}

// ��Ԃ̕ύX���s���܂�
void DysonAttack::changeState(State state, int num)
{
	state_ = state;
	timer_ = 0.0f;
	animeNum_ = num;
}

void DysonAttack::Refresh()
{
	BossAttack::Refresh();
	isFlinch_ = false;
	tornadoObj_ = nullptr;
	// SE���Đ����Ȃ�A�~�߂�
	if (CheckSoundMem(windSE_) == 1)
		StopSoundMem(windSE_);
	changeState(State::Attack, BREATH_NUMBER);
	if (direction_.x >= 0)
		angle_ = 90.0f + 29.0f;
	else angle_ = 90.0f - 29.0f;
}
