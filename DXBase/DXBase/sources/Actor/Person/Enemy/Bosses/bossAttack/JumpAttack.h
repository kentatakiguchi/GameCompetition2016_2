#ifndef JUMP_ATTACK_H_
#define JUMP_ATTACK_H_

#include "BossAttack.h"

// �W�����v�U���N���X
class JumpAttack : public BossAttack {
public:
	JumpAttack();
	JumpAttack(IWorld* world, const Vector2& position);
	// �U��
	virtual void attack(float deltaTime) override;
	// �W�����v�U��
	void jump(float deltaTime);
	// �U���s���̃��t���b�V�����s���܂�
	virtual void Refresh() override;

//protected:
//	// �W�����v���Ԃ�ݒ肵�܂�
//	void setJumpSpeed();
protected:
	// ��̐���
	void createRock();

protected:
	float degrees_;			// �p�x
	float jumpPower_;		// �W�����v��
	float initJumpPower_;	// �W�����v��(������)
	float recastTimer_;		// �čs������܂ł̎���
	float initRecastTimer_;	// �čs������܂ł̎���(�����l)
	bool isJump_;			// �W�����v��������
	bool isFirstJump_;		// �ŏ��̃W�����v��
	bool isJumpEnd_;		// �W�����v�U�����I��������
	bool isIdel_;			// �W�����v��̑ҋ@��Ԃ�
	bool isRockCreate_;		// ��𐶐�������
	Vector2 speed_;			// ���x

private:
	std::string otherName_;			// �Փ˂������葤�̖��O
	std::string prevOtherName_;		// �ߋ��̏Փ˂������葤�̖��O
	Vector2 prevPlayerDistance_;	// �ߋ��̃v���C���[�Ƃ̕���
};

#endif
