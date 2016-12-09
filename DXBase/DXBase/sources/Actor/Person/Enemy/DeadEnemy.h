#ifndef DEADENEMY_H_
#define DEADENEMY_H_

#include "../../Base/Actor.h"

class DeadEnemy :public Actor {
public:
	DeadEnemy(
		IWorld* world,
		const Vector2& position,
		const Vector2& bodyScale,
		const Vector2& direction = Vector2(1.0f, 1.0f));


};

#endif
