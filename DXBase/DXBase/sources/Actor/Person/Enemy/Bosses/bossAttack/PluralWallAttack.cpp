#include "PluralWallAttack.h"

PluralWallAttack::PluralWallAttack() : 
	WallAttack(nullptr, Vector2::Zero),
	aCount_(0),
	initACount_(aCount_),
	idelTimer_(0.0f)
{
}

PluralWallAttack::PluralWallAttack(IWorld* world, const Vector2 & position) :
	WallAttack(world, position),
	aCount_(1),
	initACount_(aCount_),
	idelTimer_(0.0f)
{
}

void PluralWallAttack::attack(float deltaTime)
{
	WallAttack::attack(deltaTime);

	// �W�����v��̑ҋ@��Ԃ��I�������A�ēx�W�����v�U��
	if (!isWallAttackEnd_) return;
	// �J�E���g�����炷
	flinchCount_--;
	//aCount_--;
	idelTimer_ += deltaTime;
	//jumpCount_ = min(0, jumpCount_);
	// �U���񐔂�0�Ȃ�U���I��
	// if (aCount_ == 0) 
	if (idelTimer_ <= 5.0f) return;
	if (flinchCount_ == 0) {
		isAttackEnd_ = true;
		return;
	}
	WallAttack::Refresh();
	idelTimer_ = 0.0f;
	// �܂��U���񐔂��c���Ă���Ȃ�A�U��
	isWallAttackEnd_ = false;
}

void PluralWallAttack::Refresh()
{
	WallAttack::Refresh();
	aCount_ = initACount_;
}
