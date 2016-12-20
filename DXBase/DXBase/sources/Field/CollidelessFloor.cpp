#include "CollidelessFloor.h"
#include"../Input/InputMgr.h"

CollidelessFloor::CollidelessFloor(IWorld * world, Vector2 & position) :spriteID_(-1),
MapChip(world, Vector2(position.x, position.y), "CollidelessFloor", CollisionBase())
{
	rotate_ = 0;
}

CollidelessFloor::CollidelessFloor(int spriteID, IWorld * world, Vector2 & position) :spriteID_(spriteID),
MapChip(world, Vector2(position.x, position.y), "CollidelessFloor", CollisionBase())
{
	rotate_ = 0;
}

CollidelessFloor::CollidelessFloor(std::shared_ptr<CollidelessFloor> chip, IWorld * world, Vector2 & position) :spriteID_(-1),
MapChip(world, Vector2(position.x, position.y), "CollidelessFloor", CollisionBase())
{
	rotate_ = 0;
}

CollidelessFloor::CollidelessFloor(CollidelessFloor & chip, IWorld * world, Vector2 & position) :spriteID_(-1),
MapChip(world, Vector2(position.x, position.y), "CollidelessFloor", CollisionBase())
{
	rotate_ = 0;
}

void CollidelessFloor::set(Vector2 & pos)
{
	position_ = pos;
	body_ = CollisionBase(
		Vector2{ pos.x ,pos.y },
		Vector2{ pos.x + (CHIPSIZE),pos.y },
		Vector2{ pos.x ,pos.y + (CHIPSIZE) },
		Vector2{ pos.x + (CHIPSIZE),pos.y + (CHIPSIZE) });
}

void CollidelessFloor::onUpdate(float deltaTime)
{
}

void CollidelessFloor::onDraw() const
{
	spriteID_ == -1 ? body_.draw(inv_) : body_.draw(spriteID_, rotate_, inv_);
}

void CollidelessFloor::onCollide(Actor & other)
{

}
