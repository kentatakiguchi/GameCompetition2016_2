#pragma once

#include "../Base/PlayerState_HoldBase.h"

// �v���C���[�L�шړ������
class PlayerState_HoldBase_Swim : public virtual PlayerState_HoldBase {
public:
	// �R���X�g���N�^
	PlayerState_HoldBase_Swim(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
protected:
	// ��ԌŗL�̏�����
	virtual void onInit() override;
	// �I��������
	virtual void onEnd()override;
	// �p�b�h���͏���
	virtual void onInput(float deltaTime)override;
};