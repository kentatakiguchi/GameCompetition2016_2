#include "BossHeart.h"

BossHeart::BossHeart(
	IWorld * world, const Vector2 & position,
	const int hp, const int bossHp) :
	Actor(world, "BossEntry", position, 
		CollisionBase(const_cast<Vector2&>(position), 10.0f)),
	hp_(hp),
	initHp_(hp_),
	bossHp_(bossHp),
	timer_(0.0f),
	isEntered_(false),
	isLetOut_(false)
{
}

void BossHeart::onUpdate(float deltaTime)
{
	isLetOut_ = false;
	// 体内に入っていないなら、返す(もしもの判定)
	if (!isEntered_) return;
	timer_ += deltaTime;
	// 一定時間経過後に戻す
	if (timer_ < 5.0f) return;
	// プレイヤーの位置を戻す

	// 初期化
	initStatus();
}

void BossHeart::onDraw() const
{
	body_.draw(inv_);

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
	// if (isLetOut_) return;
	auto actorName = actor.getName();
	if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
		hp_--;
		// 体力が無くなったら、ボスの体力を減らす
		if (hp_ <= 0) {
			bossHp_--;
			// プレイヤーを外に出す

			hp_ = initHp_;
			initStatus();
		}
	}
}

void BossHeart::onMessage(EventMessage event, void *)
{
}

// ボスの体力を返します
int BossHeart::getBossHp()
{
	return bossHp_;
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
