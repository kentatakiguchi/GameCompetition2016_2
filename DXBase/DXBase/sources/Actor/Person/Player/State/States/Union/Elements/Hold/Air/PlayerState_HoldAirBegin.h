#pragma once

#include "../Base/PlayerState_HoldBase_Air.h"
#include "../Base/PlayerState_HoldBase_Begin.h"

// �v���C���[�Е����������
class PlayerState_HoldAirBegin : public PlayerState_HoldBase_Air, public PlayerState_HoldBase_Begin {
public:
	// �R���X�g���N�^
	PlayerState_HoldAirBegin(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
};