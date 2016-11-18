#ifndef WEAK_ENEMY_H_
#define WEAK_ENEMY_H_

#include "../BaseEnemy.h"

// �f�o�b�O�p�G�l�~�[
class WeakEnemy : public BaseEnemy {
public:
	WeakEnemy(IWorld * world, const Vector2& position);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	//// �v���C���[�Ƃ̋������Z���Ƃ��̍s���ł�
	//void shortDistanceAttack();
	//// �v���C���[�Ƃ̋��������Ԃ̍s���ł�
	//void centerDistanceAttack();
	//// �v���C���[�Ƃ̋����������Ƃ��̍s���ł�
	//void longDistanceAttack();
	// �U���s���ł�
	void attack() override;
	//// ��e�s���ł�
	//void damageMove();
	//// ���S�s���ł�
	//void deadMove();
	// ���G���̍s���ł�
	void searchMove() override;
	// �ǐՎ��̍s���ł�
	void chaseMove() override;
};

#endif
