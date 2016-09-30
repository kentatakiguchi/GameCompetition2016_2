#pragma once

#include "../../Base/Actor.h"

class Player_AttackRange : public Actor {
public:
	// �R���X�g���N�^
	Player_AttackRange(IWorld* world, const Vector3& position);
private:
	// �X�V
	virtual void onUpdate(float deltaTime) override;
private:
	const float LIFE_TIME = 1.0f;
	float lifeTimer_;
};