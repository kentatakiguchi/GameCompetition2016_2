#include "Door.h"
#include "../../Define.h"
Door::Door(IWorld * world, const Vector2 & position):
	Actor(world,"Door",position,
		CollisionBase(
			Vector2{ position.x,position.y },
			Vector2{ position.x - (CHIPSIZE),position.y },
			Vector2{ position.x ,position.y - (CHIPSIZE) },
			Vector2{ position.x - (CHIPSIZE),position.y - (CHIPSIZE) })),
	mDoorFlag(true)
{
	body_.enabled(false);
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
}
