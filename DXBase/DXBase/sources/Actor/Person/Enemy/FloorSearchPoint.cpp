#include "FloorSearchPoint.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"

FloorSearchPoint::FloorSearchPoint(
	IWorld * world, 
	const Vector2& enemyPosition,
	const Vector2& addPosition,
	const Vector2& bodyScale
	) :
	Actor(world, "FSP", enemyPosition + addPosition,
		CollisionBase(
			Vector2((enemyPosition.x + addPosition.x) + bodyScale.x / 2.0f, (enemyPosition.y + addPosition.y) + bodyScale.y / 2.0f),
			Vector2((enemyPosition.x + addPosition.x) - bodyScale.x / 2.0f, (enemyPosition.y + addPosition.y) + bodyScale.y / 2.0f),
			Vector2((enemyPosition.x + addPosition.x) + bodyScale.x / 2.0f, (enemyPosition.y + addPosition.y) - bodyScale.y / 2.0f),
			Vector2((enemyPosition.x + addPosition.x) - bodyScale.x / 2.0f, (enemyPosition.y + addPosition.y) - bodyScale.y / 2.0f)
			)
		),
	turnCount_(0),
	isFloor_(false),
	isGround_(false),
	direction_(1.0f, 1.0f),
	scale_(bodyScale),
	enemyPosition_(enemyPosition),
	addPosition_(addPosition),
	floorPosition_(Vector2::Zero)
{
}

void FloorSearchPoint::onUpdate(float deltaTime)
{
	/*auto pos = position_;
	auto pointPos = Vector2(
		pointPosition_.x * direction_.x,
		pointPosition_.y * direction_.y);*/
	//position_ = pos + pointPos;

	auto addPos = Vector2(
		addPosition_.x * direction_.x,
		addPosition_.y * direction_.y);
	position_ = enemyPosition_ + addPos;

	isFloor_ = false;
	isGround_ = false;
}

void FloorSearchPoint::onDraw() const
{
	body_.draw();
}

void FloorSearchPoint::onCollide(Actor & actor)
{
	// 床に当たっていた、振り向き回数をリセット
	if (actor.getName() == "MovelessFloor") {
		turnCount_ = 0;
		isGround_ = true;
		// 位置をブロックの上面に修正する
		clampPosition(position_, actor.position_);
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
	//position_.x *= -1;
	isFloor_ = true;
}

void FloorSearchPoint::onMessage(EventMessage event, void *)
{
}

// 位置の設定
void FloorSearchPoint::setPosition(const Vector2& position)
{
	//position_ = position;
	enemyPosition_ = position;
}

// 方向の設定
void FloorSearchPoint::setDirection(const Vector2& direction)
{
	direction_ = direction;
}

// 敵の大きさを入れます
void FloorSearchPoint::setEnemyScale(const Vector2& scale)
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

bool FloorSearchPoint::isGround()
{
	return isGround_;
}

// 床と当たった場所を返します
Vector2 FloorSearchPoint::getFloorPosition()
{
	return floorPosition_;
}

// 床との位置をクランプします
void FloorSearchPoint::clampPosition(const Vector2& thisPosition, const Vector2& otherPosition)
{
	// 床との位置を計算　負の値の場合、床の下にいる
	auto posY = otherPosition.y - thisPosition.y - CHIPSIZE; //blockScale;
	//// 半径を加算した位置にする
	if (posY < 0)
		floorPosition_ = position_ + Vector2::Up * posY;
}
