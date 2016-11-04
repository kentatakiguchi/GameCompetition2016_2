#ifndef WALL_TRUN_ENEMY_H
#define WALL_TRUN_ENEMY_H

#include "../BaseEnemy.h"

class FloorSearchPoint;

class WallTrunEnemy : public BaseEnemy {
public:
	WallTrunEnemy(IWorld * world, const Vector2& position);
	void onUpdate(float deltaTime) override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	// 待機状態です
	void idel();
	// 索敵移動です
	void search();
	// 攻撃行動です
	void attack();
	// 索敵時の行動です
	void searchMove();
	// 追跡時の行動です
	void chaseMove();

private:
	FloorSearchPoint* wsObj_;
};

#endif
