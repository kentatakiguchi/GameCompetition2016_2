#include "SticklessFloor.h"
#include"../Input/InputMgr.h"

SticklessFloor::SticklessFloor(IWorld * world, Vector2 & position) :spriteID_(-1),
MapChip(world, Vector2(position.x, position.y), "SticklessFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
	rotate_ = 0;
}

SticklessFloor::SticklessFloor(int spriteID, IWorld * world, Vector2 & position) :spriteID_(spriteID),
MapChip(world, Vector2(position.x, position.y), "SticklessFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
	rotate_ = 0;
}

SticklessFloor::SticklessFloor(std::shared_ptr<SticklessFloor> chip, IWorld * world, Vector2 & position) :spriteID_(-1),
MapChip(world, Vector2(position.x, position.y), "SticklessFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
	rotate_ = 0;
}

SticklessFloor::SticklessFloor(SticklessFloor & chip, IWorld * world, Vector2 & position) :spriteID_(-1),
MapChip(world, Vector2(position.x, position.y), "SticklessFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
	rotate_ = 0;
}

void SticklessFloor::set(Vector2 & pos)
{
	position_ = pos;
	body_ = std::make_shared<BoundingBox>(pos, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true);
}

void SticklessFloor::onUpdate(float deltaTime)
{

}

void SticklessFloor::onDraw() const
{
	if (isOutCamera())return;

	spriteID_ == -1 ? body_->draw(-1,inv_) : body_->draw(spriteID_, rotate_, inv_);
}

void SticklessFloor::onCollide(Actor & other)
{
}
