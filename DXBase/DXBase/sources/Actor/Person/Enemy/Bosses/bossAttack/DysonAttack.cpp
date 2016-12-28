#include "DysonAttack.h"
#include "../../Rock.h"
#include "../Tornado.h"
#include <random>	// C++11の機能

DysonAttack::DysonAttack() : 
	BossAttack(nullptr, Vector2::Zero),
	addAngle_(0.0f),
	isRockCreate_(true),
	tornadoObj_(nullptr),
	state_(State::Attack)
{
}

DysonAttack::DysonAttack(IWorld * world, const Vector2 & position) :
	BossAttack(world, position),
	addAngle_(1.0f),
	isRockCreate_(false),
	tornadoObj_(nullptr),
	state_(State::Attack)
{
	angle_ = 70.0f;
	animeNum_ = BossAnimationNumber::BREATH_NUMBER;
	/*auto tornado = std::make_shared<Tornado>(
		world_, Vector2(-1000.0f, 0.0f), Vector2(CHIPSIZE * 10, 32.0f * 3));
	world_->addActor(ActorGroup::Enemy, tornado);
	tornadoObj_ = tornado.get();*/
}

void DysonAttack::attack(float deltaTime)
{
	switch (state_)
	{
	case State::Attack: dysonAttack(deltaTime); break;
	case State::Flinch: flinch(deltaTime); break;
	case State::Fatigue: fatigue(deltaTime); break;
	}
}

// 攻撃状態
void DysonAttack::dysonAttack(float deltaTime)
{
	// 動けない状態なら、ひるみ状態に遷移
	if (!isMove_) {
		changeState(State::Flinch,
			BossAnimationNumber::BREATH_DYSFUNCTION_NUMBER);
		isAnimaLoop_ = false;
		if (tornadoObj_ != nullptr) {
			tornadoObj_->dead();
			tornadoObj_ = nullptr;
		}
		return;
	}

	// 岩の生成
	if ((int)(timer_ * 10) % 10 == 0 && !isRockCreate_) {
		// 乱数の取得
		std::random_device random;
		// メルセンヌツイスター法 後で調べる
		// 初期Seed値を渡す
		std::mt19937 mt(random());
		// 範囲の指定(int型)
		std::uniform_int_distribution<> aSecond(CHIPSIZE * 2, CHIPSIZE * 18);
		// 岩の生成
		for (int i = 0; i != 3; i++) {
			// Xの生成位置を入れる
			world_->addActor(ActorGroup::Enemy,
				std::make_shared<Rock>(world_, Vector2(aSecond(mt), 200.0f)));
		}
		isRockCreate_ = true;
	}
	else if ((int)(timer_ * 10) % 10 == 1)
		isRockCreate_ = false;
	// ボスの竜巻攻撃(仮)
	if (tornadoObj_ == nullptr) {
		auto tornado = std::make_shared<Tornado>(
			world_, position_, Vector2(CHIPSIZE * 2, CHIPSIZE * 4));
		world_->addActor(ActorGroup::Enemy, tornado);
		tornadoObj_ = tornado.get();
		// SEの再生

	}
	// 竜巻オブジェクトの位置更新
	if (tornadoObj_ != nullptr)
		tornadoObj_->position_ = position_ - Vector2::One * 100.0f;

	if (isWspHit_ && isPrevWspHit_ != isWspHit_) {
		direction_.x *= -1;
	}
	// 角度が一定値を超えたら、加算方向を変える
	if (angle_ >= 90.0f + 40.0f || angle_ <= 90.0f - 40.0f)
		addAngle_ *= -1;
	// 角度の加算
	angle_ += addAngle_;
	tornadoObj_->setAngle(angle_);

	isPrevWspHit_ = isWspHit_;

	position_.x += 4.0f * direction_.x * (deltaTime * 60.0f);

	// 一定時間経過で攻撃終了
	if (timer_ <= 7.0f) return;
	tornadoObj_->dead();
	//tornadoObj_->initPosition();
	isAttackEnd_ = true;
}

// 怯み状態
void DysonAttack::flinch(float deltaTime)
{
	//isFlinch_ = true;
	// プレイヤーをつなぐものに当たっていないなら、疲労状態に遷移
	if (isMove_) {
		changeState(State::Fatigue,
			BossAnimationNumber::BREATH_LESS_NUMBER);
		isAnimaLoop_ = true;
		return;
	}
	// 触れ続けている間で一定時間経過したらひるむ
	if (timer_ <= 5.0f) return;
	isFlinch_ = true;
	//isAttackEnd_ = true;
}

// 疲労状態
void DysonAttack::fatigue(float deltaTime)
{
	if (timer_ <= 5.0f) return;
	// 攻撃状態に遷移
	changeState(State::Attack, 
		BossAnimationNumber::BREATH_NUMBER);
}

// 状態の変更を行います
void DysonAttack::changeState(State state, BossAnimationNumber num)
{
	state_ = state;
	timer_ = 0.0f;
	animeNum_ = num;
}

void DysonAttack::Refresh()
{
	BossAttack::Refresh();
	isFlinch_ = false;
	tornadoObj_ = nullptr;
	changeState(State::Attack,
		BossAnimationNumber::BREATH_NUMBER);
	//state_ = State::Attack;
	//animeNum_ = BossAnimationNumber::BREATH_NUMBER;
}
