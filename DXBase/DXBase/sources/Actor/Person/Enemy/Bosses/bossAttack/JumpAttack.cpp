#include "JumpAttack.h"

JumpAttack::JumpAttack() :
	BossAttack(Vector2::Zero),
	speed_(0.0f),
	degrees_(0.0f),
	jumpPower_(0.0f),
	initJumpPower_(jumpPower_),
	recastTimer_(0.0f),
	initRecastTimer_(recastTimer_),
	isJump_(true),
	isJumpEnd_(true),
	isIdel_(false),
	prevPlayerDistance_(Vector2::Zero)
{
}

JumpAttack::JumpAttack(const Vector2& position) :
	BossAttack(position),
	speed_(2.0f),
	degrees_(60.0f),
	jumpPower_(15.0f),
	initJumpPower_(jumpPower_),
	recastTimer_(0.5f),
	initRecastTimer_(recastTimer_),
	isJump_(false),
	isJumpEnd_(false),
	isIdel_(false),
	prevPlayerDistance_(Vector2::One)
{
}

// 攻撃
void JumpAttack::attack(float deltaTime)
{
	// ジャンプ攻撃中に床に接地したら、リキャストに移行
	// これだと、2巡目以降の２回目のジャンプの終了判定がすぐに行われる。
	// あとで直す
	// if (isJump_ && isGround_)
	if (isJump_ && isGround_ && timer_ > 0.3f) {
		isIdel_ = true;
		isBodyHit_ = true;
		//recastTimer_ -= deltaTime;
		//// リキャスト時間が 0 になったら、ジャンプ攻撃終了
		//if (recastTimer_ > 0.0f) return;
		//jumpPower_ = initJumpPower_;
		//isJump_ = false;
		//isJumpEnd_ = true;
		//timer_ = 0.0f;
		//return;
	}
	// ジャンプが終了したら、リキャストタイムを減算する
	if (isIdel_) {
		recastTimer_ -= deltaTime;
		// リキャスト時間が 0 になったら、ジャンプ攻撃終了
		if (recastTimer_ > 0.0f) return;
		jumpPower_ = initJumpPower_;
		isJump_ = false;
		isJumpEnd_ = true;
		timer_ = 0.0f;
		// 方向の設定
		auto distance = pPosition_ - position_;
		// 方向の値を代入
		// X
		if (distance.x < 0)
			pDirection_.x = -1;
		else if (distance.x > 0)
			pDirection_.x = 1;
		return;
	}
	// リキャスト状態でなければジャンプ攻撃
	if (recastTimer_ == initRecastTimer_)
		jump(deltaTime);
}

// ジャンプ攻撃
void JumpAttack::jump(float deltaTime)
{
	if (isBottom_)
		jumpPower_ = 0;
	// 移動
	auto addPos = Vector2(
		-std::cos(degrees_) * speed_ * pDirection_.x * (deltaTime * 60.0f),
		(-jumpPower_ / 10 + timer_) * 9.8f * (deltaTime * 60.0f));
	position_ += addPos;
	// std::sin(degrees_) * -speed_);
	//position_ += addPos;
	/*position_.y += (-jumpPower_ / 10 + timer_) * 9.8f * (deltaTime * 60.0f);*/
	// ジャンプをした
	isJump_ = true;
	isAttackStart_ = true;
	// プレイヤーに当たってもダメージなし
	isBodyHit_ = false;
}

//// 移動した位置を取得します
//Vector2 JumpAttack::getMovePosition()
//{
//	return position_;
//}

// 攻撃行動のリフレッシュを行います
void JumpAttack::Refresh()
{
	BossAttack::Refresh();
	isJump_ = false;
	isJumpEnd_ = false;
	isIdel_ = false;
	jumpPower_ = initJumpPower_;
	recastTimer_ = initRecastTimer_;
}
