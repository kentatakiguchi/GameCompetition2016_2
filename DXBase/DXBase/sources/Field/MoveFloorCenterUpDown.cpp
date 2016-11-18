#include "MoveFloorCenterUpDown.h"

MoveFloorCenterUpDown::MoveFloorCenterUpDown(IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", CollisionBase(
		Vector2{ position.x,position.y },
		Vector2{ position.x - (CHIPSIZE * 2),position.y },
		Vector2{ position.x ,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE * 2),position.y - (CHIPSIZE) }))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

MoveFloorCenterUpDown::MoveFloorCenterUpDown(std::shared_ptr<MoveFloorCenterUpDown> chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE * 2),position.y },
		Vector2{ position.x ,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE * 2),position.y - (CHIPSIZE) }
		))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

MoveFloorCenterUpDown::MoveFloorCenterUpDown(MoveFloorCenterUpDown & chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE * 2),position.y },
		Vector2{ position.x,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE * 2),position.y - (CHIPSIZE) }
		))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

void MoveFloorCenterUpDown::set(Vector2 & pos)
{
	position_ = pos;
	defaultPos_ = pos;
	body_ = CollisionBase(
		Vector2{ pos.x ,pos.y },
		Vector2{ pos.x + (CHIPSIZE * 2),pos.y },
		Vector2{ pos.x ,pos.y + (CHIPSIZE) },
		Vector2{ pos.x + (CHIPSIZE * 2),pos.y + (CHIPSIZE) });
}

void MoveFloorCenterUpDown::onUpdate(float deltaTime)
{
	moveCount_ += moveVelocity*ceilf(deltaTime);
	if (moveCount_ <= -(CHIPSIZE*UPDOWNRANGE)) {
		moveVelocity = 1;
	}
	if (moveCount_ >= CHIPSIZE*UPDOWNRANGE) {
		moveVelocity = -1;
	}
	position_.y += moveVelocity*ceilf(deltaTime);
}

void MoveFloorCenterUpDown::onDraw() const
{
	body_.draw(inv_);
}

void MoveFloorCenterUpDown::onCollide(Actor & other)
{
}