#pragma once

#include "../Base/PlayerState_HoldBase.h"

// �v���C���[�󒆂ł̂�������ԃx�[�X
class PlayerState_HoldBase_Air : public virtual PlayerState_HoldBase {
public:
	// �R���X�g���N�^
	PlayerState_HoldBase_Air(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
protected:
	// �X�V����	
	virtual void onUpdate(float deltaTime)override;
	// �ړ�����
	virtual void onMove(float deltaTime)override;
};
