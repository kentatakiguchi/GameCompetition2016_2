#include "HelperUI.h"

HelperUI::HelperUI(IWorld * world, const Vector2 & position) :
	 ActorUI(world, position)
{
	drawTex_.clear();
}

void HelperUI::onUpdate(float deltaTime)
{
}

void HelperUI::onDraw() const
{
}
