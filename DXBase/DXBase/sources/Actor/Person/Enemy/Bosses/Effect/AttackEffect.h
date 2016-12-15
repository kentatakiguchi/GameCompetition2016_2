#ifndef ATTACK_EFFECT_H_
#define ATTACK_EFFECT_H_

#include "BossEffect.h"

class AttackEffect : public BossEffect {
public:
	AttackEffect(
		IWorld* world,
		const Vector2&  position);
	/*void onUpdate(float deltaTime) override;
	void onDraw() const override;*/

//private:
//	// アニメーションの追加を行います
//	void addAnimation() override;
};

#endif
