#ifndef ROCK_H_
#define ROCK_H_

#include "Bosses/MiniBoss/AdhereMiniBoss.h"

class Rock : public AdhereMiniBoss {
public:
	Rock(IWorld* world, const Vector2&  position, const float bodyScale = 64.0f);

private:
	// �������
	void move(float deltaTime) override;
	// ���S���
	void deadMove(float deltaTime) override;
	// ���ɓ����������̏���
	void floorHit() override;
};

#endif
