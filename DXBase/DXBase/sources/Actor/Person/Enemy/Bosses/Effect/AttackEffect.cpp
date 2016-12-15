#include "AttackEffect.h"

AttackEffect::AttackEffect(
	IWorld * world,
	const Vector2 & position) :
	BossEffect(world, position - Vector2(200, 200), EFFECT_BOKO, TextureID::BOSS_EFFECT_BOKO_TEX, Vector2(5, 6))
{}

//// アニメーションの追加を行います
//void AttackEffect::addAnimation()
//{
//
//}

//void AttackEffect::onUpdate(float deltaTime)
//{
//}
//
//void AttackEffect::onDraw() const
//{
//}
