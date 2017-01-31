#pragma once

#include "../../../PlayerState_Union.h"

// �v���C���[�Е����������
class PlayerState_HoldBase : public PlayerState_Union {
public:
	// �R���X�g���N�^
	PlayerState_HoldBase(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// ��ԌŗL�̏�����
	virtual void unique_init() override;
	// �X�V����	
	virtual void update(float deltaTime) override;
	// �I��������
	virtual void end() override;
	// �L�[���͏���
	virtual void key_input(float deltaTime) override;
	// �p�b�h���͏���
	virtual void pad_input(float deltaTime) override;
private:
	// �ړ�����
	void move(float deltaTime);
private:
	// ������
	virtual void onInit();
	// �X�V����	
	virtual void onUpdate(float deltaTime);
	// �I��������
	virtual void onEnd();
	// �L�[���͏���
	virtual void onKeyInput(float deltaTime);
	// �p�b�h���͏���
	virtual void onPadInput(float deltaTime);
	// �ړ�����
	virtual void onMove(float deltaTime);
};