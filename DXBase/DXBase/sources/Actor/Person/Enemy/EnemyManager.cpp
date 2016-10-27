#include "EnemyManager.h"

EnemyManager::EnemyManager(const Vector3 position) :
	distance_(1),
	timer_(0.0f),
	deltaTimer_(0.0f),
	boxMoveCount(0.0f),
	enemyPosition_(position),
	playerPosition_(Vector3::Zero),
	threadPosition_(position + Vector3::Left * 100.0f),
	threadLength_(Vector3::Distance(enemyPosition_, threadPosition_)),
	rotate_(0.0f),
	rotateSpeed_(10.0f),
	threadGravity_(0.5f)
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
	auto direction = enemyPosition_;
	direction = Vector3(
		boxMoveConteiner_[(int)boxMoveCount % 4] * 3.0f,
		boxMoveConteiner_[((int)boxMoveCount + 3) % 4] * 1.0f,
		0.0f
		);
	//if((int)timer_ %  1 * 60.0f >= 0)
	return direction;
}

// 壁に沿った動き方（まだ）
Vector3 EnemyManager::wallMove()
{
	auto directionX = 0;
	auto directionY = 0;
	auto count = 1;
	// X
	if (count == 1 || count == 4)
		directionX = 1;
	// Y
	if (count == 2 || count == 3)
		directionY = 1;

	if (count == 4 && (count == 2 || count == 3))
		directionY = 1;
	// 敵の四方に当たり判定のあるオブジェクトを配置
	// 当たったオブジェクトの名前などを参照して、方向の値を決定する
	return Vector3();
}

// 崖を避ける動き方
Vector3 EnemyManager::cliffMove(bool isFloor)
{
	auto posi = enemyPosition_;
	// 床に当たっていなかったら方向転換
	/*if (!isFloor)
		distance_ *= -1;*/

	// 仮
	/*boxMoveCount += deltaTimer_ / 2.0f;
	if ((int)boxMoveCount % 2 == 0)
		distance_ = -1;
	else distance_ = 1;*/
	// 仮

	posi = posi.Left * distance_;
	// 敵の前方下部に当たり判定のあるオブジェクトを配置
	// 向いている方向によって、オブジェクトの位置を変える
	return posi;
}

// 糸を使った動き方
Vector3 EnemyManager::threadMove()
{
	// おもりの位置
	auto radius = rotate_ * MathHelper::Pi / 180.0f;
	auto px = threadPosition_.x + MathHelper::Cos(radius) * threadLength_;
	auto py = threadPosition_.y + MathHelper::Sin(radius) * threadLength_;
	// 重力移動をしたおもりの位置
	auto vx = px - threadPosition_.x;
	auto vy = py - threadPosition_.y;
	auto t = -(vy * threadGravity_) / (vx * vx + vy * vy);
	auto gx = px + t * vx;
	auto gy = py + threadGravity_ + t * vy;
	// 二つのおもりの角度の差
	auto r = 
		MathHelper::ATan(
			gy - threadPosition_.y,
			gx - threadPosition_.x
			) * 180.0f / MathHelper::Pi;
	// 角度差を角速度に加算
	auto sub = r - rotate_;
	sub -= (int)sub / 360.0f * 360.0f;
	//// 値が超えないように補正
	//if (sub <= -180.0f) sub += 360.0f;
	//else if (sub > 180.0f) sub -= 360.0f;

	// 半分になったらポイントを移動
	if (rotate_ >= 100.0f * 100.0f) {
		threadPosition_ = enemyPosition_ + Vector3::Left * 100.0f;
		rotate_ = 0.0f;
	}
	rotateSpeed_ += sub;
	// 角度に角速度を加算
	rotate_ += rotateSpeed_;
	// 再計算
	radius = rotate_ * MathHelper::Pi / 180.0f;
	px = threadPosition_.x + MathHelper::Cos(radius) * threadLength_;
	py = threadPosition_.y + MathHelper::Sin(radius) * threadLength_;
	// 正規化
	auto posi = Vector3(px, py, 0.0f);
	//auto nomaPosi = Vector3::Normalize(posi);

	return Vector3(px, py, 0.0f);
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
	else if (distance.y > 0)
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

// 糸の支点の位置取得
Vector3 EnemyManager::getThreadPoint()
{
	return threadPosition_;
}

// 捜索オブジェクトの設定
void EnemyManager::addFSP(FloorSearchPoint * fsp)
{
	fspContainer_.push_back(fsp);
}

// 壁に沿った動き方
Vector3 EnemyManager::getWallDirection()
{
	return Vector3();
}
