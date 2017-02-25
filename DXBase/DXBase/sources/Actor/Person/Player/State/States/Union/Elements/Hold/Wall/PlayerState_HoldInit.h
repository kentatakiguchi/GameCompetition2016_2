#pragma once

#include "../Base/PlayerState_HoldBase.h"

// �v���C���[�Е����������
class PlayerState_HoldInit : public PlayerState_HoldBase {
public:
	// �R���X�g���N�^
	PlayerState_HoldInit(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// ��ԌŗL�̏�����
	virtual void onInit() override;
	// �X�V����	
	virtual void onUpdate(float deltaTime)override;
	// �I��������
	virtual void onEnd()override;
	// �p�b�h���͏���
	virtual void onInput(float deltaTime)override;
	// �ړ�����
	virtual void onMove(float deltaTime)override;
};