#include "Rock.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../../Define.h"
#include "../../../World/IWorld.h"
#include <random>

Rock::Rock(IWorld * world, const Vector2 & position, const float bodyScale) :
	Actor(world, "MiniBoss", position,
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	timer_(0.0f),
	speed_(4.0f),
	size_(0.0f),
	degree_(90.0f),
	playerName_(""),
	texPos_(Vector2::Zero),
	orizin_(Vector2::One * (256 / 2)),
	state_(State::Idel),
	animation_(EnemyAnimation2D())
{
	addAnimation();
	animation_.changeAnimation(WAIT_NUMBER);
	animation_.timeRandom();
	// テクスチャの位置の設定
	setTexPosition(10.0f);
	// サイズの設定
	size_ = body_.GetCircle().getRadius() / (128.0f / 1.5f);
	// プレイヤーの方向を向く
	animation_.changeDirType(-getPlayerDirection().x);
}

void Rock::onUpdate(float deltaTime)
{
	// プレイヤーが口の中に入ったら死亡
	if (world_->isEntered())
		changeState(State::Dead, DEAD_NUMBER);

	switch (state_)
	{
	case State::Idel: idel(deltaTime); break;
	case State::Fall: fall(deltaTime); break;
	case State::Adhere: adhere(deltaTime); break;
	case State::Dead : deadMove(deltaTime); break;
	}

	animation_.update(deltaTime);

	timer_ += deltaTime;
}

void Rock::onDraw() const
{
	/*auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;*/
	// アニメーションの描画
	//auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	//// 画像の表示
	/*DrawExtendGraph(
		(int)(vec3Pos.x - body_.GetCircle().getRadius()),
		(int)(vec3Pos.y - body_.GetCircle().getRadius()),
		(int)(vec3Pos.x + body_.GetCircle().getRadius()),
		(int)(vec3Pos.y + body_.GetCircle().getRadius()),
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_NEEDLE_TEX), 1);*/
	animation_.draw(
		texPos_,
		orizin_,
		size_,
		degree_ + 270.0f);
}

void Rock::onCollide(Actor & actor)
{
	// 死亡状態なら返す
	if (state_ == State::Dead) return;
	auto actorName = actor.getName();
	auto getPlayerName = strstr(actorName.c_str(), "PlayerBody");
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	// 床に当たったら、消滅
	if (getFloorName != NULL) {
		changeState(State::Dead, RUN_NUMBER);
		// 位置の更新
		setTexPosition(-50.0f);
		// 中点を下にする
		orizin_ = Vector2::One * (256.0f / 2.0f) + Vector2::Up * 100.0f;
		// プレイヤーと逆の方向を向く
		animation_.changeDirType(getPlayerDirection().x);
		//body_.enabled(false);
		return;
	}
	// プレイヤーの攻撃に当たったら死亡
	if (actorName == "PlayerAttackCollider") {
		changeState(State::Dead, DEAD_NUMBER);
		body_.enabled(false);
		return;
	}
	// くっつき状態なら返す
	if (state_ == State::Adhere) return;
	// プレイヤー関連のオブジェクトに当たったら
	if (getPlayerName != NULL) {
		changeState(State::Adhere, ADHERE_NUMBER);
		animation_.setIsLoop(false);
		playerName_ = actor.getName();
		position_ = actor.getPosition();
		degree_ = getRandomDegree();
	}
}

void Rock::onMessage(EventMessage event, void *){}

// 状態の変更
void Rock::changeState(State state, int animation)
{
	state_ = state;
	animation_.changeAnimation(animation);
	timer_ = 0.0f;
}

// 待機状態
void Rock::idel(float deltaTime)
{
	if (timer_ < 0.5f) return;
	changeState(State::Fall, WAIT_NUMBER);
}

// 落下状態
void Rock::fall(float deltaTime)
{
	// 落下
	position_.y += speed_ * timer_  * 9.8f * (deltaTime * 60.0f);
	setTexPosition(10.0f);
	// プレイヤーの方向を向く
	animation_.changeDirType(-getPlayerDirection().x);
}

// くっつき状態
void Rock::adhere(float deltaTime)
{
	auto player = world_->findActor(playerName_);
	// プレイヤーがいないなら死亡
	if (player == nullptr) {
		changeState(State::Dead, DEAD_NUMBER);
		body_.enabled(false);
		return;
	}
	auto addPos = Vector2(
		100.0f * MathHelper::Cos(degree_),
		100.0f * MathHelper::Sin(degree_));
	position_ = player->getPosition() + addPos;
	setTexPosition(10.0f);
	if (timer_ < 4.0f) return;
	changeState(State::Dead, DEAD_NUMBER);
	body_.enabled(false);
}

// 死亡状態
void Rock::deadMove(float deltaTime)
{
	name_ = "DeadMiniBoss";
	size_ -= deltaTime;
	size_ = max(0.0f, size_);
	if (size_ == 0.0f)
		dead();
}

// プレイヤーとの方向を返します
Vector2 Rock::getPlayerDirection()
{
	auto player = world_->findActor("PlayerBody1");
	// プレイヤーがいなかったら、単位ベクトルを返す
	if (player == nullptr) return Vector2::One;
	// 方向の計算
	auto distance = position_ - player->getPosition();
	auto direction = Vector2::One;
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

// テクスチャの位置を設定します
void Rock::setTexPosition(float up)
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	texPos_ = Vector2(vec3Pos.x, vec3Pos.y) - Vector2::Up * up;
}

// アニメーションの追加
void Rock::addAnimation()
{
	animation_.addAnimation(
		WAIT_NUMBER,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WAIT_TEX));
	animation_.addAnimation(
		RUN_NUMBER,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WALLATTACK_DASH_TEX));
	animation_.addAnimation(
		ADHERE_NUMBER,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_BREATH_DYSFUNCTION_TEX));
	animation_.addAnimation(
		DEAD_NUMBER,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_DEATH_TEX));
}

// ランダムの角度を取得します
float Rock::getRandomDegree()
{
	// 乱数の取得
	std::random_device random;
	// メルセンヌツイスター法 後で調べる
	// 初期Seed値を渡す
	std::mt19937 mt(random());
	// 範囲の指定(int型)
	std::uniform_int_distribution<> degree(0, 360);
	return (float)degree(mt);
}
