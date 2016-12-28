#include "Rock.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../../Define.h"

Rock::Rock(IWorld * world, const Vector2 & position, const float bodyScale) : 
	Actor(world, "BaseEnemy", position,
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	timer_(0.0f),
	speed_(4.0f),
	state_(State::Idel)
{
}

void Rock::onUpdate(float deltaTime)
{
	switch (state_)
	{
	case State::Idel: idel(deltaTime); break;
	case State::Fall: fall(deltaTime); break;
	case State::Dead : deadMove(deltaTime); break;
	}

	timer_ += deltaTime;
}

void Rock::onDraw() const
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// 画像の表示
	DrawExtendGraph(
		vec3Pos.x - body_.GetCircle().getRadius(),
		vec3Pos.y - body_.GetCircle().getRadius(),
		vec3Pos.x + body_.GetCircle().getRadius(), vec3Pos.y + body_.GetCircle().getRadius(),
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_NEEDLE_TEX), 1);
	/*DrawGraph(
		vec3Pos.x - body_.GetCircle().getRadius(),
		vec3Pos.y - body_.GetCircle().getRadius(),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::ENEMY_NEEDLE_TEX), 1);*/

	body_.draw(inv_);
}

void Rock::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	auto getPlayerName = strstr(actorName.c_str(), "PlayerBody");
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	// プレイヤー関連のオブジェクトに当たったら、消滅
	if (getPlayerName != NULL || getFloorName != NULL)
		changeState(State::Dead);
}

void Rock::onMessage(EventMessage event, void *)
{
}

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
	position_.y += speed_ * timer_ * 9.8f;
}

// 死亡状態
void Rock::deadMove(float deltaTime)
{
	dead();
}
