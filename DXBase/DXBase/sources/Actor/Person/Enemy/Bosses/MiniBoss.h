#ifndef MINI_BOSS_H_
#define MINI_BOSS_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Enemy/EnemyAnimation2D.h"

class FloorSearchPoint;

class MiniBoss : public Actor {
private:
	// �A�j���V���[���N���X
	enum {
		MINI_BOSS_RUN = 0,
		MINI_BOSS_LIFT = 1,
	};
	// ��ԃN���X
	enum class State {
		Confusion,
		CalmDown,
		Approach,
		Lift,
		RunAway
	};

public:
	MiniBoss(IWorld* world, const Vector2& position, const float scale = 1.0f);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

private:
	// ��Ԃ̍X�V
	void updateState(float deltaTime);
	// ��Ԃ̕ύX���s���܂�
	void changeState(State state, int num);
	// �������
	void Confusion(float deltaTime);
	// �����������
	void CalmDown(float deltaTime);
	// �{�X�ɋ߂Â����
	void Approach(float deltaTime);
	// �{�X�������グ����
	void Lift(float deltaTime);
	// ���S���
	void RunAway(float deltaTime);
	// �n�ʂ̈ʒu�ɕ␳���܂�
	void groundClamp(Actor& actor);

public:
	//�@�~�j�{�X�𐳋C�ɖ߂��܂�
	void backToSanity();
	// �{�X�������グ���Ԃɂ��܂�
	void bossLift();
	// �{�X�̈ʒu�ɂ��邩��Ԃ��܂�
	bool isBossPosition();
	// �����グ����
	bool isLift();
	// 
	void setLiftMove(const float speed);

private:
	float stateTimer_;
	float speed_;					// �ړ����x
	float scale_;					// �摜�̑傫��
	float bossPositionRX_;
	bool isConfusion_;				// �������Ă��邩
	bool isBossPosition_;			// �{�X�̈ʒu�ɂ��邩
	bool isLift_;
	Vector2 direction_;				// ����
	State state_;					// ���
	EnemyAnimation2D animation_;	// �A�j���[�V����
	FloorSearchPoint* fspObj_;		// ���{���I�u�W�F�N�g
};

#endif