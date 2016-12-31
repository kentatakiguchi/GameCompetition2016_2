#include "WallAttack.h"
#include "../Effect/ImportEffects.h"
#include <random>	// C++11の機能

WallAttack::WallAttack() :
	BossAttack(nullptr, Vector2::Zero),
	count_(0),
	aSecond_(0),
	createCount_(0),
	speed_(0.0f),
	isWallAttackEnd_(true),
	//isFlinch_(false),
	state_(State::FloorSearch),
	prevPlayerDistance_(Vector2::Zero)
{
}

WallAttack::WallAttack(IWorld* world, const Vector2 & position) :
	BossAttack(world, position),
	count_(0),
	aSecond_(5),
	speed_(4.0f),
	isWallAttackEnd_(false),
	//isFlinch_(true),
	//state_(State::FloorSearch),
	state_(State::WallMove),
	prevPlayerDistance_(Vector2::One)
{
	moveTimes_.clear();
	moveDirections_.clear();
	// 壁移動時間コンテナに追加
	moveTimes_.push_back(5);
	moveTimes_.push_back(10);
	moveTimes_.push_back(3);
	moveTimes_.push_back(8);
	moveTimes_.push_back(1);
	moveTimes_.push_back(6);
	// 方向コンテナに追加
	moveDirections_.push_back(0.0f);
	moveDirections_.push_back(-1.0f);
	moveDirections_.push_back(0.0f);
	moveDirections_.push_back(1.0f);
	moveDirections_.push_back(0.0f);
	// 方向の設定
	auto direction = Vector2(
		moveDirections_[(count_ + 1) % 4],
		moveDirections_[count_ % 4]
		);
	direction_ = direction;
	animeNum_ = WALLATTACK_DASH_NUMBER;
}

void WallAttack::attack(float deltaTime)
{
	switch (state_)
	{
	case State::FloorSearch: floorSearch(deltaTime); break;
	case State::FloorGetOff: floorGetOff(deltaTime); break;
	case State::WallMove: wallMove(deltaTime); break;
	case State::WallAttack: wallAttack(deltaTime); break;
	}
}

void WallAttack::Refresh()
{
	BossAttack::Refresh();
	flinchCount_ = 0;
	createCount_ = 0;
	isWallAttackEnd_ = false;
	/*if (flinchCount_ <= 0)
		isFlinch_ = true;*/
	/*changeState(State::FloorSearch,
		BossAnimationNumber::WAIT_NUMBER);*/
	changeState(State::WallMove, WALLATTACK_DASH_NUMBER);
	count_ = 0;
	auto direction = Vector2(
		moveDirections_[(count_ + 1) % 4],
		moveDirections_[count_ % 4]
		);
	direction_ = direction;
	//animeNum_ = BossAnimationNumber::WAIT_NUMBER;
}

// 床捜索状態です
void WallAttack::floorSearch(float deltaTime)
{
	// 浮いている床に接地していれば、床を降りる	
	if (floorName_ == "BossAreaFloor") {
		// 計算して出てきた方向をかけて移動する
		auto direction = 1.0f;
		// ステージの大きさの半分より以下なら、左に移動する
		if (position_.x <= CHIPSIZE * 20 / 2)
			direction = -1.0f;
		direction_.x = direction;
		changeState(State::FloorGetOff, WAIT_NUMBER);
	}
	// そうでなければ、壁移動に遷移
	if (floorName_ == "MovelessFloor") {
		changeState(State::WallMove, WALLATTACK_DASH_NUMBER);
		setAttackSecond();
	}
}

// 床から降りる状態です
void WallAttack::floorGetOff(float deltaTime)
{
	// ボスの位置と空中の床の中心位置を参照して、地面に戻る
	position_.x += speed_ * direction_.x * (deltaTime * 60.0f);
	// 重力
	if(!isGround_)
		position_.y += 9.8f * (deltaTime* 60.0f);
	// 地面に接地したら壁移動状態に遷移
	if (floorName_ == "MovelessFloor") {
		changeState(State::WallMove, WALLATTACK_DASH_NUMBER);
		setAttackSecond();
	}
}

