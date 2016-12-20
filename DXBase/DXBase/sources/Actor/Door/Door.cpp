#include "Door.h"
#include "../../Define.h"
Door::Door(IWorld * world, const Vector2 & position):
	Actor(world,"Door",position,
		std::make_shared<BoundingBox>(position,Matrix::Identity,CHIPSIZE,CHIPSIZE,true))
	,mDoorFlag(true)
{
	body_->enabled(false);
}

Door::~Door()
{
}

void Door::onUpdate(float deltaTime)
{

}

void Door::onDraw() const
{
	Vector2 pos = position_*inv_;

	if (!mDoorFlag)
		body_->draw(-1,inv_);
		//DrawBox(pos.x, pos.y, (pos + Vector2(CHIPSIZE, CHIPSIZE)).x, (pos + Vector2(CHIPSIZE, CHIPSIZE)).y, GetColor(255, 255, 255), TRUE);
}

void Door::onCollide(Actor & other)
{

}

void Door::DoorOpen(bool openFlag)
{
	mDoorFlag = openFlag;
}
