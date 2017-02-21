#pragma once

#include "../../../PlayerState_Union.h"

#include "../../../../../../PlayerPtr.h"

#include "../../../../../../PlayerBodyCollider.h"

class PlayerState_AttackBase : public PlayerState_Union {
public:
	PlayerState_AttackBase(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void collide(const Actor & other) override {}
	virtual void end() override;
	virtual void key_input(float deltaTime) override;
	virtual void pad_input(float deltaTime) override;
private:
	virtual void onInit() {}
	virtual void onUpdate(float deltaTime) {}
	virtual void onCollide(const Actor & other) {}
	virtual void onEnd() {}
	virtual void onKeyInput(float deltaTime) {}
	virtual void onPadInput(float deltaTime) {}
protected:
	Vector2 dir_;
	Vector2 launch_dir_;
	float launch_power_;
	float launch_dir_easeing_;
	Vector2 chase_dir_;
	float chase_power_;
	float chase_dir_easeing_;

	Vector2 gravity_;
	float gra_easeing_;

	PlayerBodyCollPtr attackColl_;
};

