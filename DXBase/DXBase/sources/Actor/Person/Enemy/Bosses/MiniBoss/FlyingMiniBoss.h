#ifndef FLYING_MINI_BOSS_H_
#define FLYING_MINI_BOSS_H_

#include "AdhereMiniBoss.h"

class FlyingMiniBoss : public AdhereMiniBoss{
public:
	FlyingMiniBoss(
		IWorld* world, 
		const Vector2&  position, 
		const Vector2& direction = Vector2::One,
		const float bodyScale = 64.0f);

private:
	// ˆÚ“®ó‘Ô
	void move(float deltaTime) override;
	// °‚É“–‚½‚Á‚½‚Ìˆ—
	void floorHit() override;

private:
	float deg_;				// Šp“x(e‚Ì•Ï”–¼‚à•ÏX‚·‚é)
	Vector2 direction_;		// •ûŒü
};

#endif
