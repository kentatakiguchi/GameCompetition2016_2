#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "PlayerStruct.h"

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
	PlayerConnector(IWorld* world, PlayerBodyPtr main, PlayerBodyPtr sub);
	~PlayerConnector();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void create_point(int point_num = 0);
	float distance();
private:
	BezierCurve bezier_;
	
	PlayerBodyPtr main_;
	PlayerBodyPtr sub_;
	std::vector<Vector2> points;

	PuyoTextureK* puyo;

	Vector2 pos;
	Vector2 scale;
	float rotate;
};
