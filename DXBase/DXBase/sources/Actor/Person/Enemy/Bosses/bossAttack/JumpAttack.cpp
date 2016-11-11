#include "JumpAttack.h"

JumpAttack::JumpAttack() :
	BossAttack(Vector2::Zero),
	speed_(0.0f),
	degrees_(0.0f),
	jumpPower_(0.0f),
	recastTimer_(0.0f),
	initRecastTimer_(recastTimer_),
	isJumpEnd_(false)
{
}

JumpAttack::JumpAttack(const Vector2& position) :
	BossAttack(position),
	speed_(2.0f),
	degrees_(60.0f),
	jumpPower_(1.0f), 
	recastTimer_(1.0f),
	initRecastTimer_(recastTimer_),
	isJumpEnd_(false)
{
}

// 攻撃
void JumpAttack::attack(float deltaTime)
{
	// BossAttack::update(deltaTime);

	if (!isJumpEnd_ && position_.y < 500.0f)
		jump(deltaTime);
	else recastTimer_ -= deltaTime;

	

	// if (position_.y <= 500.0f) jumpCount_--;
	// position_.y += (-0.5f + stateTimer_) * GRAVITY_ * deltaTimer_;
}

// ジャンプ
void JumpAttack::jump(float deltaTime)
{
	auto addPos = Vector2(
		std::cos(degrees_) * speed_, 0.0f);
	// std::sin(degrees_) * -speed_);
	position_ += addPos;
	position_.y += (-jumpPower_ + timer_) * 9.8f * (deltaTime * 60.0f);
}

// 移動した位置を取得します
Vector2 JumpAttack::getMovePosition()
{
	return position_;
}

// 攻撃行動のリフレッシュを行います
void JumpAttack::Refresh()
{
	BossAttack::Refresh();
}
