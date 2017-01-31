#pragma once

#include "../PlayerState_Union.h"

// �v���C���[�Е��ړ����
class PlayerState_MoveEach : public PlayerState_Union {
public:
	// �R���X�g���N�^
	PlayerState_MoveEach(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
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
	// �A�j���[�V�������]
	void flip_animation();
};