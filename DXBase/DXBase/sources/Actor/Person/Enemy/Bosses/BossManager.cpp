#include "BossManager.h"
#include "bossAttack/BossAttack.h"
#include "bossAttack/importBossAttack.h"

BossManager::BossManager() : 
	attackNumber_(0)//,
	/*timer_(0.0f),
	isAttackEnd_(false),
	movePosition_(Vector2::Zero)*/
{
}

BossManager::BossManager(const Vector2 & position) : 
	attackNumber_(0)//,
	/*timer_(0.0f),
	isAttackEnd_(false),
	movePosition_(position)*/
{
	// bossAttackContainer_.clear();
	// 攻撃行動の追加
	// bossAttackContainer_.push_back(std::make_shared<JumpAttack>(position));
	bossAttackContainer_.push_back(std::make_shared<ThreeJumpAttack>(position));
}

// 指定した番号の攻撃行動を行います
void BossManager::attackMove(const float number, const float deltaTime)
{
	// 攻撃
	attackNumber_ = number;
	bossAttackContainer_[attackNumber_]->update(deltaTime);

	// 攻撃が終わったらの処理を、値を返したときに行う
}

// 行動のリフレッシュを行います
void BossManager::moveRefresh()
{
	/*timer_ = 0.0f;
	isAttackEnd_ = false;*/
}

// 行動によって移動した位置を返します
Vector2 BossManager::getMovePosition()
{
	return bossAttackContainer_[attackNumber_]->getMovePosition();
	// return bossAttackContainer_[attackNumber_].getMovePosition();

	// return jumpAttack_.getMovePosition();
	// return movePosition_;
}

// 攻撃が終了したかを返します
bool BossManager::isAttackEnd()
{
	return bossAttackContainer_[attackNumber_]->isAttackEnd();
}

Vector2 BossManager::getDirection(const Vector2 & otherPosition)
{
	// 方向の計算
	auto pos = bossAttackContainer_[attackNumber_]->getMovePosition();
	auto distance = pos - otherPosition;
	auto direction = Vector2().Zero;
	// 方向の値を代入
	// X
	if (distance.x < 0)
		direction.x = -1;
	else if (distance.x > 0)
		direction.x = 1;
	else direction.x = 0;
	// Y
	if (distance.y < 0)
		direction.y = 1;
	else if (distance.y > 0)
		direction.y = -1;
	else direction.y = 0;

	return direction;
}

Vector2 BossManager::getPlayerDirection()
{
	return Vector2();
}
