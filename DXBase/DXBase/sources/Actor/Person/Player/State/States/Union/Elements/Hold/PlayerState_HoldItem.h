#pragma once

#include "Base/PlayerState_HoldBase_Wall.h"

class PlayerState_HoldItem : public PlayerState_HoldBase_Wall {
public:
	// �R���X�g���N�^
	PlayerState_HoldItem(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// ��ԌŗL�̏�����
	virtual void onInit() override;
	// �X�V����	
	virtual void onUpdate(float deltaTime)override;
	// �I��������
	virtual void onEnd()override;
	// �p�b�h���͏���
	virtual void onInput(float deltaTime)override;
};