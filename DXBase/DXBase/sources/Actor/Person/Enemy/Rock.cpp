#include "Rock.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../../Define.h"

Rock::Rock(IWorld * world, const Vector2 & position, const float bodyScale) : 
	Actor(world, "Rock", position,
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	timer_(0.0f),
	speed_(4.0f),
	state_(State::Idel),
	animeNum_(0),
	animation_(EnemyAnimation2D())
{
	animation_.addAnimation(
		animeNum_,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WAIT_TEX));
	animation_.changeAnimation(animeNum_);
	animation_.timeRandom();
}

void Rock::onUpdate(float deltaTime)
{
	switch (state_)
	{
	case State::Idel: idel(deltaTime); break;
	case State::Fall: fall(deltaTime); break;
	case State::Dead : deadMove(deltaTime); break;
	}

	animation_.update(deltaTime);

	timer_ += deltaTime;
}

void Rock::onDraw() const
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// アニメーションの描画
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	//// 画像の表示
	/*DrawExtendGraph(
		(int)(vec3Pos.x - body_.GetCircle().getRadius()),
		(int)(vec3Pos.y - body_.GetCircle().getRadius()),
		(int)(vec3Pos.x + body_.GetCircle().getRadius()),
		(int)(vec3Pos.y + body_.GetCircle().getRadius()),
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_NEEDLE_TEX), 1);*/
	animation_.draw(
		pos - Vector2::Up * 10,
		Vector2::One * (256 / 2),
		body_.GetCircle().getRadius() / (128.0f / 1.5f));
}

void Rock::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	//auto getPlayerName = strstr(actorName.c_str(), "PlayerBody");
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	// プレイヤー関連のオブジェクトに当たったら、消滅
	if (getFloorName != NULL)
		changeState(State::Dead);
}

void Rock::onMessage(EventMessage event, void *){}

// 状態の変更
void Rock::changeState(State state)
{
	state_ = state;
	timer_ = 0.0f;
}

// 待機状態
void Rock::idel(float deltaTime)
{
	if (timer_ <= 0.5f) return;
	changeState(State::Fall);
}

// 落下状態
void Rock::fall(float deltaTime)
{
	// 落下
	position_.y += speed_ * timer_  * 9.8f * (deltaTime * 60.0f);
}

// 死亡状態
void Rock::deadMove(float deltaTime)
{
	dead();
}
