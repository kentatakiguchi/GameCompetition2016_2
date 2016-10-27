#ifndef FLOOR_TURN_ENEMY_H_
#define FLOOR_TURN_ENEMY_H_

#include "../BaseEnemy.h"

class FloorSearchPoint;

class FloorTurnEnemy : public BaseEnemy {
public:
	FloorTurnEnemy(IWorld * world, const Vector3& position);
	virtual void onUpdate(float deltaTime) override;
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
	FloorSearchPoint* fspObj_;
};

#endif