#include "TurnFloor.h"

TurnFloor::TurnFloor(IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "TurnFloor", CollisionBase(
		Vector2{ position.x,position.y },
		Vector2{ position.x - (CHIPSIZE * 2),position.y },
		Vector2{ position.x ,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE * 2),position.y - (CHIPSIZE) }))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNRANGE)
{
}

TurnFloor::TurnFloor(std::shared_ptr<TurnFloor> chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "TurnFloor", CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE * 2),position.y },
		Vector2{ position.x ,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE * 2),position.y - (CHIPSIZE) }
		))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNRANGE)
{
}

TurnFloor::TurnFloor(TurnFloor & chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "TurnFloor", CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE * 2),position.y },
		Vector2{ position.x,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE * 2),position.y - (CHIPSIZE) }
		))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNRANGE)
{
}

void TurnFloor::set(Vector2 & pos)
{
	position_ = pos;
	defaultPos_ = pos;
	body_ = CollisionBase(
		Vector2{ pos.x ,pos.y },
		Vector2{ pos.x + (CHIPSIZE * 2),pos.y },
		Vector2{ pos.x ,pos.y + (CHIPSIZE) },
		Vector2{ pos.x + (CHIPSIZE * 2),pos.y + (CHIPSIZE) });
}

void TurnFloor::onUpdate(float deltaTime)
{
	defaultPos_ = position_ - (moveVelocity*CHIPSIZE*TURNRANGE);

	moveCount_++;
	if (moveCount_ % 360 == 0) {
		moveCount_ = 0;
	}
	
	moveVelocity.x = cos(moveCount_*MathHelper::Pi/180);
	moveVelocity.y = sin(moveCount_*MathHelper::Pi / 180);

	position_ = defaultPos_ + (moveVelocity*CHIPSIZE*TURNRANGE);

}

void TurnFloor::onDraw() const
{
	body_.draw();
}

void TurnFloor::onCollide(Actor & other)
{
}
