#pragma once

#include "../Base/PlayerState_HoldBase.h"

// �v���C���[�Е����������
class PlayerState_HoldBegin : public PlayerState_HoldBase {
public:
	// �R���X�g���N�^
	PlayerState_HoldBegin(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// ��ԌŗL�̏�����
	virtual void onInit() override;
	// �X�V����	
	virtual void onUpdate(float deltaTime)override;
	// �I��������
	virtual void onEnd()override;
	// �L�[���͏���
	virtual void onKeyInput(float deltaTime)override;
	// �p�b�h���͏���
	virtual void onPadInput(float deltaTime)override;
	// �ړ�����
	virtual void onMove(float deltaTime)override;
};