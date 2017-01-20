#ifndef BOKO_EFFECT_H_
#define BOKO_EFFECT_H_

#include "BossEffect.h"

class BokoEffect : public BossEffect {
public:
	BokoEffect(
		IWorld* world,
		const Vector2&  position,
		float speed = 1.0f);

};

#endif
