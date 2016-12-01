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
	PlayerConnector(IWorld* world, const Vector2 & position, PlayerBodyPtr butty, PlayerBodyPtr retty);
	~PlayerConnector();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void create_point(int point_num = 0);
	Vector2 base_point(ActionType type);

	Vector2 target();
	Vector2 comp();

	Vector2 target_vector(int index);
	Vector2 clamp_target(Vector2 pos, int index);
private:
	BezierCurve bezier_;
	
	PlayerBodyPtr butty_;
	PlayerBodyPtr retty_;
	std::vector<PlayerBodyPointPtr> points;

	int base_index_;

	ActionType action_type_;
};
