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
	// �ҋ@��Ԃł�
	void idel();
	// �U���s���ł�
	void Attack();
	// ���G���̍s���ł�
	void searchMove();
	// �ǐՎ��̍s���ł�
	void chaseMove();

private:
	FloorSearchPoint* fspObj_;
};

#endif