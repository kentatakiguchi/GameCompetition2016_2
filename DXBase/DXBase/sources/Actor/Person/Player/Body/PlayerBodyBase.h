#pragma once

#include "../../../Base/Actor.h"
#include "../../../../World/IWorld.h"
#include "../State/States/Single/PlayerStateMgr_Single.h"
#include "../PlayerPtr.h"
#include "../HitOpponent.h"
#include "../../../../Animation/Player/PlayerAnimation2D.h"
#include "../../../../ResourceLoader/ResourceLoader.h"

// プレーヤーベース
class PlayerBodyBase : public Actor {
public:
	PlayerBodyBase();
	PlayerBodyBase(IWorld* world, const std::string name, const Vector2& position);
	~PlayerBodyBase();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	virtual void hitField(const FieldPtr& field)override;

	void drawBody() const;

	void commonCollide(Actor& other);
	void unionCollide(Actor& other);

	void change_state(PlayerState_Enum_Single state);
	PlayerStateMgr_Single& stateMgr();

	void collider();

	Vector2& velocity();
	float& dump();

	bool able_to_hold();
	bool able_to_jump();
	bool is_hit();

	HitOpponent hit_enemy();
	void reset_opponent();
	void reset_enemy();
	void reset_slope();
	float distance();
	void set_partner(PlayerBodyPtr partner);
	void set_hold_point();
	void single_action(float deltaTime);
	Vector2 get_partner_vector();

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
	HitOpponent hit_enemy_;

	float timer_;
	PlayerBodyCollPtr collider_;

	Vector2 pre_;

	ActorPtr cntr_;

	Vector2 v_;
	float bodyDump_;
	float dumpTimer_;

	float stiffness_;
	float friction_;
	float mass_;
};
