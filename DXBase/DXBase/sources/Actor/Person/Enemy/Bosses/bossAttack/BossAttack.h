#ifndef BOSS_ATTACK_H_
#define BOSS_ATTACK_H_

#include "../../../../../Math/Math.h"
#include "../../../../../Define.h"

// �{�X�U���N���X(�x�[�X)
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
	Vector2 getMovePosition();
	// �U���s���̃��t���b�V�����s���܂�
	virtual void Refresh();
	// �U�����I����������Ԃ��܂�
	bool isAttackEnd();

public:
	// �ʒu��ݒ肵�܂�
	void setPosition(const Vector2& position);
	// �v���C���[�Ƃ̕�����ݒ肵�܂�
	void setDirection(const Vector2& direction);
	// ���ɐG��Ă��邩��ݒ肵�܂�
	void setIsGround(bool isGround);

protected:
	float timer_;		// ����
	bool isAttackEnd_;	// �U�����I�������
	bool isGround_;		// �{�X�����ɐG��Ă���̂�
	Vector2 position_;	// �ʒu
	Vector2 direction_;	// �v���C���[�Ƃ̕���
};

#endif
