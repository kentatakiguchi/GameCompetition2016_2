#pragma once

#include "../Base/PlayerState_HoldBase_Wall.h"
#include "../Base/PlayerState_HoldBase_Begin.h"

// �v���C���[�Е����������
class PlayerState_HoldBegin : public PlayerState_HoldBase_Wall, public PlayerState_HoldBase_Begin {
public:
	// �R���X�g���N�^
	PlayerState_HoldBegin(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// �L�[���͏���
	virtual void onKeyInput(float deltaTime)override;
	// �p�b�h���͏���
	virtual void onPadInput(float deltaTime)override;
};