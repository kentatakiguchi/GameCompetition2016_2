#pragma once

#include "Base/PlayerState_MoveBase.h"

// プレイヤー片方移動状態
class PlayerState_MoveEachL : public PlayerState_MoveBase {
public:
	// コンストラクタ
	PlayerState_MoveEachL(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// 状態固有の初期化
	virtual void onInit() override;
	// 更新処理
	virtual void onUpdate(float deltaTime) override;
	// 衝突処理
	virtual void onCollide(const Actor & other) override {}
	// 終了時処理
	virtual void onEnd() override;
	// キー入力処理
	virtual void onKeyInput(float deltaTime) override;
	// パッド入力処理
	virtual void onPadInput(float deltaTime) override;
};