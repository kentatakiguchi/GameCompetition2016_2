#include "PiyoriEffect.h"

PiyoriEffect::PiyoriEffect(
	IWorld * world,
	const Vector2 & position):
	BossEffect(world, "PiyoriEffect", position, Vector2(256, 256),
		EFFECT_PIYO, AnimationID::BOSS_EFFECT_PIYO_TEX)
{}

void PiyoriEffect::onUpdate(float deltaTime){
	animation_.update(deltaTime);
}
