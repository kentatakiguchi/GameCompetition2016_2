#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "PlayerPtr.h"

#include "Player.h"

// ÉvÉåÅ[ÉÑÅ[
class PlayerBody_Point : public Actor {
public:
	enum class Opponent {
		NONE,
		FLOOR,
		ITEM,
		TEST
	};
public:
	PlayerBody_Point(IWorld* world, const std::string& name, const int& point_num);
	~PlayerBody_Point();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onCollide(Actor& other) override;
	void move(KeyCode up = KeyCode::UP, KeyCode down = KeyCode::DOWN, KeyCode right = KeyCode::RIGHT, KeyCode left = KeyCode::LEFT);
private:
	Vector2 input_;
	Vector2 velocity_;
	Vector2 gravity_;
	Vector2 launch_;
	Vector2 last_pos_;
	Opponent opponent_;
	Vector2 oppenent_pos_;

	PlayerBodyPtr main_target_;
	PlayerBodyPtr sub_target_;
	int num_;
};
