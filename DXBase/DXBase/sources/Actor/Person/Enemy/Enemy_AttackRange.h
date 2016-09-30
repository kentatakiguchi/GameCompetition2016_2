#pragma once

#include "../../Base/Actor.h"

class Enemy_AttackRange : public Actor {
public:
	// �R���X�g���N�^
	Enemy_AttackRange(IWorld* world, const Vector3& position);
private:
	// �X�V
	virtual void onUpdate(float deltaTime) override;
private:
	const float LIFE_TIME = 0.2f;
	float lifeTimer_;
};
