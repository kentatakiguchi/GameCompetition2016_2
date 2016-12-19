#include "MoveFloorCenterUpDown.h"

MoveFloorCenterUpDown::MoveFloorCenterUpDown(IWorld * world, Vector2 & position) :spriteID_(-1),
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
	rotate_ = 0;
}
MoveFloorCenterUpDown::MoveFloorCenterUpDown(int spriteID,IWorld * world, Vector2 & position) :spriteID_(spriteID),
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

MoveFloorCenterUpDown::MoveFloorCenterUpDown(std::shared_ptr<MoveFloorCenterUpDown> chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

MoveFloorCenterUpDown::MoveFloorCenterUpDown(MoveFloorCenterUpDown & chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "MoveFloorUpDown", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*UPDOWNRANGE)
{
}

void MoveFloorCenterUpDown::set(Vector2 & pos)
{
	position_ = pos;
	defaultPos_ = pos;
	body_ = std::make_shared<BoundingBox>(position_, rotation_, CHIPSIZE, CHIPSIZE, true);
}

void MoveFloorCenterUpDown::onUpdate(float deltaTime)
{
	moveCount_ += moveVelocity*ceilf(deltaTime);
	if (moveCount_ <= -(CHIPSIZE*UPDOWNRANGE)) {
		moveVelocity = UDMoveSpeed;
	}
	if (moveCount_ >= CHIPSIZE*UPDOWNRANGE) {
		moveVelocity = -UDMoveSpeed;
	}
	position_.y += moveVelocity*ceilf(deltaTime);
}

void MoveFloorCenterUpDown::onDraw() const
{
	spriteID_ == -1 ? body_->draw(-1,inv_) : body_->draw(spriteID_, rotate_, inv_);
}

void MoveFloorCenterUpDown::onCollide(Actor & other)
{
}