// 壁移動状態です
void WallAttack::wallMove(float deltaTime)
{
	isUseGravity_ = false;
	isAttackStart_ = true;
	isBodyHit_ = false;
	isAttackHit_ = false;
	animeNum_ = WALLATTACK_DASH_NUMBER;

	/*if (createCount_ % 2 == 0) {
		world_->addActor(ActorGroup::EffectBack,
			std::make_shared<DashEffect>(world_, position_));
	}
	createCount_++;*/
	// 時計周りで移動
	auto speed = speed_ * 3.0f;
	//auto count = 0;
	if (isWspHit_ && isPrevWspHit_ != isWspHit_) {
		count_++;
	}
	isPrevWspHit_ = isWspHit_;

	auto direction = Vector2(
		moveDirections_[(count_ + 1) % 4],
		moveDirections_[(int)(count_ % 4)]
		);
	direction_ = direction;
	animeAngle_ = (count_ * 90) % 360;
	// 仮
	auto pos = direction * speed * (deltaTime * 60.0f);
	position_ += pos;

	// 攻撃間近にアニメーションを変更する
	if (timer_ >= aSecond_ - 0.2f) {
		animeNum_ = WALLATTACK_DASHJUMP_STOP_NUMBER;
		isAnimaLoop_ = false;
	}
	// 一定時間経過で、壁攻撃に遷移
	if (timer_ >= aSecond_) {
		changeState(State::WallAttack, WALLATTACK_DASHJUMP_NUMBER);
		isAnimaLoop_ = false;
		prevPlayerDistance_ = pNormDirection_;
		// プレイヤーの方向を向く
		auto a = prevPlayerDistance_;
		auto angle = std::atan2(a.y, a.x) * 180.0f / MathHelper::Pi;
		animeAngle_ = angle + 90.0f;
	}
}

// 壁攻撃状態です
void WallAttack::wallAttack(float deltaTime)
{
	auto speed = speed_ * 7.0f;
	isAnimaLoop_ = false;
	//animeNum_ = BossAnimationNumber::WALLATTACK_DASHJUMP_NUMBER;
	// プレイヤーの居た位置に向かって飛ぶ
	position_ += prevPlayerDistance_ * speed * (deltaTime * 60.0f);
	if (timer_ <= 0.2f) return;
	if (floorName_ == "BossAreaFloor" || floorName_ == "MovelessFloor") {
		//flinchCount_--;
		isAnimaLoop_ = true;
		isBodyHit_ = true;
		isAttackHit_ = true;
		isWallAttackEnd_ = true;
		isAttackEnd_ = true;
	}
}

// 壁移動する時間を決定します
void WallAttack::setAttackSecond()
{
	// コンテナの要素数の指定
	int aCount = 0;
	auto hp = (hp_ % 100) + 1;
	/*if (flinchCount_ <= 0) {
		flinchCount_ = 1;
		if (hp >= 30) {
			flinchCount_ = 2;
		}
		else if (hp < 30) {
			flinchCount_ = 3;
		}
	}*/
	
	flinchCount_ = 1;
	// 体力が70未満の場合、カウントの値を変える
	if (hp >= 30) {
		aCount = 2;
		flinchCount_ = 2;
	}
	else if (hp < 30) {
		aCount = 4;
		flinchCount_ = 3;
	}
	// 乱数の取得
	std::random_device random;
	// メルセンヌツイスター法 後で調べる
	// 初期Seed値を渡す
	std::mt19937 mt(random());
	// 範囲の指定(int型)
	std::uniform_int_distribution<> aSecond(moveTimes_[aCount], moveTimes_[aCount + 1]);
	// 移動秒数を入れる
	aSecond_ = aSecond(mt);
}

// 状態の変更を行います
void WallAttack::changeState(State state, int number)
{
	state_ = state;
	animeNum_ = number;
	timer_ = 0.0f;
}
