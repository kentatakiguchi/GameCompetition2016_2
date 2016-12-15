#ifndef PENDULUM_ENEMY_H_
#define PENDULUM_ENEMY_H_

#include "../BaseEnemy.h"

class PendulumEnemy : public BaseEnemy {
public:
	PendulumEnemy(IWorld * world, const Vector3& position);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

private:
	// 待機状態です
	void idel();
	// 攻撃行動です
	void Attack();
	// 索敵時の行動です
	void searchMove();
	// 追跡時の行動です
	void chaseMove();

private:
	Vector3 threadPoint_;
	std::string rotateStr_;
};

#endif
