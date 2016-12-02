#ifndef SAMPLE_BOSS_H_
#define SAMPLE_BOSS_H_

#include "BaseBoss.h"
//#include "../../../../Animation/Base/Animation2D.h"
//#include "../../../../World/IWorld.h"
//#include "../../../../Math/Math.h"
//#include "../../../../Define.h"

class Tornado;

class SampleBoss : public BaseBoss{
public:
	SampleBoss(IWorld* world, const Vector2&  position);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	// ë“ã@èÛë‘
	void idel(float deltaTime) override;

private:
	Tornado* tornado_;

};

#endif
