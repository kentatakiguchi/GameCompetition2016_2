#include "PlayerState_HoldAirBegin.h"

// �R���X�g���N�^
PlayerState_HoldAirBegin::PlayerState_HoldAirBegin(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) :
	PlayerState_HoldBase(butty, retty),
	PlayerState_HoldBase_Air(butty, retty),
	PlayerState_HoldBase_Begin(butty, retty) {}

