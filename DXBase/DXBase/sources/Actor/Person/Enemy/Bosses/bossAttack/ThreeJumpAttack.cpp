#include "ThreeJumpAttack.h"

ThreeJumpAttack::ThreeJumpAttack() :
	JumpAttack(Vector2::Zero),
	jumpCount_(0),
	initJumpCount_(jumpCount_)
{
}

ThreeJumpAttack::ThreeJumpAttack(const Vector2 & position) : 
	JumpAttack(position),
	jumpCount_(3),
	initJumpCount_(jumpCount_)
{
}

void ThreeJumpAttack::attack(float deltaTime)
{
	// JumpAttack::attack(deltaTime);
	JumpAttack::attack(deltaTime);

	// �W�����v��̑ҋ@��Ԃ��I�������A�ēx�W�����v�U��
	if (!isJumpEnd_) return;
	// �J�E���g�����炷
	jumpCount_--;
	//jumpCount_ = min(0, jumpCount_);
	// �W�����v�񐔂�0�Ȃ�U���I��
	if (jumpCount_ == 0) {
		isAttackEnd_ = true;
		return;
	}
	// �܂��W�����v�񐔂�����Ȃ�A�ēx�W�����v
	isJump_ = false;
	isJumpEnd_ = false;
	recastTimer_ = initRecastTimer_;
}

void ThreeJumpAttack::Refresh()
{
	JumpAttack::Refresh();
	jumpCount_ = initJumpCount_;
}
