#ifndef ADHERE_MINI_BOSS_H_
#define ADHERE_MINI_BOSS_H_

//#include "../../../../Base/Actor.h"
#include "FighterMiniBossh.h"
#include "../../../../../Animation/Enemy/EnemyAnimation2D.h"

class AdhereMiniBoss : public FighterMiniBoss {
protected:
	// ���S���
	enum class DeadState {
		HitDead,
		AdhereDead
	};

public:
	AdhereMiniBoss(
		IWorld* world, 
		const Vector2&  position, 
		const float bodyScale = 64.0f);

protected:
	// ��Ԃ̕ύX
	void changeDeadState(DeadState dState, int animation);
	// �ҋ@���
	void idel(float deltaTime) override;
	// �ړ����
	virtual void move(float deltaTime) override;
	// ���������
	virtual void attack(float deltaTime) override;
	// ���S���
	virtual void deadMove(float deltaTime) override;
	// ���������S���
	void adhereDead(float deltaTime);
	// ���ɓ����������̏���
	virtual void floorHit() override;
	// �v���C���[�Ɠ����������̏���
	void playerHit(Actor& actor) override;

protected:
	//// �A�j���[�V�����̒ǉ�
	virtual void addAnimation() override;
	// �����_���̊p�x���擾���܂�
	float getRandomDegree();

protected:
	float adhereDeadTime_;	// ���������̎��S����
	DeadState dState_;		// ���S���
};

#endif

