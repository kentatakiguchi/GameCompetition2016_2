#include "MoveFloorCenterRightLeft.h"

MoveFloorCenterRightLeft::MoveFloorCenterRightLeft(IWorld * world, Vector2 & position) :spriteID_(-1),
	MapChip(world, Vector2(position.x, position.y), "MoveFloorRightLeft", std::make_shared<BoundingBox>(Vector2(0, 0), Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true)),
	defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*RIGHTLEFTRANGE)
{
	rotate_ = 0;
}
MoveFloorCenterRightLeft::MoveFloorCenterRightLeft(int spriteID,IWorld * world, Vector2 & position) :spriteID_(spriteID),
	MapChip(world, Vector2(position.x, position.y), "MoveFloorRightLeft", std::make_shared<BoundingBox>(Vector2(0, 0), Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*RIGHTLEFTRANGE)
{
}

MoveFloorCenterRightLeft::MoveFloorCenterRightLeft(std::shared_ptr<MoveFloorCenterRightLeft> chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "MoveFloorRightLeft", std::make_shared<BoundingBox>(Vector2(0, 0), Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*RIGHTLEFTRANGE)
{
}

MoveFloorCenterRightLeft::MoveFloorCenterRightLeft(MoveFloorCenterRightLeft & chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "MoveFloorRightLeft", std::make_shared<BoundingBox>(Vector2(0, 0), Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*RIGHTLEFTRANGE)
{
}

void MoveFloorCenterRightLeft::set(Vector2 & pos)
{
	position_ = pos;
	defaultPos_ = pos;
	body_ = std::make_shared<BoundingBox>(Vector2(0, 0), rotation_, CHIPSIZE, CHIPSIZE, true);
}

void MoveFloorCenterRightLeft::onUpdate(float deltaTime)
{
	moveCount_ += moveVelocity*ceilf(deltaTime);
	if (moveCount_ <= -(CHIPSIZE*RIGHTLEFTRANGE)) {
		moveVelocity = LRMoveSpeed;
	}
	if (moveCount_ >= CHIPSIZE*RIGHTLEFTRANGE) {
		moveVelocity = -LRMoveSpeed;
	}
	position_.x += moveVelocity*ceilf(deltaTime);
}

void MoveFloorCenterRightLeft::onDraw() const
{
	spriteID_ == -1 ? body_->draw(-1,inv_) : body_->draw(spriteID_, rotate_, inv_);
}

void MoveFloorCenterRightLeft::onCollide(Actor & other)
{
}
