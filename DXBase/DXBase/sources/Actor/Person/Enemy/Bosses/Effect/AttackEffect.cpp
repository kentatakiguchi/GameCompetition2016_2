#include "AttackEffect.h"

AttackEffect::AttackEffect(
	IWorld * world,
	const Vector2 & position) :
	BossEffect(world, "AttackEffect", position - Vector2(200, 200),
		EFFECT_ATTACK, AnimationID::BOSS_EFFECT_ATTACK_TEX)
{}

