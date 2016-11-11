#include "BossAttack.h"

BossAttack::BossAttack() : 
	timer_(0.0f),
	position_(Vector2::Zero)
{
}

BossAttack::BossAttack(const Vector2 & position) : 
	position_(position)
{
}

BossAttack::~BossAttack()
{
}

// 更新
void BossAttack::update(float deltaTime)
{
	// 攻撃
	timer_ += deltaTime;
	attack(deltaTime);
}

// 攻撃(デフォルト)
void BossAttack::attack(float deltaTime)
{

}

// 移動した位置を取得します
Vector2 BossAttack::getMovePosition()
{
	return Vector2();
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
