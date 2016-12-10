#ifndef DEADENEMY_H_
#define DEADENEMY_H_

#include "../../Base/Actor.h"
#include "../../../Animation/Enemy/EnemyAnimation2D.h"

// ���S�G�l�~�[(�Փ˔���̂�)
class DeadEnemy :public Actor {
public:
	DeadEnemy(
		IWorld* world,
		const Vector2& position,
		const float bodyScale);
	void onUpdate(float deltaTime) override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;



private:
	// �n�ʂ̈ʒu�ɕ␳���܂�
	void groundClamp(Actor& actor);

private:
	float timer_;

	bool isGround_;

	EnemyAnimation2D animation_;	// �A�j���[�V����
};

#endif
