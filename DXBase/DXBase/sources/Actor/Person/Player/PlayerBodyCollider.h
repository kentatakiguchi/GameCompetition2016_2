#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include "PlayerPtr.h"

#include "Player.h"

#include "HitOpponent.h"

// ÉvÉåÅ[ÉÑÅ[
class PlayerBodyCollider : public Actor {
public:
	PlayerBodyCollider(IWorld* world, std::string& name);
	~PlayerBodyCollider();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void pos_update(Vector2 parent_pos);
	void reset_pos();
	Vector2 other_velocity();
	Vector2 other_position();
	HitOpponent opponent();
private:
	HitOpponent opponent_;
	Vector2 other_velocity_;
	Vector2 other_position_;

};
