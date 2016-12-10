#ifndef FLOOR_TURN_ENEMY_H_
#define FLOOR_TURN_ENEMY_H_

#include "../BaseEnemy.h"

class FloorSearchPoint;

// �N���{�[�G�l�~�[�N���X
class FloorTurnEnemy : public BaseEnemy {
public:
	FloorTurnEnemy(
		IWorld * world, 
		const Vector2& position,
		float right = 1.0f);
	void beginUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	void onMessage(EventMessage event, void*) override;
	// �������Ă���I�u�W�F�N�g�̈ʒu��ݒ肵�܂�
	void setObjPosition() override;

private:
	// �U���s���ł�
	void attack() override;
	// ���G���̍s���ł�
	void searchMove() override;
	// �ǐՎ��̍s���ł�
	void chaseMove() override;

private:
	FloorSearchPoint* fspObj_;
};

#endif