#pragma once

#include "../Base/PlayerState_HoldBase_Wall.h"
#include "../Base/PlayerState_HoldBase_Swim.h"

// �v���C���[�Е����������
class PlayerState_HoldSwim : public PlayerState_HoldBase_Wall, public PlayerState_HoldBase_Swim {
public:
	// �R���X�g���N�^
	PlayerState_HoldSwim(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
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