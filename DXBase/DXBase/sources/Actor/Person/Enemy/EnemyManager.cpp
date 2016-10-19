#include "EnemyManager.h"

EnemyManager::EnemyManager() : 
	timer_(0.0f),
	deltaTimer_(0.0f),
	boxMoveCount(0.0f),
	enemyPosition_(Vector3(0.0f, 0.0f, 0.0f)),
	playerPosition_(Vector3(0.0f, 0.0f,0.0f))
{
	boxMoveConteiner_.push_back(0);
	boxMoveConteiner_.push_back(1);
	boxMoveConteiner_.push_back(0);
	boxMoveConteiner_.push_back(-1);
}

EnemyManager::~EnemyManager()
{
}

// 更新
void EnemyManager::update(float deltaTime)
{
	deltaTimer_ = deltaTime;
	timer_ += deltaTimer_;
}

// 箱の動き方(壁なし)
Vector3 EnemyManager::boxMove()
{
	boxMoveCount += deltaTimer_ / 2.0f;
	auto posi = enemyPosition_;
	posi = Vector3(
		boxMoveConteiner_[(int)boxMoveCount % 4] * 3.0f,
		boxMoveConteiner_[((int)boxMoveCount + 3) % 4] * 1.0f,
		0.0f
		);
	//if((int)timer_ %  1 * 60.0f >= 0)
	return posi;
}

// 壁に沿った動き方（まだ）
Vector3 EnemyManager::wallMove()
{
	// 敵の四方に当たり判定のあるオブジェクトを配置
	// 当たったオブジェクトの名前などを参照して、方向の値を決定する
	return Vector3();
}

// 崖を避ける動き方
Vector3 EnemyManager::cliffMove()
{
	// 敵の前方下部に当たり判定のあるオブジェクトを配置
	// 向いている方向によって、オブジェクトの位置を変える
	return Vector3();
}

// 糸を使った動き方
Vector3 EnemyManager::threadMove()
{
	return Vector3();
}

// プレイヤーとの距離を返します
float EnemyManager::getPlayerLength()
{
	// プレイヤーの位置を取得
	Vector2 vec2PlayerPosition = Vector2(playerPosition_.x, playerPosition_.y);
	Vector2 vec2EnemyPosition = Vector2(enemyPosition_.x, enemyPosition_.y);
	Vector2 length = vec2PlayerPosition - vec2EnemyPosition;
	return length.Length();
}

// プレイヤーとの方向を単位ベクトルで取得します
Vector2 EnemyManager::getPlayerDirection()
{
	// 方向の計算
	auto distance = enemyPosition_ - playerPosition_;
	auto direction = Vector2().Zero;
	//auto direction = 1.0f;
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
	else if (distance.x > 0)
		direction.y = -1;
	else direction.y = 0;
	return direction;
}

// プレイヤーとの方向を正規化されたベクトルで取得します
Vector3 EnemyManager::getPlayerNormalizeDirection()
{
	// 方向の計算
	auto distance = enemyPosition_ - playerPosition_;
	//// 変換
	//auto nomaDistance = Vector2(distance.x, distance.y);
	//// 正規化
	//nomaDistance = nomaDistance.Normalize(nomaDistance);
	//auto distance3 = Vector3(nomaDistance.x, nomaDistance.y, 0.0f);
	distance = distance.Normalize(distance);
	return distance;
}

//　敵自身とプレイヤーの位置を入れます
void EnemyManager::setEMPosition(const Vector3& enemyPosition, const Vector3& playerPosition)
{
	enemyPosition_ = enemyPosition;
	playerPosition_ = playerPosition;
}
