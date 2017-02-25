#pragma once

#include "../Base/PlayerState_HoldBase_Air.h"
#include "../Base/PlayerState_HoldBase_Swim.h"

// �v���C���[�Е����������
class PlayerState_HoldAirSwim : public PlayerState_HoldBase_Air, public PlayerState_HoldBase_Swim {
public:
	// �R���X�g���N�^
	PlayerState_HoldAirSwim(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// ������
	virtual void onInit()override;
	// �X�V����	
	virtual void onUpdate(float deltaTime)override;
	// �I��������
	virtual void onEnd()override;
	// �p�b�h���͏���
	virtual void onInput(float deltaTime)override;
	// �ړ�����
	virtual void onMove(float deltaTime)override;
};