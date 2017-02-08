#include "ThreeJumpAttack.h"

ThreeJumpAttack::ThreeJumpAttack() :
	JumpAttack(nullptr, Vector2::Zero),
	jumpCount_(0),
	initJumpCount_(jumpCount_)
{}

ThreeJumpAttack::ThreeJumpAttack(IWorld* world, const Vector2 & position) :
	JumpAttack(world, position),
	jumpCount_(3),
	initJumpCount_(jumpCount_)
{}

void ThreeJumpAttack::attack(float deltaTime)
{
	JumpAttack::attack(deltaTime);
	// �W�����v��̑ҋ@��Ԃ��I�������A�ēx�W�����v�U��
	if (!isJumpEnd_) return;
	// �J�E���g�����炷
	jumpCount_--;
	JumpAttack::Refresh();
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
	isAttackHit_ = true;
	jumpCount_ = initJumpCount_;
}
