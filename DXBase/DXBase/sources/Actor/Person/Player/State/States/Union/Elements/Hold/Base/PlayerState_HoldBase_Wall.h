#pragma once

#include "../Base/PlayerState_HoldBase.h"

// �v���C���[�ǂ�������ԃx�[�X
class PlayerState_HoldBase_Wall : public virtual PlayerState_HoldBase{
public:
	// �R���X�g���N�^
	PlayerState_HoldBase_Wall(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
protected:
	// �X�V����	
	virtual void onUpdate(float deltaTime)override;
	// �p�b�h���͏���
	virtual void onInput(float deltaTime)override;
	// �ړ�����
	virtual void onMove(float deltaTime)override;
};