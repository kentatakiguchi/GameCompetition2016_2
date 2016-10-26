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

// プレーヤー
class Player : public Actor {
public:
	using PlayerBodyPtr = std::shared_ptr<PlayerBody>;

	enum class MOTION {};
public:
	Player(IWorld* world, const Vector3& position);
	~Player();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void changeMotion(float deltaTime);
	void setBody(PlayerBodyPtr main, PlayerBodyPtr sub);
	PlayerBodyPtr getMainBody();
	PlayerBodyPtr getSubBody();

	void createOval(Vector3 main_pos, Vector3 sub_pos, int height)const;
	void createOval(Vector3 center, float width, int height)const;
	

	void field();	

	Vector2 GetVelo()
	{
		return mVelo;
	}
	Vector2 GetSpringVelo()
	{
		return veloPlus;
	}
private:
	void createWindow();
	StateMgr stateMgr_;

	int hp_;
	
	PlayerBodyPtr main_body_;
	PlayerBodyPtr sub_body_;

	Vector2 prePosition;						// 移動前の座標	
	Vector2 curPosition;						// 移動後の座標
	Vector2 mVelo;                              //プレイヤーの速度
	Vector2 mPositionVelo;                      //速度用の座標
};

