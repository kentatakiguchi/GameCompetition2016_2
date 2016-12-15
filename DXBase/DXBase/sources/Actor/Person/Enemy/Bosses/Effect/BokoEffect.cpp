#include "BokoEffect.h"

BokoEffect::BokoEffect(
	IWorld * world,
	const Vector2 & position) : 
	BossEffect(world, "BokoEffect", position - Vector2(200, 200),
		EFFECT_BOKO, TextureID::BOSS_EFFECT_BOKO_TEX,
		Vector2(512, 512), Vector2(5, 6))
{
}
