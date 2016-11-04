#ifndef FLOOR_TURN_ENEMY_H_
#define FLOOR_TURN_ENEMY_H_

#include "../BaseEnemy.h"

class FloorSearchPoint;

class FloorTurnEnemy : public BaseEnemy {
public:
	FloorTurnEnemy(IWorld * world, const Vector2& position);
	void onUpdate(float deltaTime) override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	// �ҋ@��Ԃł�
	void idel();
	// �U���s���ł�
	void attack();
	// ���G���̍s���ł�
	void searchMove();
	// �ǐՎ��̍s���ł�
	void chaseMove();

private:
	FloorSearchPoint* fspObj_;
};

#endif