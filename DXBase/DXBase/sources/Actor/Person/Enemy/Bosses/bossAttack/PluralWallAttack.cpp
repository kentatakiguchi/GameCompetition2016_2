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

	// ジャンプ後の待機状態が終わったら、再度ジャンプ攻撃
	if (!isWallAttackEnd_) return;
	// カウントを減らす
	flinchCount_--;
	//aCount_--;
	idelTimer_ += deltaTime;
	//jumpCount_ = min(0, jumpCount_);
	// 攻撃回数が0なら攻撃終了
	// if (aCount_ == 0) 
	if (idelTimer_ <= 5.0f) return;
	if (flinchCount_ == 0) {
		isAttackEnd_ = true;
		return;
	}
	WallAttack::Refresh();
	idelTimer_ = 0.0f;
	// まだ攻撃回数が残っているなら、攻撃
	isWallAttackEnd_ = false;
}

void PluralWallAttack::Refresh()
{
	WallAttack::Refresh();
	aCount_ = initACount_;
}
