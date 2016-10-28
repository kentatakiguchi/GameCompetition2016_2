#include "ScroolStop.h"
#include "../../World/IWorld.h"
#include "../Body/CollisionBase.h"
ScroolStop::ScroolStop(IWorld* world, const Vector2& position, StopDirection dire) :
	Actor(world, "ScroolStopPoint", Vector3(position.x, position.y, 0.0f), CollisionBase()),
	mDire(dire),
	sceneInFlag(Vector2::Zero)
{
}

ScroolStop::~ScroolStop()
{
}

void ScroolStop::onUpdate(float deltaTime)
{
	//ÉtÉâÉOÇèâä˙âª
	sceneInFlag = Vector2::Zero;
	switch (mDire)
	{
	case RIGHT: {
		if (position_.x <= 800.0f)
			sceneInFlag.x = TRUE;
		break;
	}
	case LEFT: {
		if (position_.x >= 0.0f)
			sceneInFlag.x = TRUE;
		break;
	}
	case TOP: {
		if (position_.y >= 0)
			sceneInFlag.y = TRUE;
		break;
	}
	case BOT: {
		if (position_.y <= 600)
			sceneInFlag.y = TRUE;
		break;
	}
	}
}

void ScroolStop::onDraw() const
{
	DrawCircle(position_.x, position_.y, 20, GetColor(255, 0, 255), true, true);
}

void ScroolStop::onCollide(Actor & other)
{
}
