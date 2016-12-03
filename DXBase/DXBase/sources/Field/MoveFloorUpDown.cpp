#include "MoveFloorUpDown.h"

MoveFloorUpDown::MoveFloorUpDown(IWorld * world, Vector2 & position):
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", CollisionBase(
	Vector2{ position.x,position.y },
	Vector2{ position.x - (CHIPSIZE),position.y },
	Vector2{ position.x ,position.y - (CHIPSIZE) },
	Vector2{ position.x - (CHIPSIZE),position.y - (CHIPSIZE) }))
	,defaultPos_(position),moveVelocity(1),moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

MoveFloorUpDown::MoveFloorUpDown(std::shared_ptr<MoveFloorUpDown> chip, IWorld * world, Vector2 & position):
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE),position.y },
		Vector2{ position.x ,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE),position.y - (CHIPSIZE) }
		))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

MoveFloorUpDown::MoveFloorUpDown(MoveFloorUpDown & chip, IWorld * world, Vector2 & position):
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE),position.y },
		Vector2{ position.x,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE),position.y - (CHIPSIZE) }
		))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

void MoveFloorUpDown::set(Vector2 & pos)
{
	position_ = pos;
	defaultPos_ = pos;
	body_ = CollisionBase(
		Vector2{ pos.x ,pos.y },
		Vector2{ pos.x + (CHIPSIZE),pos.y },
		Vector2{ pos.x ,pos.y + (CHIPSIZE) },
		Vector2{ pos.x + (CHIPSIZE),pos.y + (CHIPSIZE) });
}

void MoveFloorUpDown::onUpdate(float deltaTime)
{
	moveCount_ += moveVelocity*ceilf(deltaTime);
	if (moveCount_<=0) {
		moveVelocity = UDMoveSpeed;
	}
	if (moveCount_>= CHIPSIZE*UPDOWNRANGE) {
		moveVelocity = -UDMoveSpeed;
	}
	position_.y += moveVelocity*ceilf(deltaTime);
}

void MoveFloorUpDown::onDraw() const
{
	body_.draw(inv_);
}

void MoveFloorUpDown::onCollide(Actor & other)
{
}
