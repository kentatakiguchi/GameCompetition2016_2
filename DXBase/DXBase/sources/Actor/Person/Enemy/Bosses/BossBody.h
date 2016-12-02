#ifndef BOSS_BODY_H_
#define BOSS_BODY_H_

#include "../../../Base/Actor.h"

class BossBody : public Actor {
public:
	BossBody(IWorld* world, const Vector2&  position);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;
};

#endif