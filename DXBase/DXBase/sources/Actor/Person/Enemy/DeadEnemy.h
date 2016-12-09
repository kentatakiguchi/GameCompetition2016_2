#ifndef DEADENEMY_H_
#define DEADENEMY_H_

#include "../../Base/Actor.h"
#include "../../../Animation/Enemy/EnemyAnimation2D.h"

class DeadEnemy :public Actor {
public:
	DeadEnemy(
		IWorld* world,
		const Vector2& position,
		const Vector2& bodyScale,
		const int id,
		const int res,
		const Vector2& direction = Vector2(1.0f, 1.0f));
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

	// 地面の位置に補正します
	void groundClamp(Actor& actor);

private:
	float timer_;

	bool isGround_;

	EnemyAnimation2D animation_;	// アニメーション
};

#endif
