#pragma once

#include "../PlayerState_Union.h"

// �v���C���[�ҋ@���
class PlayerState_Idle : public PlayerState_Union {
public:
	// �R���X�g���N�^
	PlayerState_Idle(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// ��ԌŗL�̏�����
	virtual void unique_init() override;
	// �X�V����	
	virtual void update(float deltaTime) override;
	// �Փˏ���
	virtual void collide(const Actor & other) override {}
	// �I��������
	virtual void end() override;
	// ���͏���
	virtual void input(float deltaTime) override;
private:
	// �ړ�����
	void move(float deltaTime);
};