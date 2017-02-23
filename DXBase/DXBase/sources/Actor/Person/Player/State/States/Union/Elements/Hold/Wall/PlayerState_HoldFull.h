#pragma once

#include "../Base/PlayerState_HoldBase_Wall.h"
#include "../Base/PlayerState_HoldBase_Full.h"

// �v���C���[�L�эő���
class PlayerState_HoldFull : public PlayerState_HoldBase_Wall, public PlayerState_HoldBase_Full {
public:
	// �R���X�g���N�^
	PlayerState_HoldFull(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// �L�[���͏���
	virtual void onKeyInput(float deltaTime)override;
	// �p�b�h���͏���
	virtual void onPadInput(float deltaTime)override;
};
