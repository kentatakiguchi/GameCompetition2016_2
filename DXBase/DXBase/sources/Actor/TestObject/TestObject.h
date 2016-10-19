#ifndef TEST_OBJECT_H_
#define TEST_OBJECT_H_

#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include "../../Math/Vector3.h"
// プレーヤー
class TestObject : public Actor {
public:
	TestObject(IWorld* world, const Vector3& position);
	~TestObject();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
private:

	Vector2 mVelo;                              //プレイヤーの速度
};

#endif
