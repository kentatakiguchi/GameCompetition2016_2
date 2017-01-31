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
	virtual void onCollide(Actor& other) override;

	void commonCollide(Actor& other);
	void singleCollide(Actor& other);
	void unionCollide(Actor& other);

	void alpheUpdate(float deltaTime);

	void change_state(PlayerState_Enum_Single state);

	void collider();

	Vector2& velocity();
	float& dump();
	void posUpdate(float deltaTime);

	bool able_to_hold();
	bool able_to_jump();
	bool is_hit();

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
	void single_action(float deltaTime);
	Vector2 get_partner_vector();
	void reset_dead_limit();
	void count_dead_limit(float deltaTime);

	Vector2& hit_vector();

	PlayerAnimation2D& animation();

	Vector2 GetVelo() { return velocity_; }

	//強制移動関数(速度版)
	void ForcedMove(Vector2 velocity);
private:
	PlayerStateMgr_Single stateMgr_;
	PlayerAnimation2D animation_;

	Vector2 velocity_;
	Vector2 slope_;
	PlayerBodyPtr partner_;
	HitOpponent opponent_;
	HitOpponent hit_partner_;
	HitOpponent hit_enemy_;

	float dead_limit_;
	float timer_;
	PlayerBodyCollPtr collider_;
	//PlayerBodyCollPtr attack_collider_;

	Vector2 v_;
	float bodyDump_;
	float dumpTimer_;

	float stiffness_;
	float friction_;
	float mass_;
	std::map<int,TextureID> NumIDs;
};



