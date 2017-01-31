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
	float scale_;					// 画像の大きさ
	Vector2 direction_;				// 方向
	EnemyAnimation2D animation_;	// アニメーション
	FloorSearchPoint* fspObj_;		// 床捜索オブジェクト
};

#endif