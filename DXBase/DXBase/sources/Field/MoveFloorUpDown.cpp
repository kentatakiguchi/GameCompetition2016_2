#include "MoveFloorUpDown.h"

MoveFloorUpDown::MoveFloorUpDown(IWorld * world, Vector2 & position):
	MapChip(world, Vector2(position.x, position.y), CollisionBase(
	Vector2{ position.x,position.y },
	Vector2{ position.x - (CHIPSIZE*2),position.y },
	Vector2{ position.x ,position.y - (CHIPSIZE) },
	Vector2{ position.x - (CHIPSIZE*2),position.y - (CHIPSIZE) }))
	,defaultPos_(position),moveVelocity(1),moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

MoveFloorUpDown::MoveFloorUpDown(std::shared_ptr<MoveFloorUpDown> chip, IWorld * world, Vector2 & position):
	MapChip(world, Vector2(position.x, position.y), CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE*2),position.y },
		Vector2{ position.x ,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE*2),position.y - (CHIPSIZE) }
		))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

MoveFloorUpDown::MoveFloorUpDown(MoveFloorUpDown & chip, IWorld * world, Vector2 & position):
	MapChip(world, Vector2(position.x, position.y), CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE*2),position.y },
		Vector2{ position.x,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE*2),position.y - (CHIPSIZE) }
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
		Vector2{ pos.x + (CHIPSIZE*2),pos.y },
		Vector2{ pos.x ,pos.y + (CHIPSIZE) },
		Vector2{ pos.x + (CHIPSIZE*2),pos.y + (CHIPSIZE) });
}

void MoveFloorUpDown::onUpdate(float deltaTime)
{
	moveCount_ += moveVelocity;
	if (moveCount_<=0) {
		moveVelocity = 1;
	}
	if (moveCount_>= CHIPSIZE*UPDOWNRANGE) {
		moveVelocity = -1;
	}
	position_.y += moveVelocity;
}

void MoveFloorUpDown::onDraw() const
{
	body_.draw();
}

void MoveFloorUpDown::onCollide(Actor & other)
{
}
