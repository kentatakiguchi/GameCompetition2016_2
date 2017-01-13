#ifndef WALL_MOVE_ENEMY_H_
#define WALL_MOVE_ENEMY_H_

#include "../BaseEnemy.h"

// �ǈړ��G�l�~�[�N���X
class WallMoveEnemy : public BaseEnemy {
public:
	WallMoveEnemy(
		IWorld * world,
		const Vector2& position,
		const Vector2& direction = Vector2(-1.0f, -1.0f));
	void onUpdate(float deltaTime) override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;
private:
	// ���G�ړ��ł�
	void search() override;
	// ���G���̍s���ł�
	void searchMove() override;
	// �Ǒ{���I�u�W�F�N�g�̈ʒu��ǉ�
	void addWSPPosition();
	// �Ǒ{���I�u�W�F�N�g�̑傫����ǉ�
	void addWSPScale();
	// �A�j���[�V�����̒ǉ����s���܂�
	void addAnimation() override;

private:
	Vector2 addScale_;	// �ǉ��̑傫��
};

#endif
