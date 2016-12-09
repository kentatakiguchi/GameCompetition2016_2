#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "State/States/Union/PlayerStateMgr_Union.h"
//#include "PlayerBody.h"
//#include "PlayerConnector.h"

#include "PlayerPtr.h"
#include "../../../Renderer/Puyo_Texture_K.h"

// プレーヤー
class Player : public Actor {
public:
	enum class MOTION {};
public:
	Player(IWorld* world, const Vector2& position);
	~Player();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	PlayerBodyPtr blue_body();
	PlayerBodyPtr red_body();
	PlayerCntrPtr connector();

	void set_body();
public:
	// 接続処理
	void connect();
	// 接続可能かどうか
	bool is_connectable();
	// 死亡したかどうか
	bool is_dead();
private:
	//PlayerStateMgr_Union stateMgr_;
	// mainとなる部位
	PlayerBodyPtr retty_;
	// sub となる部位
	PlayerBodyPtr butty_;
	// コネクター
	//PlayerCntrPtr cntr_;
};

