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
	virtual void onInit() = 0;
	// �X�V����	
	virtual void onUpdate(float deltaTime) = 0;
	// �I��������
	virtual void onEnd() = 0;
	// �L�[���͏���
	virtual void onKeyInput(float deltaTime) = 0;
	// �p�b�h���͏���
	virtual void onPadInput(float deltaTime) = 0;
	// �ړ�����
	virtual void onMove(float deltaTime) = 0;
protected:
	// �v���C���[�|�C���^
	PlayerBodyPtr holdBody_;
	// �v���C���[�|�C���^
	PlayerBodyPtr moveBody_;
};