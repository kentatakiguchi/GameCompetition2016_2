#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "PlayerPtr.h"
#include "State/States/Union/PlayerStateMgr_Union.h"
#include "../../../Renderer/Puyo_Texture_K.h"

#include "Player.h"

// プレーヤー
class PlayerConnector : public Actor {
public:
	PlayerConnector(IWorld* world, const Vector2 & position, PlayerBodyPtr butty, PlayerBodyPtr retty);
	~PlayerConnector();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	PlayerBodyPtr blue_body();
	PlayerBodyPtr red_body();
	PlayerStateMgr_Union& state_mgr();
	void state_action(float deltaTime);
	void create_point(int point_num = 0);

	Vector2 get_point(int index);
	std::vector<Vector2> get_points();
private:
	// ダメージを受けたかどうか
	bool is_damaged();
	// クリアしたかどうか
	bool is_cleared();
	// 死亡したかどうか
	bool is_dead();

	void puyoUpdate();
private:
	PlayerStateMgr_Union stateMgr_;

	PlayerBodyPtr butty_;
	PlayerBodyPtr retty_;
	std::vector<PlayerBodyPointPtr> points;

	//ぷよテクスチャ
	PuyoTextureK* mPuyo;
	//ひっぱる力
	float mPower;
	//補間
	Vector2 mPuyoResPos;
	Vector2 mPuyoPos;
	Vector2 mPuyoVelo;
	//ぷよする時間
	float mPuyoTimer;
	bool mPuyoFlag;
};
