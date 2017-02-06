#ifndef ADHERE_MINI_BOSS_H_
#define ADHERE_MINI_BOSS_H_

#include "../../../../Base/Actor.h"
#include "../../../../../Animation/Enemy/EnemyAnimation2D.h"

class AdhereMiniBoss : public Actor {
protected:
	enum class State {
		Idel,
		Move,
		Adhere,
		Dead,
		AdhereDead
	};
	// �A�j���[�V�����ԍ�
	enum {
		WAIT_NUMBER = 0,
		RUN_NUMBER = 1,
		ADHERE_NUMBER = 2,
		DEAD_NUMBER = 3
	};

public:
	AdhereMiniBoss(IWorld* world, const Vector2&  position, const float bodyScale = 64.0f);
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
	void idel(float deltaTime);
	// �ړ����
	virtual void move(float deltaTime);
	// ���������
	void adhere(float deltaTime);
	// ���S���
	virtual void deadMove(float deltaTime);
	// ���������S���
	void adhereDead(float deltaTime);
	// ���ɓ����������̏���
	virtual void floorHit();

protected:
	// �v���C���[�Ƃ̕�����Ԃ��܂�
	Vector2 getPlayerDirection();
	// �e�N�X�`���̈ʒu��ݒ肵�܂�
	void setTexPosition(float up);
	// �A�j���[�V�����̒ǉ�
	void addAnimation();
	// �����_���̊p�x���擾���܂�
	float getRandomDegree();
	// �n�ʂ̈ʒu�ɕ␳���܂�
	void groundClamp(Actor& actor);

protected:
	int animeNum_;					// �A�j���[�V�����ԍ�
	float speed_;					// ���x
	float timer_;					// ����
	float size_;					// �傫��
	float degree_;					// �p�x
	bool isClamp_;					// �n�ʂ̈ʒu�ɕ�Ԃ��邩
	bool isTop_, isBottom_;			// ���̏㉺�ɓ���������
	bool isLeft_, isRight_;			// ���̍��E�ɓ���������
	std::string playerName_;		// �v���C���[�̖��O
	Vector2 texPos_;				// �e�N�X�`���̈ʒu
	Vector2 orizin_;				// ���_
	State state_;					// ���
	EnemyAnimation2D animation_;	// �A�j���[�V����
};

#endif

