#pragma once

#include "../PlayerState_Union.h"

#include "../../../../PlayerPtr.h"

#include "../../../../PlayerBodyCollider.h"

class PlayerState_Attack : public PlayerState_Union {
public:
	PlayerState_Attack(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
	virtual void key_input(float deltaTime) override;
	virtual void pad_input(float deltaTime) override;
private:
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

//#pragma once
//
//#include "../PlayerState_Union.h"
//
//class PlayerState_Attack : public PlayerState_Union {
//public:
//	PlayerState_Attack();
//
//	virtual void unique_init() override;
//
//	virtual void update(float deltaTime) override;
//
//	virtual void end() override;
//private:
//	void key_update();
//	void pad_update();
//private:
//	Vector2 dir_;
//	float dump_;
//	float power_;
//
//	float dir_easeing_;
//	float gra_easeing_;
//
//};
