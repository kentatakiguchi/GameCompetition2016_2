#include "PlayerState_HoldAirSwim.h"

// コンストラクタ
PlayerState_HoldAirSwim::PlayerState_HoldAirSwim(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) :
	PlayerState_HoldBase(butty, retty),
	PlayerState_HoldBase_Air(butty, retty),
	PlayerState_HoldBase_Swim(butty, retty){}
