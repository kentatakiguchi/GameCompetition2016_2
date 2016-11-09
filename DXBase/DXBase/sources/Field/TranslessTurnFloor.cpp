#include "TranslessTurnFloor.h"

TranslessTurnFloor::TranslessTurnFloor(IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "TranslessTurnFloor", CollisionBase(
		Vector2{ position.x,position.y },
		Vector2{ position.x - (CHIPSIZE * 2),position.y },
		Vector2{ position.x ,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE * 2),position.y - (CHIPSIZE) }))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNSPEED)
{
}

TranslessTurnFloor::TranslessTurnFloor(std::shared_ptr<TranslessTurnFloor> chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "TranslessTurnFloor", CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE * 2),position.y },
		Vector2{ position.x ,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE * 2),position.y - (CHIPSIZE) }
		))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNSPEED)
{
}

TranslessTurnFloor::TranslessTurnFloor(TranslessTurnFloor & chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "TranslessTurnFloor", CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE * 2),position.y },
		Vector2{ position.x,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE * 2),position.y - (CHIPSIZE) }
		))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNSPEED)
{
}

void TranslessTurnFloor::set(Vector2 & pos)
{
	position_ = pos;
	defaultPos_ = pos;
	body_ = CollisionBase(
		Vector2{ pos.x ,pos.y },
		Vector2{ pos.x + (CHIPSIZE * 2),pos.y },
		Vector2{ pos.x ,pos.y + (CHIPSIZE) },
		Vector2{ pos.x + (CHIPSIZE * 2),pos.y + (CHIPSIZE) });
}

void TranslessTurnFloor::onUpdate(float deltaTime)
{
	moveCount_++;
	if (moveCount_ % 360 == 0) {
		moveCount_ = 0;
	}
	body_.RotateBox(moveCount_);

}

void TranslessTurnFloor::onDraw() const
{
	body_.draw();
}

void TranslessTurnFloor::onCollide(Actor & other)
{
}