#ifndef WALL_TRUN_ENEMY_H
#define WALL_TRUN_ENEMY_H

#include "../BaseEnemy.h"

class FloorSearchPoint;

class WallTrunEnemy : public BaseEnemy {
public:
	WallTrunEnemy(IWorld * world, const Vector2& position);
	virtual void onUpdate(float deltaTime) override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

private:
	// ‘Ò‹@ó‘Ô‚Å‚·
	void idel();
	// õ“GˆÚ“®‚Å‚·
	void search();
	// UŒ‚s“®‚Å‚·
	void Attack();
	// õ“G‚Ìs“®‚Å‚·
	void searchMove();
	// ’ÇÕ‚Ìs“®‚Å‚·
	void chaseMove();

private:
	FloorSearchPoint* wsObj_;
};

#endif
