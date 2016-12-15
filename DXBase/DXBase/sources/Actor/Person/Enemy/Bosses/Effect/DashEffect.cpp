#include "DashEffect.h"

DashEffect::DashEffect(IWorld * world, const Vector2 & position) :
	BossEffect(world, "DashEffect", position - Vector2(200, 200),
		EFFECT_DASH, TextureID::BOSS_EFFECT_DASH_TEX,
		Vector2(256, 256), Vector2(9, 7))
{
	animation_.changeAnimation(EFFECT_DASH, 10.0f);
}
