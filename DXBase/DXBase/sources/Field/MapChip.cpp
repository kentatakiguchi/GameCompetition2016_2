#include "MapChip.h"

MapChip::MapChip(IWorld * world, Vector2 & position):rotate_(0),
	Actor(world, "MapChip", Vector2(position.x, position.y), std::make_shared<BoundingBox>(Vector2(0, 0), Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
}
MapChip::MapChip(IWorld * world, Vector2 & position,const IBodyPtr& base) :
	Actor(world, "MapChip", Vector2(position.x, position.y),base)
{

}

MapChip::MapChip(IWorld * world, Vector2 & position, std::string name,const IBodyPtr & base):
	rotate_(0),Actor(world,name, Vector2(position.x, position.y), base){
}


MapChip::MapChip(std::shared_ptr<MapChip> chip,IWorld* world, Vector2 & position)
	:Actor(world, "MapChip", Vector2(position.x, position.y), std::make_shared<BoundingBox>(Vector2(0, 0),Matrix::CreateRotationZ(0),CHIPSIZE,CHIPSIZE,true))
{

}

MapChip::MapChip(MapChip& chip,IWorld* world, Vector2 & position)
	:Actor(world, "MapChip", Vector2(position.x, position.y), std::make_shared<BoundingBox>(Vector2(0, 0),Matrix::CreateRotationZ(rotate_),CHIPSIZE,CHIPSIZE,true))
{
}

void MapChip::set(Vector2& pos)
{
	position_ = pos;
	body_ = std::make_shared<BoundingBox>(Vector2(0, 0),Matrix::CreateRotationZ(rotate_),CHIPSIZE,CHIPSIZE,true);
}

void MapChip::onUpdate(float deltaTime)
{
}

void MapChip::onDraw() const
{
	body_->draw(-1,inv_);
}

void MapChip::onCollide(Actor & other)
{
}
