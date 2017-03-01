#ifndef BOSS_SCROLL_POINT_H_
#define BOSS_SCROLL_POINT_H_

#include "../../../../../Base/Actor.h"

class BossScrollPoint : public Actor {
public:
	BossScrollPoint(
		IWorld* world,
		const Vector2& position);
	void onUpdate(float deltaTime) override;
};

#endif