#ifndef DYSON_ATTACK_H_
#define DYSON_ATTACK_H_

#include "BossAttack.h"

// �z�����ݍU��
class DysonAttack : public BossAttack {
public:
	DysonAttack();
	DysonAttack(const Vector2& position);
	// �U��
	void attack(float deltaTime) override;
	// �U���s���̃��t���b�V�����s���܂�
	void Refresh() override;
};

#endif
