#include "MovelessFloor.h"
#include"../Input/InputMgr.h"

MovelessFloor::MovelessFloor(IWorld * world, Vector2 & position) :spriteID_(-1),
	MapChip(world, Vector2(position.x, position.y), "MovelessFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
	rotate_ = 0;
}

MovelessFloor::MovelessFloor(int spriteID, IWorld * world, Vector2 & position):spriteID_(spriteID),
	MapChip(world, Vector2(position.x, position.y), "MovelessFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
	rotate_ = 0;
}

MovelessFloor::MovelessFloor(std::shared_ptr<MovelessFloor> chip, IWorld * world, Vector2 & position) :spriteID_(-1),
	MapChip(world, Vector2(position.x, position.y), "MovelessFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
	rotate_ = 0;
}

MovelessFloor::MovelessFloor(MovelessFloor & chip, IWorld * world, Vector2 & position) :spriteID_(-1),
	MapChip(world, Vector2(position.x, position.y), "MovelessFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
	rotate_ = 0;
}

void MovelessFloor::set(Vector2 & pos)
{
	position_ = pos;
	body_ = std::make_shared<BoundingBox>(position_, rotation_, CHIPSIZE, CHIPSIZE, true);
}

void MovelessFloor::onUpdate(float deltaTime)
{
	

}

void MovelessFloor::onDraw() const
{
	if (isOutCamera())return;

	spriteID_ == -1 ? body_->draw(-1,inv_) : body_->draw(spriteID_,rotate_,inv_);
}

void MovelessFloor::onCollide(Actor & other)
{
}
