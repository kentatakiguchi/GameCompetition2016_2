#ifndef TEST_PLAYER_H_
#define TEST_PLAYER_H_

#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include "../../Math/Vector3.h"
// ÉvÉåÅ[ÉÑÅ[
class TestPlayer : public Actor {
public:
	TestPlayer(IWorld* world, const Vector2& position);
	~TestPlayer();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
private:
	float time;
};

#endif
