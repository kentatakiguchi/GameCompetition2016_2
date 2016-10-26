#include "FloorSearchPoint.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"

FloorSearchPoint::FloorSearchPoint(IWorld * world, const Vector3 & position) :
	vec2Position_(position.x, position.y),
	Actor(world, "BaseEnemy", position, CollisionBase(vec2Position_, 10.0f)),
	direction_(0),
	turnCount_(0),
	isFloor_(false),
	enemyScale_(Vector2::Zero)
{
}

void FloorSearchPoint::onUpdate(float deltaTime)
{

}

void FloorSearchPoint::onDraw() const
{
	body_.draw();
}

void FloorSearchPoint::onCollide(Actor & actor)
{
	// 床に当たっていた、振り向き回数をリセット
	if (actor.getName() == "Floor") {
		turnCount_ = 0;
		return;
	}
	//// 振り向き回数を加算
	//turnCount_ += 1;
	//// 両端に床が無かったら、動かない
	//if (turnCount_ > 1) {
	//	direction_ = 0;
	//	return;
	//}
	//// 方向の変更
	//direction_ *= -1;
	isFloor_ = true;
}

void FloorSearchPoint::onMessage(EventMessage event, void *)
{
}

// 位置の設定
void FloorSearchPoint::setPosition(Vector3 position)
{
	position_ = position;
}

// 方向の設定
void FloorSearchPoint::setDirection(int direction)
{
	direction_ = direction;
}

// 敵の大きさを入れます
void FloorSearchPoint::setEnemyScale(const Vector2 scale)
{
	//enemyScale_ = scale;
	position_.x += scale.x;
	position_.y += scale.y;
}

// 床と当たったかを返します
bool FloorSearchPoint::isFloor()
{
	return isFloor_;
}
