#include "MoveFloorUpDown.h"

MoveFloorUpDown::MoveFloorUpDown(IWorld * world, Vector2 & position) :spriteID_(-1),
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
	rotate_ = 0;
}
MoveFloorUpDown::MoveFloorUpDown(int spriteID,IWorld * world, Vector2 & position) :spriteID_(spriteID),
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

MoveFloorUpDown::MoveFloorUpDown(std::shared_ptr<MoveFloorUpDown> chip, IWorld * world, Vector2 & position):
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

MoveFloorUpDown::MoveFloorUpDown(MoveFloorUpDown & chip, IWorld * world, Vector2 & position):
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

void MoveFloorUpDown::set(Vector2 & pos)
{
	position_ = pos;
	defaultPos_ = pos;
	body_ = std::make_shared<BoundingBox>(position_, rotation_, CHIPSIZE, CHIPSIZE, true);
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
	spriteID_ == -1 ? body_->draw(-1,inv_) : body_->draw(spriteID_, rotate_, inv_);
}

void MoveFloorUpDown::onCollide(Actor & other)
{
}
