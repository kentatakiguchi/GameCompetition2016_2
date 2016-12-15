#ifndef THREE_JUMP_ATTACK_H_
#define THREE_JUMP_ATTACK_H_

#include "JumpAttack.h"

// �R�A���W�����v�U���N���X
class ThreeJumpAttack : public JumpAttack {
public:
	ThreeJumpAttack();
	ThreeJumpAttack(IWorld* world, const Vector2& position);
	// �U��
	void attack(float deltaTime) override;
	// �U���s���̃��t���b�V�����s���܂�
	void Refresh() override;

private:
	int jumpCount_;			// �W�����v��
	int initJumpCount_;		// �����̃W�����v��
};

#endif
