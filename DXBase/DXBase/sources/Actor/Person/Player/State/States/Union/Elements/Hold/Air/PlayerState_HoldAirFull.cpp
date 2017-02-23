#include "PlayerState_HoldAirFull.h"

// コンストラクタ
PlayerState_HoldAirFull::PlayerState_HoldAirFull(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : 
	PlayerState_HoldBase(butty, retty),
	PlayerState_HoldBase_Air(butty, retty),
	PlayerState_HoldBase_Full(butty, retty) {}

