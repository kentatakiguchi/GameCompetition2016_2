#ifndef FLYING_ENEMY_H_
#define FLYING_ENEMY_H_

#include "../BaseEnemy.h"

class FloorSearchPoint;

// �n�l�N���{�[�G�l�~�[�N���X
class FlyingEnemy : public BaseEnemy {
public:
	FlyingEnemy(
		IWorld * world,
		const Vector2& position,
		float Down = 1.0f);
	void beginUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	void onMessage(EventMessage event, void*) override;

private:
	// ���G�ړ��ł�
	void search() override;
	// �v���C���[�𔭌��������̍s���ł�
	void discovery() override;
	// �U���s���ł�
	void attack() override;
	// ���G���̍s���ł�
	void searchMove() override;
	// �v���C���[�̒ǐՍs���ł�
	void chase() override;
	// �ǐՎ��̍s���ł�
	void chaseMove() override;
	// �G�������������̍s���ł�
	void lostMove() override;
	// �A�j���[�V�����̒ǉ����s���܂�
	void addAnimation() override;

private:
	float direTimer_;			// �����]�����鎞��
	float lostTimer_;			// ������������
	Vector2 pastPosition_;
	FloorSearchPoint* wsObj_;	// �Ǒ{���I�u�W�F�N�g
};

#endif
