#include "PlayerSearchObj.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"

PlayerSearchObj::PlayerSearchObj(IWorld * world, const Vector2& enemyPosition, const Vector2& playerPosition) :
	Actor(world, "BaseEnemy",
		Vector2(
			std::abs(enemyPosition.x + playerPosition.x) / 2,
			std::abs(enemyPosition.y + playerPosition.y) / 2),
		CollisionBase(
			const_cast<Vector2&>(enemyPosition),
			const_cast<Vector2&>(playerPosition)
			)
		),
	enemyPosition_(enemyPosition),
	playerPosition_(playerPosition),
	blockPosition_(Vector2::Zero)
{
}

void PlayerSearchObj::onUpdate(float deltaTime)
{
	position_ = body_.setSegmentPoint(
		position_, enemyPosition_, playerPosition_);
}

void PlayerSearchObj::onDraw() const
{
	// body_.setSegmentPoint(enemyPosition_, playerPosition_)
	DrawFormatString(25, 75, GetColor(255, 255, 255),
		"プレイヤーとの線分:X%d, Y%d",
		(int)position_.x,
		(int)position_.y);
	body_.draw(inv_);
}

void PlayerSearchObj::onCollide(Actor & actor)
{
	// 床に当たっていたら、位置を代入
	if (actor.getName() == "MovelessFloor") {
		blockPosition_ = actor.position_;
		return;
	}
}

// 敵とプレイヤーの位置を設定します
void PlayerSearchObj::setPosition(const Vector2 & enemyPosition, const Vector2 & playerPosition)
{
	enemyPosition_ = enemyPosition;
	playerPosition_ = playerPosition;
}

// プレイヤーが見えているかを返します
bool PlayerSearchObj::isPlayerLook()
{
	auto blockLen = (enemyPosition_ - blockPosition_).Length();
	auto playerLen = (enemyPosition_ - playerPosition_).Length();
	// プレイヤーとの距離との距離が短かったら、trueを返す
	if (playerLen < blockLen)
		return true;
	return false;
}
