#ifndef DASH_EFFECT_H_
#define DASH_EFFECT_H_

#include "BossEffect.h"

class DashEffect : public BossEffect {
public:
	DashEffect(
		IWorld* world,
		const Vector2&  position);
};

#endif