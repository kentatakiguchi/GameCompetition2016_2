#pragma once

#include "Base/PlayerState_MoveBase.h"

// �v���C���[�Е��ړ����
class PlayerState_MoveEachL : public PlayerState_MoveBase {
public:
	// �R���X�g���N�^
	PlayerState_MoveEachL(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// ��ԌŗL�̏�����
	virtual void onInit() override;
	// �X�V����
	virtual void onUpdate(float deltaTime) override;
	// �Փˏ���
	virtual void onCollide(const Actor & other) override {}
	// �I��������
	virtual void onEnd() override;
	// �L�[���͏���
	virtual void onKeyInput(float deltaTime) override;
	// �p�b�h���͏���
	virtual void onPadInput(float deltaTime) override;
};