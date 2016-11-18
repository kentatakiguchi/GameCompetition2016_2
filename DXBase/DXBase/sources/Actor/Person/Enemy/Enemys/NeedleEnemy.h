#ifndef NEEDLE_ENEMY_H_
#define NEEDLE_ENEMY_H_

#include "../BaseEnemy.h"

// 針クラス(何もしない。障害物)
class NeedleEnemy : public BaseEnemy {
public:
	NeedleEnemy(
		IWorld * world,
		const Vector2& position,
		const float degress);
	void update(float deltaTime) override;
	void onDraw() const;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	// 待機状態です
	void idel();

private:
	float degress_;
};

#endif
