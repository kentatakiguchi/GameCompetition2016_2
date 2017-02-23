#pragma once

#include "../Base/PlayerState_HoldBase_Wall.h"
#include "../Base/PlayerState_HoldBase_Begin.h"

// プレイヤー片方くっつき状態
class PlayerState_HoldBegin : public PlayerState_HoldBase_Wall, public PlayerState_HoldBase_Begin {
public:
	// コンストラクタ
	PlayerState_HoldBegin(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// キー入力処理
	virtual void onKeyInput(float deltaTime)override;
	// パッド入力処理
	virtual void onPadInput(float deltaTime)override;
};