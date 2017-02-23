#pragma once

#include "../Base/PlayerState_HoldBase_Wall.h"
#include "../Base/PlayerState_HoldBase_Full.h"

// プレイヤー伸び最大状態
class PlayerState_HoldFull : public PlayerState_HoldBase_Wall, public PlayerState_HoldBase_Full {
public:
	// コンストラクタ
	PlayerState_HoldFull(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// キー入力処理
	virtual void onKeyInput(float deltaTime)override;
	// パッド入力処理
	virtual void onPadInput(float deltaTime)override;
};
