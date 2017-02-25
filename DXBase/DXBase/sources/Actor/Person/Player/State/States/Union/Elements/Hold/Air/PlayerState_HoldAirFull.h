#pragma once

#include "../Base/PlayerState_HoldBase_Air.h"
#include "../Base/PlayerState_HoldBase_Full.h"

// �v���C���[�L�эő���
class PlayerState_HoldAirFull : public PlayerState_HoldBase_Air, public PlayerState_HoldBase_Full {
public:
	// �R���X�g���N�^
	PlayerState_HoldAirFull(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
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
