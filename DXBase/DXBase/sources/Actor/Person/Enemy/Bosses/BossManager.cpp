#include "BossManager.h"
#include "bossAttack/BossAttack.h"
#include "bossAttack/importBossAttack.h"

BossManager::BossManager() : 
	attackNumber_(0),
	bossPosition_(Vector2::Zero),
	playerPosition_(Vector2::Zero)
	/*timer_(0.0f),
	isAttackEnd_(false),
	movePosition_(Vector2::Zero)*/
{
}

BossManager::BossManager(const Vector2 & position) : 
	attackNumber_(0), 
	bossPosition_(position),
	playerPosition_(Vector2::Zero)
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
void BossManager::attackRefresh()
{
	bossAttackContainer_[attackNumber_]->Refresh();
}

// 行動によって移動した位置を返します
Vector2 BossManager::getMovePosition()
{
	return bossAttackContainer_[attackNumber_]->getMovePosition();
}

// 攻撃が終了したかを返します
bool BossManager::isAttackEnd()
{
	return bossAttackContainer_[attackNumber_]->isAttackEnd();
}

// ボスの位置を設定します
void BossManager::setPosition(const Vector2& position)
{
	bossPosition_ = position;
}

// プレイヤーの位置を設定します
void BossManager::setPlayerPosition(const Vector2 & position)
{
	playerPosition_ = position;
}

// 攻撃前の位置を決定します
void BossManager::prevPosition()
{
	bossAttackContainer_[attackNumber_]->setPosition(bossPosition_);
}

Vector2 BossManager::getDirection(const Vector2 & otherPosition)
{
	// 方向の計算(ボスの位置を主軸にする)
	// auto pos = bossAttackContainer_[attackNumber_]->getMovePosition();
	auto distance = otherPosition - bossPosition_;
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
	// bossAttackに方向を設定する
	auto direction = getDirection(playerPosition_);
	bossAttackContainer_[attackNumber_]->setDirection(direction);
	return direction;
}

void BossManager::setIsGround(bool isGround)
{
	bossAttackContainer_[attackNumber_]->setIsGround(isGround);
}

// ボスが壁の下側に当たったかを設定します
void BossManager::setIsBottom(bool isBottom)
{
	bossAttackContainer_[attackNumber_]->setIsBottom(isBottom);
}
