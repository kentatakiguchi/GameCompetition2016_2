#ifndef BOSS_ATTACK_H_
#define BOSS_ATTACK_H_

#include "../../../../../Math/Math.h"
#include "../../../../../Define.h"

class BossAttack {
public:
	BossAttack();
	BossAttack(const Vector2& position);
	// �f�X�g���N�^
	virtual ~BossAttack();
	// �X�V
	void update(float deltaTime);
	// �U��
	virtual void attack(float deltaTime);
	// �ړ������ʒu���擾���܂�
	virtual Vector2 getMovePosition();
	// �U���s���̃��t���b�V�����s���܂�
	virtual void Refresh();
	// �U�����I����������Ԃ��܂�
	bool isAttackEnd();

	//// �W�����v�U��
	//void jumpAttack(float deltaTime);
	//// �ǍU��
	//void wallAttack(float deltaTime);

protected:
	float timer_;		// ����
	bool isAttackEnd_;	// �U�����I�������
	Vector2 position_;	// �ʒu
};

#endif
