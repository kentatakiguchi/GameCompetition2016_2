#pragma once

#include "../../../PlayerState_Union.h"

// プレイヤー片方移動状態
class PlayerState_MoveBase : public PlayerState_Union {
public:
	// コンストラクタ
	PlayerState_MoveBase(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// 状態固有の初期化
	virtual void unique_init() override;
	// 更新処理
	virtual void update(float deltaTime) override;
	// 衝突処理
	virtual void collide(const Actor & other) override {}
	// 終了時処理
	virtual void end() override;
	// キー入力処理
	virtual void key_input(float deltaTime) override;
	// パッド入力処理
	virtual void pad_input(float deltaTime) override;
private:
	virtual void onInit() {}
	virtual void onUpdate(float deltaTime) {}
	virtual void onCollide(const Actor & other) {}
	virtual void onEnd() {}
	virtual void onKeyInput(float deltaTime) {}
	virtual void onPadInput(float deltaTime) {}
private:
	// 移動処理
	void move(float deltaTime);
	// アニメーション反転
	void flip_animation();
};