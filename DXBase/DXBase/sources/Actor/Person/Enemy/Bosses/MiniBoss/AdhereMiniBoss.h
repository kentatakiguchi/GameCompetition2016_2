#ifndef ADHERE_MINI_BOSS_H_
#define ADHERE_MINI_BOSS_H_

//#include "../../../../Base/Actor.h"
#include "FighterMiniBossh.h"
#include "../../../../../Animation/Enemy/EnemyAnimation2D.h"

class AdhereMiniBoss : public FighterMiniBoss {
protected:
	/*enum class State {
		Idel,
		Move,
		Adhere,
		Dead
	};*/
	// ���S���
	enum class DeadState {
		HitDead,
		AdhereDead
	};
	//// �A�j���[�V�����ԍ�
	//enum {
	//	WAIT_NUMBER = 0,
	//	RUN_NUMBER = 1,
	//	ADHERE_NUMBER = 2,
	//	DEAD_NUMBER = 3
	//};

public:
	AdhereMiniBoss(
		IWorld* world, 
		const Vector2&  position, 
		const float bodyScale = 64.0f);
	/*void onUpdate(float deltaTime) override;
	void onDraw() const override;*/
	/*void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;*/

protected:
	// ��Ԃ̕ύX
	void changeDeadState(DeadState dState, int animation);
	//// ��Ԃ̍X�V
	//void updateState(float deltaTime);
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
	//// �v���C���[�Ƃ̕�����Ԃ��܂�(�P�ʃx�N�g��)
	//Vector2 getPlayerDirection();
	//// �e�N�X�`���̈ʒu��ݒ肵�܂�
	//void setTexPosition(float up);
	//// �A�j���[�V�����̒ǉ�
	virtual void addAnimation() override;
	// �����_���̊p�x���擾���܂�
	float getRandomDegree();
	//// �n�ʂ̈ʒu�ɕ␳���܂�
	//void groundClamp(Actor& actor);

protected:
	float adhereDeadTime_;	// ���������̎��S����
	DeadState dState_;		// ���S���
};

#endif

