#ifndef FIGHTER_MINI_BOSS_H_
#define FIGHTER_MINI_BOSS_H_

#include "../../../../Base/Actor.h"
#include "../../../../../Animation/Enemy/EnemyAnimation2D.h"

class FighterMiniBoss : public Actor {
protected:
	enum class State {
		Idel,
		Move,
		Attack,
		Dead
	};

public:
	FighterMiniBoss(
		IWorld* world,
		const Vector2&  position,
		const float bodyScale = 64.0f);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

protected:
	// ��Ԃ̕ύX
	void changeState(State state, int animation);
	// ��Ԃ̍X�V
	void updateState(float deltaTime);
	// �ҋ@���
	virtual void idel(float deltaTime);
	// �ړ����
	virtual void move(float deltaTime);
	// �U�����
	virtual void attack(float deltaTime);
	// ���S���
	virtual void deadMove(float deltaTime);
	// ���ɓ����������̏���
	virtual void floorHit();
	// �v���C���[�ɓ����������̏���	
	virtual void playerHit(Actor& actor);

protected:
	// �v���C���[�Ƃ̕�����Ԃ��܂�(�P�ʃx�N�g��)
	Vector2 getPlayerDirection();
	// �e�N�X�`���̈ʒu��ݒ肵�܂�
	void setTexPosition(float up);
	// �A�j���[�V�����̒ǉ�
	virtual void addAnimation();
	// �n�ʂ̈ʒu�ɕ␳���܂�
	void groundClamp(Actor& actor);

protected:
	int animeNum_;					// �A�j���[�V�����ԍ�
	float speed_;					// ���x
	float stateTimer_;				// ����
	float size_;					// �傫��
	float degree_;					// �p�x
	//float adhereDeadTime_;			// ���������̎��S����
	bool isClamp_;					// �n�ʂ̈ʒu�ɕ�Ԃ��邩
	bool isTop_, isBottom_;			// ���̏㉺�ɓ���������
	bool isLeft_, isRight_;			// ���̍��E�ɓ���������
	bool isInvincible_;				// ���G��
	std::string playerName_;		// �v���C���[�̖��O
	Vector2 texPos_;				// �e�N�X�`���̈ʒu
	Vector2 orizin_;				// ���_
	Vector2 prevPlayerDirection_;	// �v���C���[�Ƃ̉ߋ��̕���
	State state_;					// ���
	EnemyAnimation2D animation_;	// �A�j���[�V����
};

#endif