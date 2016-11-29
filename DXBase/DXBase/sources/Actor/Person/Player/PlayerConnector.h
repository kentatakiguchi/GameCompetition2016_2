#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "PlayerPtr.h"

#include "../../../Math/BezierCurve.h"
#include "../../../Renderer/Puyo_Texture_K.h"

#include "Player.h"

// ÉvÉåÅ[ÉÑÅ[
class PlayerConnector : public Actor {
public:
	enum class Opponent {
		NONE,
		FLOOR,
		ITEM,
		ENEMY,
		TEST
	};
public:
	PlayerConnector();
	PlayerConnector(IWorld* world, PlayerBodyPtr butty, PlayerBodyPtr retty);
	~PlayerConnector();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void create_point(int point_num = 0);
	float distance();
	Vector2 base_point(ActionType type);
	Vector2 composed_vector(Vector2 point, int index);
	Vector2 lerp_target(int index);
	Vector2 target();
	Vector2 comp();
private:
	BezierCurve bezier_;
	
	PlayerBodyPtr butty_;
	PlayerBodyPtr retty_;
	std::vector<PlayerBodyPointPtr> points;

	Vector2 pos;
	Vector2 scale;
	float rotate;

	int base_index_;

	ActionType action_type_;
};
