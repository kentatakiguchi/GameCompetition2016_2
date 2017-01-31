#ifndef MINI_BOSS_H_
#define MINI_BOSS_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Enemy/EnemyAnimation2D.h"

class FloorSearchPoint;

class MiniBoss : public Actor {
public:
	MiniBoss(IWorld* world, const Vector2& position, const float scale = 1.0f);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

private:
	void groundClamp(Actor& actor);

private:
	float scale_;					// �摜�̑傫��
	Vector2 direction_;				// ����
	EnemyAnimation2D animation_;	// �A�j���[�V����
	FloorSearchPoint* fspObj_;		// ���{���I�u�W�F�N�g
};

#endif