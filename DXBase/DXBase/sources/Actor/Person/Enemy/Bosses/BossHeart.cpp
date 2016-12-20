#include "BossHeart.h"

BossHeart::BossHeart(
	IWorld * world, const Vector2 & position,
	const int hp, const int bossHp) :
	Actor(world, "BossEntry", position, 
		std::make_shared<BoundingCircle>(const_cast<Vector2&>(position),Matrix::Identity, 32.0f,true)),
	stateCount_(3),
	initStateCount_(stateCount_),
	hp_(hp * stateCount_),
	initHp_(hp_),
	prevHp_(hp_),
	bossHp_(bossHp),
	timer_(0.0f),
	isEntered_(false),
	isLetOut_(false)
{
}

void BossHeart::onUpdate(float deltaTime)
{
	// デバッグ
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::N)) {
		hp_ -= 100;
		bossHp_--;
		stateCount_--;
		initStatus();
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::M)) {
		hp_ -= 50;
		if (hp_ % 100 == 0) {
			bossHp_ -= 1;
		}
	}

	// 追い出しをfalseにする
	isLetOut_ = false;
	// 前回の体力を更新
	prevHp_ = hp_;
	// 体内に入っていないなら、返す(もしもの判定)
	if (!isEntered_) return;
	timer_ += deltaTime;
	// ５秒経過後に追い出しをしたことにする
	if (timer_ < 5.0f) return;
	// 初期化
	initStatus();
}

void BossHeart::onDraw() const
{
	body_->draw(-1,inv_);

	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	DrawString(
		vec3Pos.x, vec3Pos.y -100,
		"心臓です", GetColor(255, 255, 255));
	// 攻撃可能なら表示
	if (isEntered_) {
		// 文字の表示
		DrawString(
			vec3Pos.x, vec3Pos.y,
			"攻撃可能", GetColor(255, 255, 255));
		// 体力の表示
		DrawFormatString(
			vec3Pos.x, vec3Pos.y - 75,
			GetColor(255, 255, 255), "体力:%d", hp_);
	}
}

void BossHeart::onCollide(Actor & actor)
{
	// 体内に入っていないなら、返す(もしもの判定)
	if (!isEntered_) return;
	auto actorName = actor.getName();
	if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
		hp_--;
		// 初期体力と過去の体力が同一なら、すぐに返す
		auto initHp = initHp_ / initStateCount_;
		if (prevHp_ == initHp * stateCount_) return;
		// 余りが 100 ならボスの体力を削る
		// 現在の体力の余りが前回の体力の余りより少ない場合
		if ((int)(hp_ / initHp) < (int)(prevHp_ / initHp)) {
			// 体力の補正
			hp_ += prevHp_ - hp_;
		}
		// 体力が状態が変わる節目(100の倍数)なら、ボスの体力を削る
		if (hp_ % initHp == 0) {
			// 体力が無くなったら、ボスの体力を減らす
			bossHp_--;
			stateCount_--;
			initStatus();
		}
	}
}

void BossHeart::onMessage(EventMessage event, void *)
{
}

// 心臓の体力を返します
int BossHeart::getHeartHp()
{
	return hp_;
}

// ボスの体力を返します
int BossHeart::getBossHp()
{
	return bossHp_;
}

void BossHeart::addBossHp(int hp)
{
	hp_ += hp;
	if (hp_ % 100 == 0)
		bossHp_ -= 1;
}

// プレイヤーが体内に入ったかを設定します
void BossHeart::setIsEntered(bool isEntered)
{
	isEntered_ = isEntered;
}

// プレイヤーを追い出したかを返します
bool BossHeart::isLetOut()
{
	return isLetOut_;
}

// ステータスの初期化を行います
void BossHeart::initStatus()
{
	timer_ = 0.0f;
	isLetOut_ = true;
	isEntered_ = false;
}
