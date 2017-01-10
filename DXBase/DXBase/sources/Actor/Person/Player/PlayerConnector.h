#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"

#include "PlayerPtr.h"
#include "State/States/Union/PlayerStateMgr_Union.h"
#include "../../../Renderer/Puyo_Texture_K.h"

// プレーヤーコネクタ
class PlayerConnector : public Actor {
public:
	// コンストラクタ
	PlayerConnector(IWorld* world, const Vector2 & position, PlayerBodyPtr butty, PlayerBodyPtr retty);
	// デストラクタ
	~PlayerConnector();
	// 更新処理
	virtual void onUpdate(float deltaTime) override;
	// 描画処理
	virtual void onDraw() const override;
	// body取得(青)
	PlayerBodyPtr blue_body();
	// body取得(赤)
	PlayerBodyPtr red_body();
	// 
	PlayerStateMgr_Union& state_mgr();

	void state_update(float deltaTime);
	void create_point(int point_num = 0);
	float length_sum();

	Vector2 get_point(int index);
public:
	PlayerStateMgr_Union stateMgr_;
private:
	// ダメージを受けたかどうか
	bool is_damaged();
	// クリアしたかどうか
	bool is_cleared();

	void puyoUpdate();
private:


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
