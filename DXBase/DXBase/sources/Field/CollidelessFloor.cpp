#include "CollidelessFloor.h"
#include"../Input/InputMgr.h"

CollidelessFloor::CollidelessFloor(IWorld * world, Vector2 & position) :spriteID_(-1),
MapChip(world, Vector2(position.x, position.y), "CollidelessFloor", std::make_shared<BoundingBox>())
{
	rotate_ = 0;
}

CollidelessFloor::CollidelessFloor(int spriteID, IWorld * world, Vector2 & position) :spriteID_(spriteID),
MapChip(world, Vector2(position.x, position.y), "CollidelessFloor", std::make_shared<BoundingBox>())
{
	rotate_ = 0;
}

CollidelessFloor::CollidelessFloor(std::shared_ptr<CollidelessFloor> chip, IWorld * world, Vector2 & position) :spriteID_(-1),
MapChip(world, Vector2(position.x, position.y), "CollidelessFloor", std::make_shared<BoundingBox>())
{
	rotate_ = 0;
}

CollidelessFloor::CollidelessFloor(CollidelessFloor & chip, IWorld * world, Vector2 & position) :spriteID_(-1),
MapChip(world, Vector2(position.x, position.y), "CollidelessFloor", std::make_shared<BoundingBox>())
{
	rotate_ = 0;
}

void CollidelessFloor::set(Vector2 & pos)
{
	position_ = pos;
	body_ = std::make_shared<BoundingBox>(position_, rotation_, body_->width(), body_->height(), true);
}

void CollidelessFloor::onUpdate(float deltaTime)
{
}

void CollidelessFloor::onDraw() const
{
	spriteID_ == -1 ? body_->draw(-1,inv_) : body_->draw(spriteID_, rotate_, inv_);
}

void CollidelessFloor::onCollide(Actor & other)
{

}
