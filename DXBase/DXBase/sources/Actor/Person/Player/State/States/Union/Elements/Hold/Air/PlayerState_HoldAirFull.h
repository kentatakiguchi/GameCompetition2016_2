#pragma once

#include "../Base/PlayerState_HoldBase_Air.h"
#include "../Base/PlayerState_HoldBase_Full.h"

// プレイヤー伸び最大状態
class PlayerState_HoldAirFull : public PlayerState_HoldBase_Air, public PlayerState_HoldBase_Full {
public:
	// コンストラクタ
	PlayerState_HoldAirFull(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
};
