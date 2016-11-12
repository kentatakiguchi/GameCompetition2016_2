#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "State/Base/StateMgr.h"
#include "PlayerPtr.h"

// プレーヤー
class PlayerBody : public Actor {
public:
	enum class Opponent {
		NONE,
		//FLOOR,
		ITEM,
		PARTNER,
		ENEMY,
		TEST
	};
public:
	struct SingleKeys {
	public:
		KeyCode up;
		KeyCode down;
		KeyCode right;
		KeyCode left;
	public:
		SingleKeys(KeyCode up_key = KeyCode::UP, KeyCode down_key = KeyCode::DOWN, KeyCode right_key = KeyCode::RIGHT, KeyCode left_key = KeyCode::LEFT) {
			up = up_key;
			down = down_key;
			right = right_key;
			left = left_key;
		}
	};
public:
	PlayerBody();
	PlayerBody(IWorld* world, const std::string name, const Vector2& position);
	~PlayerBody();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onCollide(Actor& other) override;
	void init_state();
	void move(Vector2 vector);	
	
	void sprit_move(KeyCode up = KeyCode::UP, KeyCode down = KeyCode::DOWN, KeyCode right = KeyCode::RIGHT, KeyCode left = KeyCode::LEFT);
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
	bool isOnFloor();
	bool isDead();
	void single_action(float deltaTime);
	SingleKeys get_keys();

	Vector2 GetVelo() {
		return Vector2(velocity_.x, velocity_.y);
	}
private:
	Vector2 input_;
	Vector2 velocity_;
	Vector2 gravity_;
	Vector2 launch_;
	Vector2 last_pos_;
	PlayerBodyPtr target_;
	Opponent opponent_;
	bool isOnFloor_;
	Vector2 oppenent_pos_;

	float jump_power_;
	const char* other_;
	// 単独状態か否か
	bool is_single_;
	StateMgr stateMgr_;
	// 分離時のキー
	SingleKeys keys_;

	float dead_limit_;
};



