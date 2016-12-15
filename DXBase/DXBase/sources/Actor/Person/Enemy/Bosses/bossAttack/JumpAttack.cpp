#include "JumpAttack.h"
#include "../Effect/ImportEffects.h"

JumpAttack::JumpAttack() :
	BossAttack(nullptr, Vector2::Zero),
	speed_(0.0f),
	degrees_(0.0f),
	jumpPower_(0.0f),
	initJumpPower_(jumpPower_),
	recastTimer_(0.0f),
	initRecastTimer_(recastTimer_),
	isJump_(true),
	isFirstJump_(true),
	isJumpEnd_(true),
	isIdel_(false),
	prevPlayerDistance_(Vector2::Zero)
{
}

JumpAttack::JumpAttack(IWorld* world, const Vector2& position) :
	BossAttack(world, position),
	speed_(2.0f),
	degrees_(60.0f),
	jumpPower_(15.0f),
	initJumpPower_(jumpPower_),
	recastTimer_(0.5f),
	initRecastTimer_(recastTimer_),
	isJump_(false),
	isFirstJump_(false),
	isJumpEnd_(false),
	isIdel_(false),
	prevPlayerDistance_(Vector2::One)
{
	animeNum_ = BossAnimationNumber::JUMP_UP_NUMBER;
}

// �U��
void JumpAttack::attack(float deltaTime)
{
	if (!isFirstJump_) {
		// �����̐ݒ�
		auto distance = pPosition_ - position_;
		// �����̒l����
		// X
		if (distance.x < 0)
			pDirection_.x = -1;
		else if (distance.x > 0)
			pDirection_.x = 1;
		direction_ = pDirection_;
		isFirstJump_ = true;
	}
	// �W�����v�U�����ɏ��ɐڒn������A���L���X�g�Ɉڍs
	// ���ꂾ�ƁA2���ڈȍ~�̂Q��ڂ̃W�����v�̏I�����肪�����ɍs����B
	// ���ƂŒ���
	// if (isJump_ && isGround_)
	if (isJump_ && isGround_ && timer_ > 0.3f) {
		isIdel_ = true;
		isBodyHit_ = true;
		auto addPos = Vector2::Left * 70;
		world_->addActor(ActorGroup::Effect,
			std::make_shared<BokoEffect>(world_, position_ + addPos));
		//recastTimer_ -= deltaTime;
		//// ���L���X�g���Ԃ� 0 �ɂȂ�����A�W�����v�U���I��
		//if (recastTimer_ > 0.0f) return;
		//jumpPower_ = initJumpPower_;
		//isJump_ = false;
		//isJumpEnd_ = true;
		//timer_ = 0.0f;
		//return;
	}
	// �W�����v���I��������A���L���X�g�^�C�������Z����
	if (isIdel_) {
		recastTimer_ -= deltaTime;
		// ���L���X�g���Ԃ� 0 �ɂȂ�����A�W�����v�U���I��
		if (recastTimer_ > 0.0f) return;
		jumpPower_ = initJumpPower_;
		isJump_ = false;
		isJumpEnd_ = true;
		timer_ = 0.0f;
		// �����̐ݒ�
		auto distance = pPosition_.x - position_.x;
		// �����̒l����
		// X
		if (distance < 0)
			pDirection_.x = -1;
		else if (distance >= 0)
			pDirection_.x = 1;
		direction_ = pDirection_;
		return;
	}
	// ���L���X�g��ԂłȂ���΃W�����v�U��
	if (recastTimer_ == initRecastTimer_)
		jump(deltaTime);
}

// �W�����v�U��
void JumpAttack::jump(float deltaTime)
{
	if (isBottom_)
		jumpPower_ = 0;
	// �ړ�
	auto addPos = Vector2(
		-std::cos(degrees_) * speed_ * pDirection_.x * (deltaTime * 60.0f),
		(-jumpPower_ / 10 + timer_) * 9.8f * (deltaTime * 60.0f));
	position_ += addPos;
	// �ړ��ʂ� - �Ȃ��A+ �Ȃ牺�̃A�j���[�V�����ɂ���
	if (addPos.y <= 0)
		animeNum_ = BossAnimationNumber::JUMP_UP_NUMBER;
	else
		animeNum_ = BossAnimationNumber::JUMP_DOWN_NUMBER;
	// std::sin(degrees_) * -speed_);
	//position_ += addPos;
	/*position_.y += (-jumpPower_ / 10 + timer_) * 9.8f * (deltaTime * 60.0f);*/
	// �W�����v������
	isJump_ = true;
	isAttackStart_ = true;
	// �v���C���[�ɓ������Ă��_���[�W�Ȃ�
	isBodyHit_ = false;
}

//// �ړ������ʒu���擾���܂�
//Vector2 JumpAttack::getMovePosition()
//{
//	return position_;
//}

// �U���s���̃��t���b�V�����s���܂�
void JumpAttack::Refresh()
{
	BossAttack::Refresh();
	isJump_ = false;
	isFirstJump_ = false;
	isJumpEnd_ = false;
	isIdel_ = false;
	jumpPower_ = initJumpPower_;
	recastTimer_ = initRecastTimer_;
	animeNum_ = BossAnimationNumber::JUMP_UP_NUMBER;
}
