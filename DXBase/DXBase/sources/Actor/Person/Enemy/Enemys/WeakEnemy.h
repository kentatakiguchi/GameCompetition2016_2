#ifndef WEAK_ENEMY_H_
#define WEAK_ENEMY_H_

#include "../BaseEnemy.h"

class WeakEnemy : public BaseEnemy {
public:
	WeakEnemy(IWorld * world, const Vector2& position);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

private:
	// �ҋ@��Ԃł�
	void idel();
	//// �v���C���[�Ƃ̋������Z���Ƃ��̍s���ł�
	//void shortDistanceAttack();
	//// �v���C���[�Ƃ̋��������Ԃ̍s���ł�
	//void centerDistanceAttack();
	//// �v���C���[�Ƃ̋����������Ƃ��̍s���ł�
	//void longDistanceAttack();
	// �U���s���ł�
	void Attack();
	//// ��e�s���ł�
	//void damageMove();
	//// ���S�s���ł�
	//void deadMove();
	// ���G���̍s���ł�
	void searchMove();
	// �ǐՎ��̍s���ł�
	void chaseMove();
};

#endif
