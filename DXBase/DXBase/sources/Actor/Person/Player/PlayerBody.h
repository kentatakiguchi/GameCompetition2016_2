#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "State/Base/StateMgr.h"
#include "PlayerStruct.h"
#include "HitOpponent.h"

#include "../../../Animation/Base/Animation2D.h"

// プレーヤー
class PlayerBody : public Actor {
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
	void move_hold(Vector2 vector);

	void sprit_move(KeyCode up = KeyCode::UP, KeyCode down = KeyCode::DOWN, KeyCode right = KeyCode::RIGHT, KeyCode left = KeyCode::LEFT);
	void chase();
	void gravity();
	void acc_gravity();

	bool able_to_hold();
	bool able_to_jump();
	bool is_hit();

	void hold_gravity();
	void circleClamp();
	void launch(Vector2 dir);
	HitOpponent hitOpponent();
	HitOpponent hit_partner();
	HitOpponent hit_enemy();
	void reset_opponent();
	void reset_partner();
	void reset_enemy();
	void reset_velocity();
	float distance();
	void set_partner(PlayerBodyPtr partner);
	void set_hold_point();
	PlayerBodyPtr get_partner();
	bool isDead();
	bool isInv();
	void single_action(float deltaTime);
	SingleKeys get_keys();

	Vector2 get_partner_vector();
	void create_attack_collider_();
	void delete_attack_collider_();
	void reset_dead_limit();
	void count_dead_limit(float deltaTime);

	Vector2 GetVelo() {
		return Vector2(velocity_.x, velocity_.y);
	}
private:
	Vector2 input_;
	Vector2 velocity_;
	Vector2 gravity_;
	Vector2 launch_;
	Vector2 last_pos_;
	PlayerBodyPtr partner_;
	HitOpponent opponent_;
	HitOpponent hit_partner_;
	HitOpponent hit_enemy_;
	Vector2 oppenent_pos_;

	float jump_power_;
	// 単独状態か否か
	bool is_single_;
	StateMgr stateMgr_;
	// 分離時のキー
	SingleKeys keys_;

	float dead_limit_;

	PlayerBodyCollPtr collider_;
	PlayerBodyCollPtr attack_collider_;

	Vector3 draw_pos_;

	Animation2D animation_;
};



