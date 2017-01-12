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
{
}

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
	/*auto tornado = std::make_shared<Tornado>(
		world_, Vector2(-1000.0f, 0.0f), Vector2(CHIPSIZE * 10, 32.0f * 3));
	world_->addActor(ActorGroup::Enemy, tornado);
	tornadoObj_ = tornado.get();*/
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
		std::uniform_int_distribution<> aSecond(CHIPSIZE * 2, CHIPSIZE * 18);
		// ��̐���
		for (int i = 0; i != 3; i++) {
			// X�̐����ʒu������
			world_->addActor(ActorGroup::Enemy,
				std::make_shared<Rock>(world_, Vector2(aSecond(mt), 200.0f)));
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
		world_->addActor(ActorGroup::EnemyBullet, tornado);
		tornadoObj_ = tornado.get();
		// SE�̍Đ�
		PlaySoundMem(windSE_, DX_PLAYTYPE_LOOP);
	}
	// �����I�u�W�F�N�g�̈ʒu�X�V
	if (tornadoObj_ != nullptr)
		tornadoObj_->position_ = position_ + Vector2(40.0f *  direction_.x, -120.0f);

	if (isWspHit_ && isPrevWspHit_ != isWspHit_) {
		direction_.x *= -1;
		wsDirection_ = direction_;
	}
	// �p�x�����l�𒴂�����A���Z������ς���
	if (angle_ >= 90.0f + 40.0f || angle_ <= 90.0f - 40.0f)
		addAngle_ *= -1;
	// �p�x�̉��Z
	angle_ += addAngle_ * (deltaTime * 60.0f);
	tornadoObj_->setAngle(angle_);

	isPrevWspHit_ = isWspHit_;

	position_.x += 4.0f * direction_.x * (deltaTime * 60.0f);

	// ��莞�Ԍo�߂ōU���I��
	if (timer_ <= 7.0f) return;
	tornadoObj_->dead();
	// SE�̒�~
	StopSoundMem(windSE_);
	//tornadoObj_->initPosition();
	isAttackEnd_ = true;
}

// ���ݏ��
void DysonAttack::flinch(float deltaTime)
{
	//isFlinch_ = true;
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
	//isAttackEnd_ = true;
}

// ��J���
void DysonAttack::fatigue(float deltaTime)
{
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
	changeState(State::Attack, BREATH_NUMBER);
	//state_ = State::Attack;
	//animeNum_ = BossAnimationNumber::BREATH_NUMBER;
}
