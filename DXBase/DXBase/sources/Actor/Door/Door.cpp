#include "Door.h"
#include "../../Define.h"
Door::Door(IWorld * world, const Vector2 & position):
	Actor(world,"Door",position,
		CollisionBase(position,position+Vector2(CHIPSIZE,0.0f),position+Vector2(0.0f,CHIPSIZE),position+Vector2(CHIPSIZE,CHIPSIZE))),
	mDoorFlag(false)
{
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
		body_.draw(inv_);
		//DrawBox(pos.x, pos.y, (pos + Vector2(CHIPSIZE, CHIPSIZE)).x, (pos + Vector2(CHIPSIZE, CHIPSIZE)).y, GetColor(255, 255, 255), TRUE);
}

void Door::onCollide(Actor & other)
{

}

void Door::DoorOpen(bool openFlag)
{
	mDoorFlag = openFlag;
	body_.enabled(!openFlag);
}
