#include "Tornado.h"

Tornado::Tornado(IWorld * world, const Vector2 & position, const Vector2& bodyScale) :
	Actor(world, "Tornado", position,
		std::make_shared<BoundingBox>(Vector2(0, 1) * bodyScale.y / -2.0f, Matrix::Identity, bodyScale.x * 2, bodyScale.y, true)),
	//CollisionBase(
	//		Vector2(position.x + bodyScale.x, position.y + bodyScale.y / 2.0f),
	//		Vector2(position.x, position.y + bodyScale.y / 2.0f),
	//		Vector2(position.x + bodyScale.x, position.y - bodyScale.y / 2.0f),
	//		Vector2(position.x, position.y - bodyScale.y / 2.0f)
	//		)),
	initPosition_(position)
{
}

void Tornado::onUpdate(float deltaTime)
{
	//auto a = rotation_.;
	//body_.

	//body_.RotateBox(-45);

	/*auto point = body_.GetBox().component_.point;
	auto addPos = (0.0f, -100.0f);

	body_.GetBox().transform(
		point[1] + addPos, point[2] + addPos,
		point[3] + addPos, point[4] + addPos);*/

	//findPlayer();
	//auto player = world_
}

void Tornado::onDraw() const
{
	//findPlayer();
	/*auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;*/
	// デバッグ
	//DrawFormatString(600, 25, GetColor(255, 0, 255), "座標:%f,%f", position_.x,position_.y);
	
	body_->transform(getPose())->draw(-1, inv_);
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
	//body_.RotateBox(angle);
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
		SCREEN_SIZE.x / 2.0f + body_->height())
		return;
}
