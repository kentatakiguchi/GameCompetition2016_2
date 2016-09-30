#pragma once

#include "../../Base/Actor.h"

class Player_AttackRange : public Actor {
public:
	// コンストラクタ
	Player_AttackRange(IWorld* world, const Vector3& position);
private:
	// 更新
	virtual void onUpdate(float deltaTime) override;
private:
	const float LIFE_TIME = 1.0f;
	float lifeTimer_;
};