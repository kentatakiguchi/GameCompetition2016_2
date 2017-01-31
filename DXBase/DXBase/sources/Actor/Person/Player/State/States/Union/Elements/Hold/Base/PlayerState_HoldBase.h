#pragma once

#include "../../../PlayerState_Union.h"

// プレイヤー片方くっつき状態
class PlayerState_HoldBase : public PlayerState_Union {
public:
	// コンストラクタ
	PlayerState_HoldBase(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// 状態固有の初期化
	virtual void unique_init() override;
	// 更新処理	
	virtual void update(float deltaTime) override;
	// 終了時処理
	virtual void end() override;
	// キー入力処理
	virtual void key_input(float deltaTime) override;
	// パッド入力処理
	virtual void pad_input(float deltaTime) override;
private:
	// 移動処理
	void move(float deltaTime);
private:
	// 初期化
	virtual void onInit();
	// 更新処理	
	virtual void onUpdate(float deltaTime);
	// 終了時処理
	virtual void onEnd();
	// キー入力処理
	virtual void onKeyInput(float deltaTime);
	// パッド入力処理
	virtual void onPadInput(float deltaTime);
	// 移動処理
	virtual void onMove(float deltaTime);
};