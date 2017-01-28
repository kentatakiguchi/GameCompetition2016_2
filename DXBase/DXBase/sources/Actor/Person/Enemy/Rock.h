#ifndef ROCK_H_
#define ROCK_H_

#include "../../Base/Actor.h"
#include "../../../Animation/Enemy/EnemyAnimation2D.h"

class Rock : public Actor {
private:
	enum class State {
		Idel,
		Fall,
		Adhere,
		Dead
	};
	// �A�j���[�V�����ԍ�
	enum {
		WAIT_NUMBER = 0,
		RUN_NUMBER = 1,
		ADHERE_NUMBER = 2,
		DEAD_NUMBER = 3
	};

public:
	Rock(IWorld* world, const Vector2&  position, const float bodyScale = 64.0f);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	// ��Ԃ̕ύX
	void changeState(State state, int animation);
	// �ҋ@���
	void idel(float deltaTime);
	// �������
	void fall(float deltaTime);
	// ���������
	void adhere(float deltaTime);
	// ���S���
	void deadMove(float deltaTime);

private:
	// �v���C���[�Ƃ̕�����Ԃ��܂�
	Vector2 getPlayerDirection();
	// �e�N�X�`���̈ʒu��ݒ肵�܂�
	void setTexPosition(float up);
	// �A�j���[�V�����̒ǉ�
	void addAnimation();
	// �����_���̊p�x���擾���܂�
	float getRandomDegree();

private:
	float speed_;					// ���x
	float timer_;					// ����
	float size_;					// �傫��
	float degree_;					// �p�x
	std::string playerName_;		// �v���C���[�̖��O
	Vector2 texPos_;				// �e�N�X�`���̈ʒu
	Vector2 orizin_;				// ���_
	State state_;					// ���
	EnemyAnimation2D animation_;	// �A�j���[�V����
};

#endif
