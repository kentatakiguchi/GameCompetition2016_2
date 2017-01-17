#include "DysonAttack.h"
#include "../../Rock.h"
#include "../Tornado.h"
#include "../../../../../ResourceLoader/ResourceLoader.h"
#include <random>	// C++11の機能

DysonAttack::DysonAttack() : 
	BossAttack(nullptr, Vector2::Zero),
	windSE_(0),
	addAngle_(0.0f),
	isRockCreate_(true),
	tornadoObj_(nullptr),
	state_(State::Attack)
{}

DysonAttack::DysonAttack(IWorld * world, const Vector2 & position) :
	BossAttack(world, position),
	windSE_(ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_WIND)),
	addAngle_(1.0f),
	isRockCreate_(false),
	tornadoObj_(nullptr),
	state_(State::Attack)
{
	angle_ = 70.0f;
	animeNum_ = BREATH_NUMBER;
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
		changeState(State::Flinch, BREATH_DYSFUNCTION_NUMBER);
		isAnimaReverse_ = false;
		isAnimaLoop_ = false;
		if (tornadoObj_ != nullptr) {
			tornadoObj_->dead();
			tornadoObj_ = nullptr;
			// SEの停止
			StopSoundMem(windSE_);
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
		int size = static_cast<int>(CHIPSIZE);
		std::uniform_int_distribution<> aSecond(size * 2, size * 18);
		// 岩の生成
		for (int i = 0; i != 3; i++) {
			// Xの生成位置を入れる
			world_->addActor(ActorGroup::Enemy,
				std::make_shared<Rock>(world_, Vector2((float)aSecond(mt), 200.0f)));
		}
		isRockCreate_ = true;
	}
	else if ((int)(timer_ * 10) % 10 == 1)
		isRockCreate_ = false;
	// ボスの竜巻攻撃(仮)
	if (tornadoObj_ == nullptr) {
		wsDirection_ = direction_;
		auto tornado = std::make_shared<Tornado>(
			world_, position_ + Vector2(40.0f *  direction_.x, -120.0f),
			Vector2(CHIPSIZE * 4, CHIPSIZE * 1));
		world_->addActor(ActorGroup::Enemy, tornado);
		tornadoObj_ = tornado.get();
		// SEの再生
		PlaySoundMem(windSE_, DX_PLAYTYPE_LOOP);
	}
	// 竜巻オブジェクトの位置更新
	if (tornadoObj_ != nullptr)
		tornadoObj_->position_ = position_ + Vector2(40.0f *  direction_.x, -120.0f);
	// 壁に当たった時に反転する
	if (isWspHit_ && isPrevWspHit_ != isWspHit_) {
		direction_.x *= -1;
		wsDirection_ = direction_;
		angle_ = 180 - angle_;
		addAngle_ *= -1;
	}
	// 角度が一定値を超えたら、加算方向を変える
	if (angle_ >= 90.0f + 30.0f || angle_ <= 90.0f - 30.0f) {
		addAngle_ *= -1;
		if (direction_.x < 0) {
			if (addAngle_ >= 0) {
				isAnimaReverse_ = false;
			}
			else {
				isAnimaReverse_ = true;
			}
		}
		else if (direction_.x >= 0) {
			if (addAngle_ < 0) {
				isAnimaReverse_ = false;
			}
			else {
				isAnimaReverse_ = true;
			}
		}
	}
	// 角度の加算
	angle_ += addAngle_ * (deltaTime * 60.0f);
	tornadoObj_->setAngle((int)angle_);
	isPrevWspHit_ = isWspHit_;

	position_.x += 4.0f * direction_.x * (deltaTime * 60.0f);

	// デルタタイムが0以下なら、SEを一時停止する
	if (CheckSoundMem(windSE_) == 1 &&
		deltaTime <= 0) {
		StopSoundMem(windSE_);
	}
	else if (CheckSoundMem(windSE_) == 0 &&	deltaTime > 0) {
		// SEの再生(停止した箇所から再生)
		PlaySoundMem(windSE_, DX_PLAYTYPE_LOOP, false);
	}

	// 一定時間経過で攻撃終了
	if (timer_ <= 7.0f) return;
	tornadoObj_->dead();
	// SEの停止
	StopSoundMem(windSE_);
	isAttackEnd_ = true;
}

// 怯み状態
void DysonAttack::flinch(float deltaTime)
{
	isAnimaLoop_ = false;
	// プレイヤーをつなぐものに当たっていないなら、疲労状態に遷移
	if (isMove_) {
		changeState(State::Fatigue, BREATH_LESS_NUMBER);
		isAnimaLoop_ = true;
		return;
	}
	// 触れ続けている間で一定時間経過したらひるむ
	if (timer_ <= 1.5f) return;
	isFlinch_ = true;
}

// 疲労状態
void DysonAttack::fatigue(float deltaTime)
{
	//isAnimaLoop_ = true;
	if (timer_ <= 5.0f) return;
	// 攻撃状態に遷移
	changeState(State::Attack, BREATH_NUMBER);
}

// 状態の変更を行います
void DysonAttack::changeState(State state, int num)
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
	// SEが再生中なら、止める
	if (CheckSoundMem(windSE_) == 1)
		StopSoundMem(windSE_);
	changeState(State::Attack, BREATH_NUMBER);
	if (direction_.x >= 0)
		angle_ = 90.0f + 29.0f;
	else angle_ = 90.0f - 29.0f;
}
