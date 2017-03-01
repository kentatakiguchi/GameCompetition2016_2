#ifndef FLYING_MINI_BOSS_H_
#define FLYING_MINI_BOSS_H_

#include "AdhereMiniBoss.h"

class FlyingMiniBoss : public AdhereMiniBoss{
public:
	FlyingMiniBoss(
		IWorld* world, 
		const Vector2&  position, 
		const Vector2& direction = Vector2::One,
		const float bodyScale = 64.0f);

private:
	// �ړ����
	void move(float deltaTime) override;
	// ���ɓ����������̏���
	void floorHit() override;
	// �v���C���[�̍U���ɓ����������̏���
	void playerAttackHit(Actor& actor) override;

private:
	float deg_;				// �p�x(�e�̕ϐ������ύX����)
	Vector2 direction_;		// ����
};

#endif
