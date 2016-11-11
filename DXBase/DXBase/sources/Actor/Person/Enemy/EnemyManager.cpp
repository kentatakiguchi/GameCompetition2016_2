#include "EnemyManager.h"
#include "FloorSearchPoint.h"

EnemyManager::EnemyManager(const Vector2 position) :
	distance_(1),
	wspResult_(0),
	wCollideCount_(0),
	wCollidePastCount_(wCollideCount_),
	timer_(0.0f),
	deltaTimer_(0.0f),
	boxMoveCount(0.0f),
	isDirection_(true),
	enemyPosition_(position),
	playerPosition_(Vector2::Zero),
	threadPosition_(position + Vector2::Left * 100.0f),
	threadLength_(Vector2::Distance(enemyPosition_, threadPosition_)),
	enemyDirection_(Vector2::Zero),
	wsDirection_(-1.0f, 0.0f),
	rotate_(0.0f),
	rotateSpeed_(10.0f),
	threadGravity_(0.5f)
{
	wspDirectionMap_.clear();

	wallMoveConteiner_.push_back(0);
	wallMoveConteiner_.push_back(1);
	wallMoveConteiner_.push_back(0);
	wallMoveConteiner_.push_back(-1);
	// 素数を追加(3～4桁)
	primeContainer_.push_back(200);
	primeContainer_.push_back(300);
	primeContainer_.push_back(500);
	primeContainer_.push_back(700);
	primeContainer_.push_back(1100);
	primeContainer_.push_back(1300);
	primeContainer_.push_back(1700);
	primeContainer_.push_back(1900);
	// mapに追加
	//// 当たっていない
	//wspDirectionMap_[0] = Vector2(0.0f, 0.0f);
	//wspDirectionMap_[10] = Vector2(0.0f, 0.0f);
	//wspDirectionMap_[20] = Vector2(0.0f, 0.0f);
	// 1つのみ(四隅) 2 5 13 19
	// X に移動量がある場合
	wspDirectionMap_[211] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[511] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[1311] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[1911] = Vector2(0.0f, 1.0f);
	// Y に移動量がある場合
	wspDirectionMap_[221] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[521] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[1321] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[1921] = Vector2(1.0f, 0.0f);
	// 1つのみ(上下左右) 3 7 11 17
	/*wspDirectionMap_[311] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[721] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[1121] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[1711] = Vector2(1.0f, 0.0f);*/
	// 2つ当たる
	wspDirectionMap_[812] = Vector2(wsDirection_.x, 0.0f);
	wspDirectionMap_[822] = Vector2(wsDirection_.x, 0.0f);
	// 3つ当たる(辺) 10 22 35 49
	wspDirectionMap_[1003] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[2203] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[3503] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[4903] = Vector2(-1.0f, 0.0f);
	// 3つ当たる(隅の近辺) 12 19 27 47
	// X に移動量がある場合
	wspDirectionMap_[1213] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[1913] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[2713] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[4713] = Vector2(0.0f, -1.0f);
	// Y に移動量がある場合
	wspDirectionMap_[1223] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[1923] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[2723] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[4723] = Vector2(-1.0f, 0.0f);
	// 3つの(四隅の組み合わせ)当たる 20 28 34 37
	// X に移動量がある場合
	wspDirectionMap_[2013] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[2813] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[3413] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[3713] = Vector2(0.0f, -1.0f);
	// Y に移動量がある場合
	wspDirectionMap_[2023] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[2823] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[3423] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[3723] = Vector2(-1.0f, 0.0f);

	// 4つ当たる(隅) (0135) (0356) (2147) (2467) 
	// X に移動量がある場合
	wspDirectionMap_[2514] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[3814] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[3914] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[5214] = Vector2(0.0f, -1.0f);
	// Y に移動量がある場合
	wspDirectionMap_[2524] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[3824] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[3924] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[5224] = Vector2(-1.0f, 0.0f);
	// 5点当たる
	wspDirectionMap_[5515] = Vector2(0.0f, -1.0f);

	// 1つのみ当たらない 74 70 66 60
	wspDirectionMap_[7417] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[7017] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[6617] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[6017] = Vector2(0.0f, 1.0f);
	wspDirectionMap_[7427] = Vector2(0.0f, -1.0f);
	wspDirectionMap_[7027] = Vector2(-1.0f, 0.0f);
	wspDirectionMap_[6627] = Vector2(1.0f, 0.0f);
	wspDirectionMap_[6027] = Vector2(0.0f, 1.0f);
	// 全部当たっている
	wspDirectionMap_[7718] = Vector2::Zero;
	wspDirectionMap_[7728] = Vector2::Zero;
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
	eachWSPObj();
	// 全部の値に割り振られていれば不要
	for (auto i = wspDirectionMap_.begin(); i != wspDirectionMap_.end(); i++) {
		// 方向を決められる場合か、ヒット数が1の場合　かつ
		// マップに入れてある値と同一ならば、方向を決める
		/*if ((isDirection_ || (wCollideCount_ == 1 || wCollidePastCount_ != wCollideCount_)) &&
			i->first == wspResult_) {*/
		if (isDirecion() && i->first == wspResult_) {
			wsDirection_ = wspDirectionMap_[wspResult_];
			// 方向を決めたらfalseにする
			isDirection_ = false;
			break;
		}
	}
	// 過去のカウントを更新
	wCollidePastCount_ = wCollideCount_;
	return wsDirection_;
	//return Vector2();
}

void EnemyManager::setIsDirection(bool isDirection)
{
	isDirection_ = isDirection;
}

float EnemyManager::eachWSPObj()
{
	wspResult_ = 0;
	wCollideCount_ = 0;
	for (int i = 0; i != wspContainer_.size(); i++) {
		// 当たっているなら、コンテナの値とヒット数を加算する
		if (wspContainer_[i]->isGround()) {
			wspResult_ += primeContainer_[i];
			wspResult_ += 1;
			wCollideCount_ += 1;
		}
	}
	// 進行方向によって、値を加算する(2桁)
	if (wsDirection_.x != 0)
		wspResult_ += 10;
	else if (wsDirection_.y != 0)
		wspResult_ += 20;

	return wspResult_;
}

FloorSearchPoint* EnemyManager::getWSPObj(const int number)
{
	return wspContainer_[number];
}

bool EnemyManager::isDirecion()
{
	// カウントが同一なら、falseを返す
	if (wCollidePastCount_ == wCollideCount_) 
		return false;
	//// 敵側の判定でtrueか、衝突数が1以外の場合はtrueを返す
	//if (isDirection_ || wCollideCount_ != 1)
	//	return true;

	return true;
}
