#ifndef JUMP_ATTACK_H_
#define JUMP_ATTACK_H_

#include "BossAttack.h"

// �W�����v�U���N���X
class JumpAttack : public BossAttack {
public:
	JumpAttack();
	JumpAttack(const Vector2& position);	
	// �U��
	virtual void attack(float deltaTime) override;
	// �W�����v�U��
	void jump(float deltaTime);
	//// �ړ������ʒu���擾���܂�
	//Vector2 getMovePosition() override;
	// �U���s���̃��t���b�V�����s���܂�
	virtual void Refresh() override;

protected:
	float speed_;			// ���x
	float degrees_;			// �p�x
	float jumpPower_;		// �W�����v��
	float recastTimer_;		// �čs������܂ł̎���
	float initRecastTimer_;	// �čs������܂ł̎���(�����l)
	bool isJump_;			// �W�����v��������
	bool isJumpEnd_;		// �W�����v�U�����I��������
};

#endif