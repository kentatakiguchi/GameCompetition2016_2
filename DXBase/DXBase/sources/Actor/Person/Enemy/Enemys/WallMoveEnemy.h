#ifndef WALL_MOVE_ENEMY_H_
#define WALL_MOVE_ENEMY_H_

#include "../BaseEnemy.h"
#include <vector> // �f�o�b�O

class WallMoveEnemy : public BaseEnemy {
public:
	WallMoveEnemy(IWorld * world, const Vector2& position);
	void onUpdate(float deltaTime) override;
	void onDraw() const;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;
private:
	// ���G�ړ��ł�
	void search();
	// ���G���̍s���ł�
	void searchMove();
	// �Ǒ{���I�u�W�F�N�g�̈ʒu��ǉ�
	void addWSPPosition();
	// �Ǒ{���I�u�W�F�N�g�̑傫����ǉ�
	void addWSPScale();

private:
	Vector2 addScale_;

	typedef std::vector<bool> IsGroundContainer;
	IsGroundContainer isGCont;
};

#endif
