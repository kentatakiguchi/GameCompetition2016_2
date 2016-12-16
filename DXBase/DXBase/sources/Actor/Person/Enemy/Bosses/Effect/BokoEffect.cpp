#include "BokoEffect.h"

BokoEffect::BokoEffect(
	IWorld * world,
	const Vector2 & position) : 
	BossEffect(world, "BokoEffect", position - Vector2(200, 200),
		EFFECT_BOKO, AnimationID::BOSS_EFFECT_BOKO_TEX)
{}
