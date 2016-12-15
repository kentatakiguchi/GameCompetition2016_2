#include "PiyoriEffect.h"

PiyoriEffect::PiyoriEffect(
	IWorld * world,
	const Vector2 & position):
	BossEffect(world, "PiyoriEffect", position - Vector2(200, 200),
		EFFECT_PIYO, TextureID::BOSS_EFFECT_PIYO_TEX,
		Vector2(256, 256), Vector2(8, 7))
{
}

void PiyoriEffect::onUpdate(float deltaTime){
	animation_.update(deltaTime);
}
