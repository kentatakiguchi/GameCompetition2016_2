#pragma once

#include "Base/PlayerState_HoldBase.h"

class PlayerState_HoldItem : public PlayerState_HoldBase {
public:
	// コンストラクタ
	PlayerState_HoldItem(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// 状態固有の初期化
	virtual void onInit() override;
	// 更新処理	
	virtual void onUpdate(float deltaTime)override;
	// 終了時処理
	virtual void onEnd()override;
	// キー入力処理
	virtual void onKeyInput(float deltaTime)override;
	// パッド入力処理
	virtual void onPadInput(float deltaTime)override;
	// 移動処理
	virtual void onMove(float deltaTime)override;
private:
	// プレイヤーポインタ
	PlayerBodyPtr holdBody_;
	// プレイヤーポインタ
	PlayerBodyPtr moveBody_;
};