#pragma once

#include "../../PlayerState_Union.h"

// プレイヤー片方移動状態
class PlayerState_MoveEach : public PlayerState_Union {
public:
	// コンストラクタ
	PlayerState_MoveEach(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// 状態固有の初期化
	virtual void unique_init() override;
	// 更新処理
	virtual void update(float deltaTime) override;
	// 衝突処理
	virtual void collide(const Actor & other) override {}
	// 終了時処理
	virtual void end() override;
	// 入力処理
	virtual void input(float deltaTime) override;
private:
	// 移動処理
	void move(float deltaTime);
	// アニメーション反転
	void flip_animation();
private:
	// プレイヤーポインタ
	PlayerBodyPtr manuBody_;
	// プレイヤーポインタ
	PlayerBodyPtr autoBody_;
};