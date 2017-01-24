#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include "State/States/Single/PlayerStateMgr_Single.h"
#include "PlayerPtr.h"
#include "HitOpponent.h"
#include<map>
#include "../../../Animation/Player/PlayerAnimation2D.h"
#include"../../../ResourceLoader/ResourceLoader.h"

// プレーヤー
class PlayerBody : public Actor {
public:
	PlayerBody();
	PlayerBody(IWorld* world, const std::string name, const Vector2& position);
	~PlayerBody();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onCollide(Actor& other) override;

	void change_state(PlayerState_Enum_Single state);
	void move(Vector2 vector);

	void chase();
	void gravity();
	void acc_gravity();

	bool able_to_hold();
	bool able_to_jump();
	bool is_hit();

	void hold_gravity();
	void clamp();
	void launch(Vector2 dir);
	HitOpponent hitOpponent();
	HitOpponent hit_partner();
	HitOpponent hit_enemy();
	void reset_opponent();
	void reset_partner();
	void reset_enemy();
	void reset_slope();
	float distance();
	void set_partner(PlayerBodyPtr partner);
	void set_hold_point();
	bool dead_limit();
	bool isInv();
	void single_action(float deltaTime);
	Vector2 get_partner_vector();
	void create_attack_collider_();
	void delete_attack_collider_();
	void reset_dead_limit();
	void count_dead_limit(float deltaTime);

	PlayerAnimation2D& animation();

	Vector2 GetVelo() { return velocity_; }

	//強制移動関数(速度版)
	void ForcedMove(Vector2 velocity);
private:
	PlayerStateMgr_Single stateMgr_;
	PlayerAnimation2D animation_;

	Vector2 input_;
	Vector2 velocity_;
	Vector2 gravity_;
	Vector2 slope_;
	Vector2 launch_;
	PlayerBodyPtr partner_;
	HitOpponent opponent_;
	HitOpponent hit_partner_;
	HitOpponent hit_enemy_;

	float dead_limit_;
	float timer_;
	PlayerBodyCollPtr collider_;
	PlayerBodyCollPtr attack_collider_;

	Vector2 v_;

	float stiffness_;
	float friction_;
	float mass_;

	Vector2 suction_;

	std::map<int,TextureID> NumIDs;
};



