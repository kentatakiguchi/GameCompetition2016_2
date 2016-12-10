#ifndef WALL_TRUN_ENEMY_H
#define WALL_TRUN_ENEMY_H

#include "../BaseEnemy.h"

class FloorSearchPoint;

// �S���h�G�l�~�[�N���X
class WallTrunEnemy : public BaseEnemy {
public:
	WallTrunEnemy(
		IWorld * world, 
		const Vector2& position,
		const Vector2& direction = Vector2(0.0f, -1.0f));
	void update(float deltaTime) override;
	void onMessage(EventMessage event, void*) override;

private:
	// ���G�ړ��ł�
	void search() override;
	// �U���s���ł�
	void attack() override;
	// ���G���̍s���ł�
	void searchMove() override;
	// �ǐՎ��̍s���ł�
	void chaseMove() override;
	// �A�j���[�V�����̒ǉ����s���܂�
	void addAnimation() override;

private:
	FloorSearchPoint* wsObj_;
};

#endif
