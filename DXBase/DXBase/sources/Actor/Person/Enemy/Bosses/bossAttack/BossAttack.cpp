#include "BossAttack.h"

BossAttack::BossAttack() : 
	timer_(0.0f),
	isAttackEnd_(true),
	isGround_(false),
	isBottom_(false),
	position_(Vector2::Zero),
	direction_(Vector2::Zero)
{
}

BossAttack::BossAttack(const Vector2 & position) : 
	timer_(0.0f),
	isAttackEnd_(false),
	isGround_(false),
	position_(position),
	direction_(Vector2::One)
{
}

BossAttack::~BossAttack()
{
}

// 更新
void BossAttack::update(float deltaTime)
{
	// 攻撃
	attack(deltaTime);
	// 時間の加算
	timer_ += deltaTime;
}

// 攻撃(デフォルト)
void BossAttack::attack(float deltaTime)
{
}

// 移動した位置を取得します
Vector2 BossAttack::getMovePosition()
{
	return position_;
}

// 攻撃行動のリフレッシュを行います
void BossAttack::Refresh()
{
	timer_ = 0.0f;
	isAttackEnd_ = false;
}

// 攻撃が終了したかを返します
bool BossAttack::isAttackEnd()
{
	return isAttackEnd_;
}

// 位置を設定します
void BossAttack::setPosition(const Vector2 & position)
{
	position_ = position;
}

// プレイヤーとの方向を設定します
void BossAttack::setDirection(const Vector2 & direction)
{
	direction_ = direction;
}

// 床に触れているかを設定します
void BossAttack::setIsGround(bool isGround)
{
	isGround_ = isGround;
}

// 壁の下側に当たったかを設定します
void BossAttack::setIsBottom(bool isBottom)
{
	isBottom_ = isBottom;
}
