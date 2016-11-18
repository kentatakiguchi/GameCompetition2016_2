#include "JumpAttack.h"

JumpAttack::JumpAttack() :
	BossAttack(Vector2::Zero),
	speed_(0.0f),
	degrees_(0.0f),
	jumpPower_(0.0f),
	recastTimer_(0.0f),
	initRecastTimer_(recastTimer_),
	isJump_(true),
	isJumpEnd_(true)
{
}

JumpAttack::JumpAttack(const Vector2& position) :
	BossAttack(position),
	speed_(2.0f),
	degrees_(60.0f),
	jumpPower_(15.0f), 
	recastTimer_(0.5f),
	initRecastTimer_(recastTimer_),
	isJump_(false),
	isJumpEnd_(false)
{
}

// �U��
void JumpAttack::attack(float deltaTime)
{
	// �W�����v�U�����ɏ��ɐڒn������A���L���X�g�Ɉڍs
	// ���ꂾ�ƁA2���ڈȍ~�̂Q��ڂ̃W�����v�̏I�����肪�����ɍs����B
	// ���ƂŒ���
	// if (isJump_ && isGround_)
	if (isJump_ && isGround_ && timer_ > 0.3f) {
		recastTimer_ -= deltaTime;
		// ���L���X�g���Ԃ� 0 �ɂȂ�����A�W�����v�U���I��
		if (recastTimer_ > 0.0f) return;
		isJump_ = false;
		isJumpEnd_ = true;
		timer_ = 0.0f;
		return;
	}
	// ���L���X�g��ԂłȂ���΃W�����v�U��
	if (recastTimer_ == initRecastTimer_)
		jump(deltaTime);
}

// �W�����v�U��
void JumpAttack::jump(float deltaTime)
{
	// �ړ�
	auto addPos = Vector2(
		-std::cos(degrees_) * speed_ * direction_.x * (deltaTime * 60.0f), 0.0f);
	// std::sin(degrees_) * -speed_);
	position_ += addPos;
	position_.y += (-jumpPower_ / 10 + timer_) * 9.8f * (deltaTime * 60.0f);
	// �W�����v������
	isJump_ = true;
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
	isJumpEnd_ = false;
	recastTimer_ = initRecastTimer_;
}
