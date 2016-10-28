#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "State/Base/StateMgr.h"

// ÉvÉåÅ[ÉÑÅ[
class PlayerBody : public Actor {
public:
	enum class Opponent {
		NONE,
		FLOOR,
		ITEM,
		TEST
	};
public:
	PlayerBody(IWorld* world, const std::string name, const Vector2& position);
	~PlayerBody();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onCollide(Actor& other) override;
	void changeMotion(float deltaTime);
	void move(KeyCode up = KeyCode::UP, KeyCode down = KeyCode::DOWN, KeyCode right = KeyCode::RIGHT, KeyCode left = KeyCode::LEFT);
	void move_ver(KeyCode up = KeyCode::UP, KeyCode down = KeyCode::DOWN, KeyCode right = KeyCode::RIGHT, KeyCode left = KeyCode::LEFT);
	void move_hor(KeyCode up = KeyCode::UP, KeyCode down = KeyCode::DOWN, KeyCode right = KeyCode::RIGHT, KeyCode left = KeyCode::LEFT);
	void chase();
	void gravity();
	void acc_gravity();
	void hold_gravity();
	void circleClamp();
	void launch(Vector2 dir);
	Opponent hitOpponent();
	void reset_opponent();
	void reset_velocity();
	void pre_vector();
	float distance();
	void target(std::shared_ptr<PlayerBody> target);
	void set_name(std::string name);

	Vector2 GetVelo() {
		return Vector2(velocity_.x, velocity_.y);
	}
private:
	Vector2 input_;
	Vector2 velocity_;
	Vector2 gravity_;
	Vector2 launch_;
	Vector2 last_pos_;
	std::shared_ptr<PlayerBody> target_;
	Opponent opponent_;
	Vector2 x;
	std::string name_1_;
};

