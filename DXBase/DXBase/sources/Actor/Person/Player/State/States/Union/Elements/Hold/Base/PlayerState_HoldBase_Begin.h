#pragma once

#include "../Base/PlayerState_HoldBase.h"

// �v���C���[�L�юn�߂̏��
class PlayerState_HoldBase_Begin : public virtual PlayerState_HoldBase {
public:
	// �R���X�g���N�^
	PlayerState_HoldBase_Begin(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
protected:
	// ��ԌŗL�̏�����
	virtual void onInit() override;
	// �I��������
	virtual void onEnd()override;
	// �p�b�h���͏���
	virtual void onInput(float deltaTime)override;
};