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
	samplePos_(Vector2::Zero)
{
}

void PlayerSearchObj::onUpdate(float deltaTime)
{
	/*auto pos = Vector2(
		std::abs(enemyPosition_.x + playerPosition_.x) / 2,
		std::abs(enemyPosition_.y + playerPosition_.y) / 2
		);*/
	//position_ = pos;
	//body_.GetSegment().translate(pos);
	//body_.GetSegment().transform(enemyPosition_, playerPosition_);
	/*auto pos = Vector2(
		std::abs(.x),
		std::abs(body_.setSegmentPoint(enemyPosition_, playerPosition_).y)
		);*/

	// position = 始点の位置
	position_ = enemyPosition_;
	body_.setSegmentPoint(const_cast<Vector2&>(Vector2::Zero), playerPosition_ - enemyPosition_);
	/*position_ = Vector2::Zero;
	body_.setSegmentPoint(enemyPosition_, playerPosition_);*/

	/*position_ = enemyPosition_;
	body_.setSegmentPoint(enemyPosition_, playerPosition_);*/

	//position_ = Vector2::Zero;
	//samplePos_ = body_.setSegmentPoint(const_cast<Vector2&>(Vector2::Zero), playerPosition_);
}

void PlayerSearchObj::onDraw() const
{
	// body_.setSegmentPoint(enemyPosition_, playerPosition_)
	DrawFormatString(25, 75, GetColor(255, 255, 255),
		"プレイヤーとの線分:X%d, Y%d",
		(int)position_.x,
		(int)position_.y);
	body_.draw();
}

void PlayerSearchObj::onCollide(Actor & actor)
{
}

// 敵とプレイヤーの位置を設定します
void PlayerSearchObj::setPosition(const Vector2 & enemyPosition, const Vector2 & playerPosition)
{
	enemyPosition_ = enemyPosition;
	playerPosition_ = playerPosition;
}
