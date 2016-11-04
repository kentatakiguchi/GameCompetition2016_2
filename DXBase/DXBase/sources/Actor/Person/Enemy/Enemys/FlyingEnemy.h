#ifndef FLYING_ENEMY_H_
#define FLYING_ENEMY_H_

#include "../BaseEnemy.h"

class FloorSearchPoint;

class FlyingEnemy : public BaseEnemy {
public:
	FlyingEnemy(IWorld * world, const Vector2& position);
	void onUpdate(float deltaTime) override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	// �v���C���[�𔭌��������̍s���ł�
	void discovery();
	// �U���s���ł�
	void attack();
	// ���G���̍s���ł�
	void searchMove();
	// �ǐՎ��̍s���ł�
	void chaseMove();
	// 
	void lostMove();

private:
	float direTimer_;			// �����]�����鎞��
	float lostTimer_;			// ������������
	Vector2 pastPosition;
	FloorSearchPoint* wsObj_;	// �Ǒ{���I�u�W�F�N�g
};

#endif
