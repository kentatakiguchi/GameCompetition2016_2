#include "BossAreaFloor.h"
#include"../Input/InputMgr.h"

BossAreaFloor::BossAreaFloor(IWorld * world, Vector2 & position) :spriteID_(-1),
MapChip(world, Vector2(position.x, position.y), "BossAreaFloor", std::make_shared<BoundingBox>(Vector2(0, 0),Matrix::CreateRotationZ(0),CHIPSIZE,CHIPSIZE,true))
	//Vector2{ position.x,position.y },
	//Vector2{ position.x - (CHIPSIZE),position.y },
	//Vector2{ position.x ,position.y - (CHIPSIZE) },
	//Vector2{ position.x - (CHIPSIZE),position.y - (CHIPSIZE) }))
{
	rotate_ = 0;
}

BossAreaFloor::BossAreaFloor(int spriteID, IWorld * world, Vector2 & position) :spriteID_(spriteID),
MapChip(world, Vector2(position.x, position.y), "BossAreaFloor", std::make_shared<BoundingBox>(Vector2(0, 0), Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
	rotate_ = 0;
}

BossAreaFloor::BossAreaFloor(std::shared_ptr<BossAreaFloor> chip, IWorld * world, Vector2 & position) :spriteID_(-1),
MapChip(world, Vector2(position.x, position.y), "BossAreaFloor", std::make_shared<BoundingBox>(Vector2(0, 0), Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
	rotate_ = 0;
}

BossAreaFloor::BossAreaFloor(BossAreaFloor & chip, IWorld * world, Vector2 & position) :spriteID_(-1),
MapChip(world, Vector2(position.x, position.y), "BossAreaFloor", std::make_shared<BoundingBox>(Vector2(0, 0), Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
	rotate_ = 0;
}

void BossAreaFloor::set(Vector2 & pos)
{
	position_ = pos;
	body_ = std::make_shared<BoundingBox>(Vector2(0, 0), rotation_, CHIPSIZE, CHIPSIZE, true);
}

void BossAreaFloor::onUpdate(float deltaTime)
{

}

void BossAreaFloor::onDraw() const
{
	//spriteID_ == -1 ? body_.draw(inv_) : 
	body_->draw(spriteID_, rotate_, inv_);
}

void BossAreaFloor::onCollide(Actor & other)
{
}
