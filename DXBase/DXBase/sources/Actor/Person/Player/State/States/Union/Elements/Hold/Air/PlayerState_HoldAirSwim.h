#pragma once

#include "../Base/PlayerState_HoldBase_Air.h"
#include "../Base/PlayerState_HoldBase_Swim.h"

// プレイヤー片方くっつき状態
class PlayerState_HoldAirSwim : public PlayerState_HoldBase_Air, public PlayerState_HoldBase_Swim {
public:
	// コンストラクタ
	PlayerState_HoldAirSwim(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
};