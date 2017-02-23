#pragma once

#include "../Base/PlayerState_HoldBase_Air.h"
#include "../Base/PlayerState_HoldBase_Begin.h"

// プレイヤー片方くっつき状態
class PlayerState_HoldAirBegin : public PlayerState_HoldBase_Air, public PlayerState_HoldBase_Begin {
public:
	// コンストラクタ
	PlayerState_HoldAirBegin(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
};