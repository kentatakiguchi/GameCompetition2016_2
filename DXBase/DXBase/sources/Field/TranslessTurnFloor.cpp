#include "TranslessTurnFloor.h"

TranslessTurnFloor::TranslessTurnFloor(IWorld * world, Vector2 & position) :spriteID_(-1),
	MapChip(world, Vector2(position.x, position.y), "TranslessTurnFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNSPEED)
{
}
TranslessTurnFloor::TranslessTurnFloor(int spriteID,IWorld * world, Vector2 & position) :spriteID_(spriteID),
	MapChip(world, Vector2(position.x, position.y), "TranslessTurnFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNSPEED)
{
}

TranslessTurnFloor::TranslessTurnFloor(std::shared_ptr<TranslessTurnFloor> chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "TranslessTurnFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNSPEED)
{
}

TranslessTurnFloor::TranslessTurnFloor(TranslessTurnFloor & chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "TranslessTurnFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNSPEED)
{
}

void TranslessTurnFloor::set(Vector2 & pos)
{
	position_ = pos;
	defaultPos_ = pos;
	body_ = std::make_shared<BoundingBox>(pos, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true);
}

void TranslessTurnFloor::onUpdate(float deltaTime)
{
	moveCount_+=1*ceilf(deltaTime);
	if (moveCount_ % 360 == 0) {
		moveCount_ = 0;
	}
	//body_.RotateBox(moveCount_);
	rotate_ = moveCount_;
}

void TranslessTurnFloor::onDraw() const
{
	spriteID_ == -1 ? body_->draw(-1,inv_) : body_->draw(spriteID_, rotate_, inv_);
}

void TranslessTurnFloor::onCollide(Actor & other)
{
}
