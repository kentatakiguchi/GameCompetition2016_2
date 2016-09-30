#pragma once

#include "../../Base/Actor.h"

class Enemy_AttackRange : public Actor {
public:
	// コンストラクタ
	Enemy_AttackRange(IWorld* world, const Vector3& position);
private:
	// 更新
	virtual void onUpdate(float deltaTime) override;
private:
	const float LIFE_TIME = 0.2f;
	float lifeTimer_;
};
