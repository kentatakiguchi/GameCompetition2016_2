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
{}

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
	otherName_(""),
	prevOtherName_(""),
	prevPlayerDistance_(Vector2::One)
{
	isBodyHit_ = false;
	isAttackHit_ = true;
	animeNum_ = JUMP_UP_NUMBER;
}

// 攻撃
void JumpAttack::attack(float deltaTime)
{

	if (collideObj_ != nullptr)
		otherName_ = collideObj_->getName();
	// 前回衝突したオブジェクトの名前を更新
	prevOtherName_ = otherName_;
	otherName_ = "";
	collideObj_ = nullptr;
	if (!isFirstJump_) {
		// 方向の設定
		auto distance = pPosition_ - position_;
		// 方向の値を代入
		if (distance.x < 0)
			pDirection_.x = -1;
		else if (distance.x > 0)
			pDirection_.x = 1;
		direction_ = pDirection_;
		isFirstJump_ = true;
	}
	// ジャンプ攻撃中に床に接地したら、リキャストに移行
	if (isJump_ && isGround_ && timer_ > 0.3f) {
		isIdel_ = true;
		isBodyHit_ = true;
		auto addPos = Vector2::Left * 40.0f;
		world_->addActor(ActorGroup::Effect,
			std::make_shared<BokoEffect>(world_, position_ + addPos));
		// 着地時に攻撃判定追加

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
		auto distance = pPosition_.x - position_.x;
		// 方向の値を代入
		if (distance < 0)
			pDirection_.x = -1;
		else if (distance >= 0)
			pDirection_.x = 1;
		direction_ = pDirection_;
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
	// 移動量が - なら上、+ なら下のアニメーションにする
	if (addPos.y <= 0) animeNum_ = JUMP_UP_NUMBER;
	else animeNum_ = JUMP_DOWN_NUMBER;
	// ジャンプをした
	isJump_ = true;
	isAttackStart_ = true;
	// プレイヤーに当たってもダメージなし
	isBodyHit_ = false;
}

// 攻撃行動のリフレッシュを行います
void JumpAttack::Refresh()
{
	BossAttack::Refresh();
	isJump_ = false;
	isFirstJump_ = false;
	isJumpEnd_ = false;
	isIdel_ = false;
	isBodyHit_ = true;
	jumpPower_ = initJumpPower_;
	recastTimer_ = initRecastTimer_;
	animeNum_ = JUMP_UP_NUMBER;
}
