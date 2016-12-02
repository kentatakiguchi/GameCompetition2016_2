#ifndef DYSON_ATTACK_H_
#define DYSON_ATTACK_H_

#include "BossAttack.h"

class IWorld;
class Tornado;

// �z�����ݍU��
class DysonAttack : public BossAttack {
public:
	DysonAttack();
	DysonAttack(IWorld* world, const Vector2& position);
	// �U��
	void attack(float deltaTime) override;
	// �U���s���̃��t���b�V�����s���܂�
	void Refresh() override;

private:
	IWorld* world_;			// ���[���h

	Tornado* tornadoObj_;	// �����I�u�W�F�N�g
};

#endif
