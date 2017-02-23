#pragma once

#include "../Base/PlayerState_HoldBase.h"

// �v���C���[�L�эő���
class PlayerState_HoldBase_Full : public virtual PlayerState_HoldBase {
public:
	// �R���X�g���N�^
	PlayerState_HoldBase_Full(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
protected:
	// ��ԌŗL�̏�����
	virtual void onInit() override;
	// �I��������
	virtual void onEnd()override;
	// �L�[���͏���
	virtual void onKeyInput(float deltaTime)override;
	// �p�b�h���͏���
	virtual void onPadInput(float deltaTime)override;
};