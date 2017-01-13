#include "Tornado.h"
#include "../../../../ResourceLoader/ResourceLoader.h"

Tornado::Tornado(IWorld * world, const Vector2 & position, const Vector2& bodyScale) :
	Actor(world, "Tornado", position,
		CollisionBase(
			Vector2(position.x , position.y + bodyScale.y / 2.0f),
			Vector2(position.x + bodyScale.x, position.y + bodyScale.y / 2.0f),
			Vector2(position.x , position.y - bodyScale.y / 2.0f),
			Vector2(position.x + bodyScale.x, position.y - bodyScale.y / 2.0f)
			)),
	angle_(0.0f),
	initPosition_(position),
	animation_(EnemyAnimation2D())
{
	// アニメーションの追加
	animation_.addAnimation(
		0,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_EFFECT_ATTACK_SUIKOMI_30_TEX));
	animation_.changeAnimation(0);
}

void Tornado::onUpdate(float deltaTime)
{
	animation_.update(deltaTime);
}

void Tornado::onDraw() const
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// アニメーションの描画
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	auto angle = 270 + angle_;
	auto size = 1.0f;
	animation_.draw(
		pos,
		Vector2(256 * size / 2, 512 * size),
		size, angle);
}

void Tornado::onCollide(Actor & actor){}

void Tornado::onMessage(EventMessage event, void *){}

// 位置を初期化します
void Tornado::initPosition()
{
	position_ = initPosition_;
}

// 角度を変更します
void Tornado::setAngle(int angle)
{
	// 仮
	body_.RotateBox(angle);
	//// 回転したい
	//for (int i = 0; i != 4; i++) {
	//	//auto point = body_.GetBox().component_.point[i];
	//	auto tx = body_.GetBox().component_.point[i].x - position_.x;
	//	auto ty = body_.GetBox().component_.point[i].y - position_.y;
	//	body_.GetBox().component_.point[i].x = tx * cosf(angle * MathHelper::Pi / 180) - ty * sinf(angle * MathHelper::Pi / 180) + position_.x;
	//	body_.GetBox().component_.point[i].y = tx * sinf(angle * MathHelper::Pi / 180) + ty * cosf(angle * MathHelper::Pi / 180) + position_.y;
	//}
	angle_ = (float)angle;
}

// プレイヤーを探します
void Tornado::findPlayer() const
{
	auto player = world_->findActor("PlayerBody1");
	auto playerLength_ = 0.0f;
	if (player != nullptr) {
		playerLength_ = Vector2(player->getPosition() - position_).Length();
	}
	if (playerLength_ >=
		SCREEN_SIZE.x / 2.0f + body_.GetBox().getHeight())
		return;
}
