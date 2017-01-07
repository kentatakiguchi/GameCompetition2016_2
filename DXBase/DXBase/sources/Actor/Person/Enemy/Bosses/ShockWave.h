#ifndef SHOCKWAVE_H_
#define SHOCKWAVE_H_

#include "../../../Base/Actor.h"
#include "../../../../World/IWorld.h"

class ShockWave : public Actor {
public:
	ShockWave(IWorld* world,
		const Vector2&  position,
		const Vector2& bodyScale);
	void onUpdate(float deltaTime) override;
	//void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	float timer_;
};

#endif
