#ifndef TORNADO_H_
#define TORNADO_H_

#include "../../../Base/Actor.h"

// 竜巻クラス(竜巻の基点を位置としています)
class Tornado : public Actor {
public:
	Tornado(IWorld* world, const Vector2&  position, const float bodyScale);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;
};

#endif
