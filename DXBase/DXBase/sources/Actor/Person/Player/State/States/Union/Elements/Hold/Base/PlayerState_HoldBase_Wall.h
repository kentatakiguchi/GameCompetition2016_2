#pragma once

#include "../Base/PlayerState_HoldBase.h"

// �v���C���[�Е����������
class PlayerState_HoldBase_Wall : public virtual PlayerState_HoldBase{
public:
	// �R���X�g���N�^
	PlayerState_HoldBase_Wall(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
protected:
	// �X�V����	
	virtual void onUpdate(float deltaTime)override;
	// �L�[���͏���
	virtual void onKeyInput(float deltaTime)override;
	// �p�b�h���͏���
	virtual void onPadInput(float deltaTime)override;
	// �ړ�����
	virtual void onMove(float deltaTime)override;
};