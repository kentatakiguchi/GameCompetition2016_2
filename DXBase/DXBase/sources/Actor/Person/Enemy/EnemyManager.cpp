#include "EnemyManager.h"
#include "FloorSearchPoint.h"

EnemyManager::EnemyManager(const Vector2 position) :
	distance_(1),
	timer_(0.0f),
	deltaTimer_(0.0f),
	boxMoveCount(0.0f),
	wspResult_(0.0f),
	enemyPosition_(position),
	playerPosition_(Vector2::Zero),
	threadPosition_(position + Vector2::Left * 100.0f),
	threadLength_(Vector2::Distance(enemyPosition_, threadPosition_)),
	enemyDirection_(Vector2::Zero),
	wsDirection_(1.0f, 0.0f),
	rotate_(0.0f),
	rotateSpeed_(10.0f),
	threadGravity_(0.5f)
{
	wallMoveConteiner_.push_back(0);
	wallMoveConteiner_.push_back(1);
	wallMoveConteiner_.push_back(0);
	wallMoveConteiner_.push_back(-1);
	// mapに追加


	// 1つのみ当たらない
	wspDirectionMap_[74] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[70] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[66] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[60] = Vector2(0.0f, 1.0f);
	// 全部当たっている
	wspDirectionMap_[77] = Vector2::Zero;
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
Vector2 EnemyManager::boxMove()
{
	boxMoveCount += deltaTimer_ / 2.0f;
	auto direction = enemyPosition_;
	direction = Vector2(
		wallMoveConteiner_[(int)boxMoveCount % 4] * 3.0f,
		wallMoveConteiner_[((int)boxMoveCount + 3) % 4] * 1.0f
		);
	//if((int)timer_ %  1 * 60.0f >= 0)
	return direction;
}

// 壁に沿った動き方（まだ）
Vector2 EnemyManager::wallMove()
{
	//auto direction = Vector2::Zero;
	// 壁に当たっているかを検索
	//if (wspContainer_[0]->isGround()) {
	//	if (wspContainer_[1]->isGround()) {
	//		wsDirection_.x = 1;
	//		wsDirection_.y = 0;
	//	}
	//	else if (wspContainer_[3]->isGround()) {
	//		wsDirection_.x = 0;
	//		//wsDirection_.y = 1;
	//	}
	//	else if (!wspContainer_[1]->isGround()) {
	//		if (wsDirection_.x == 1)
	//			wsDirection_.y = -1;
	//		else if (wsDirection_.y == 1)
	//			wsDirection_.x = -1;
	//	}
	//}
	//else if (wspContainer_[5]->isGround()) {
	//	if (wsDirection_.x == 1)
	//		wsDirection_.y = 1;
	//	else if (wsDirection_.y == -1)
	//		wsDirection_.x = -1;
	//}

	/*else if (wspContainer_[2]->isGround()) {
		if (enemyDirection_.x == -1)
			direction.y = -1;
		else if (enemyDirection_.y == 1)
			direction.x = 1;
	}
	else if (wspContainer_[7]->isGround()) {
		if (enemyDirection_.x == -1)
			direction.y = 1;
		else if (enemyDirection_.y == -1)
			direction.x = 1;
	}*/

	// 敵の四方に当たり判定のあるオブジェクトを配置
	// 当たったオブジェクトの名前などを参照して、方向の値を決定する
	return wsDirection_;
}

// 崖を避ける動き方
Vector2 EnemyManager::cliffMove(bool isFloor)
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
Vector2 EnemyManager::threadMove()
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
		threadPosition_ = enemyPosition_ + Vector2::Left * 100.0f;
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

	return Vector2(px, py);
}

// 指定したオブジェクトとの距離を返します
float EnemyManager::getLength(const Vector2 & otherPosition)
{
	auto length = otherPosition - enemyPosition_;
	return length.Length();
}

// プレイヤーとの距離を返します
float EnemyManager::getPlayerLength()
{
	// プレイヤーの位置を取得
	return getLength(playerPosition_);
}

// 指定したオブジェクトとの方向を単位ベクトルで取得します
Vector2 EnemyManager::getDirection(const Vector2& otherPosition)
{
	// 方向の計算
	auto distance = enemyPosition_ - otherPosition;
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

// プレイヤーとの方向を単位ベクトルで取得します
Vector2 EnemyManager::getPlayerDirection()
{
	return getDirection(playerPosition_);
}

// プレイヤーとの方向を正規化されたベクトルで取得します
Vector2 EnemyManager::getPlayerNormalizeDirection()
{
	// 方向の計算
	auto distance = enemyPosition_ - playerPosition_;
	return distance.Normalize(distance);
}

//　敵自身とプレイヤーの位置を入れます
void EnemyManager::setEMPosition(const Vector2& enemyPosition, const Vector2& playerPosition, const Vector2 direction)
{
	enemyPosition_ = enemyPosition;
	playerPosition_ = playerPosition;
	enemyDirection_ = direction;
}

// 糸の支点の位置取得
Vector2 EnemyManager::getThreadPoint()
{
	return threadPosition_;
}

// 捜索オブジェクトの設定
void EnemyManager::addFSP(FloorSearchPoint * fsp)
{
	wspContainer_.push_back(fsp);
}

// 壁に沿った動き方
Vector2 EnemyManager::getWallDirection()
{
	auto direction = Vector2::Zero;
	// 
	for (auto i = wspDirectionMap_.begin(); i != wspDirectionMap_.end(); i++) {
		// マップに入れてある値と同一ならば、方向を決める
		if (i->first == wspResult_)
			direction = wspDirectionMap_[wspResult_];
	}
	return direction;
	//return Vector2();
}

float EnemyManager::eachWSPObj()
{
	//for (auto i = wspDirectionMap_.begin(); i != wspDirectionMap_.end(); i++) {
	//	// マップに入れてある値と同一ならば、方向を決める
	//	if (i->first == wspResult_)
	//}
	return 0.0f;
}

FloorSearchPoint* EnemyManager::getWSPObj(const int number)
{
	return wspContainer_[number];
}
