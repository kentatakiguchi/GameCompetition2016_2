#pragma once

#include "../PlayerState_Union.h"

// �������
class PlayerState_StandBy : public PlayerState_Union {
public:
	// �R���X�g���N�^
	PlayerState_StandBy(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// ��ԌŗL�̏�����
	virtual void unique_init() override;
	// �X�V����	
	virtual void update(float deltaTime) override {}
	// �I��������
	virtual void end() override {}
};