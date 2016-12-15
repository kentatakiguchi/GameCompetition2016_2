#ifndef DYSON_ATTACK_H_
#define DYSON_ATTACK_H_

#include "BossAttack.h"

class IWorld;
class Tornado;

// �z�����ݍU��
class DysonAttack : public BossAttack {
private:
	enum class State {
		Attack,
		Flinch,
		Fatigue
	};

public:
	DysonAttack();
	DysonAttack(IWorld* world, const Vector2& position);
	// �U��
	void attack(float deltaTime) override;
	// �U���s���̃��t���b�V�����s���܂�
	void Refresh() override;

private:
	// �U�����
	void dysonAttack(float deltaTime);
	// ���ݏ��
	void flinch(float deltaTime);
	// ��J���
	void fatigue(float deltaTime);
	// ��Ԃ̕ύX���s���܂�
	void changeState(State state, BossAnimationNumber num);

private:
	float addAngle_;		// �p�x�̉��Z��
	bool isRockCreate_;		// ��𐶐������� 

	IWorld* world_;			// ���[���h

	Tornado* tornadoObj_;	// �����I�u�W�F�N�g

	State state_;
};

#endif
