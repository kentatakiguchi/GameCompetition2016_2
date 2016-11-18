#ifndef NEEDLE_ENEMY_H_
#define NEEDLE_ENEMY_H_

#include "../BaseEnemy.h"

// �j�N���X(�������Ȃ��B��Q��)
class NeedleEnemy : public BaseEnemy {
public:
	NeedleEnemy(
		IWorld * world,
		const Vector2& position,
		const Vector2& direction);
	void update(float deltaTime) override;
	void onDraw() const;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	// �ҋ@��Ԃł�
	void idel();
};

#endif