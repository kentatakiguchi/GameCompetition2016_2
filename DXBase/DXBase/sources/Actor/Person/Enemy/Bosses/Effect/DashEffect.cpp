#include "DashEffect.h"

DashEffect::DashEffect(IWorld * world, const Vector2 & position) :
	BossEffect(world, "DashEffect", position - Vector2(200, 200),
		EFFECT_DASH, AnimationID::BOSS_EFFECT_DASH_TEX)
{
	animation_.changeAnimation(EFFECT_DASH, 10.0f);
}
