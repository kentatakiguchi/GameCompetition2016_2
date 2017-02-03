#ifndef BOSS_WING_EFFECT_H_
#define BOSS_WING_EFFECT_H_

#include "../../../../Base/Actor.h"

class BossWingEffect : public Actor {
private:
	enum class State {
		FlyOut,
		Fall,
		Dead
	};

public:
	BossWingEffect(IWorld* world, const Vector2& position);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;

//private:

};

#endif
