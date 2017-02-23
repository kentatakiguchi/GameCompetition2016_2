#pragma once

#include "../Base/PlayerState_HoldBase_Wall.h"
#include "../Base/PlayerState_HoldBase_Swim.h"

// �v���C���[�Е����������
class PlayerState_HoldSwim : public PlayerState_HoldBase_Wall, public PlayerState_HoldBase_Swim {
public:
	// �R���X�g���N�^
	PlayerState_HoldSwim(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// �L�[���͏���
	virtual void onKeyInput(float deltaTime)override;
	// �p�b�h���͏���
	virtual void onPadInput(float deltaTime)override;
};