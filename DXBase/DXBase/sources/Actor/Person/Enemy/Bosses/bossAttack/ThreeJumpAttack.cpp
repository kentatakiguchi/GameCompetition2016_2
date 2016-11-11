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

	if (!isJumpEnd_ && position_.y < 500.0f)
		JumpAttack::attack(deltaTime);
	else recastTimer_ -= deltaTime;
	// ジャンプ後の待機状態が終わったら、再度ジャンプ攻撃
	if (recastTimer_ > 0.0f) return;
	if (jumpCount_ != 0)
		jumpCount_--;
	else isAttackEnd_ = true;
	recastTimer_ = initRecastTimer_;
}

void ThreeJumpAttack::Refresh()
{
	JumpAttack::Refresh();
	jumpCount_ = initJumpCount_;
	recastTimer_ = initRecastTimer_;
}
