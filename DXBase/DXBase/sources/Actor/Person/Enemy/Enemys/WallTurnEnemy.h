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
	// �ҋ@��Ԃł�
	void idel();
	// ���G�ړ��ł�
	void search();
	// �U���s���ł�
	void Attack();
	// ���G���̍s���ł�
	void searchMove();
	// �ǐՎ��̍s���ł�
	void chaseMove();

private:
	FloorSearchPoint* wsObj_;
};

#endif
