#ifndef DEADENEMY_H_
#define DEADENEMY_H_

#include "../../Base/Actor.h"
#include "../../../Animation/Enemy/EnemyAnimation2D.h"

// 死亡エネミー(衝突判定のみ)
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
	// 地面の位置に補正します
	void groundClamp(Actor& actor);

private:
	float timer_;

	bool isGround_;

	EnemyAnimation2D animation_;	// アニメーション
};

#endif
