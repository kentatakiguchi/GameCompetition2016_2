#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "Field.h"
//#include "Ray.h"
//#include "Bullet.h"
//#include "EventMessage.h"
#include "../../../Math/Vector3.h"
#include "State/Base/StateMgr.h"
#include "PlayerBody.h"

// ÉvÉåÅ[ÉÑÅ[
class Player : public Actor {
public:
	using PlayerBodyPtr = std::shared_ptr<PlayerBody>;

	enum class MOTION {};
public:
	Player(IWorld* world, const Vector3& position);
	~Player();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void changeMotion(float deltaTime);
	void setBody(PlayerBodyPtr main, PlayerBodyPtr sub);
	PlayerBodyPtr getMainBody();
	PlayerBodyPtr getSubBody();

	void createOval(Vector3 r_pos, Vector3 l_pos, int height)const;
	void createOval(Vector3 center, float width, int height)const;
	//void field();
private:
	void createWindow();
	StateMgr stateMgr_;

	int hp_;
	
	PlayerBodyPtr main_body_;
	PlayerBodyPtr sub_body_;
};

