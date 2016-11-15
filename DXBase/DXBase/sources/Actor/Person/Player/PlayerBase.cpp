#include "PlayerBase.h"

PlayerBase::PlayerBase(IWorld * world, const Vector2 & position)
{
}

PlayerBase::~PlayerBase()
{
}

void PlayerBase::onUpdate(float deltaTime)
{
}

void PlayerBase::onLateUpdate(float deltaTime)
{
}

void PlayerBase::onDraw() const
{
}

void PlayerBase::onCollide(Actor & other)
{
}

void PlayerBase::setBody(PlayerBodyPtr main, PlayerBodyPtr sub)
{
}

PlayerBodyPtr PlayerBase::getMainBody()
{
	return PlayerBodyPtr();
}

PlayerBodyPtr PlayerBase::getSubBody()
{
	return PlayerBodyPtr();
}
