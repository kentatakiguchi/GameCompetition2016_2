#pragma once

#include "../Base/PlayerState_HoldBase_Wall.h"
#include "../Base/PlayerState_HoldBase_Swim.h"

// プレイヤー片方くっつき状態
class PlayerState_HoldSwim : public PlayerState_HoldBase_Wall, public PlayerState_HoldBase_Swim {
public:
	// コンストラクタ
	PlayerState_HoldSwim(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// キー入力処理
	virtual void onKeyInput(float deltaTime)override;
	// パッド入力処理
	virtual void onPadInput(float deltaTime)override;
};