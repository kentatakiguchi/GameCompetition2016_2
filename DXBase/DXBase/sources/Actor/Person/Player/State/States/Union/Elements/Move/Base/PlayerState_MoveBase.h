#pragma once

#include "../../../PlayerState_Union.h"

// �v���C���[�Е��ړ����
class PlayerState_MoveBase : public PlayerState_Union {
public:
	// �R���X�g���N�^
	PlayerState_MoveBase(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
private:
	// ��ԌŗL�̏�����
	virtual void unique_init() override;
	// �X�V����
	virtual void update(float deltaTime) override;
	// �Փˏ���
	virtual void collide(const Actor & other) override {}
	// �I��������
	virtual void end() override;
	// �L�[���͏���
	virtual void key_input(float deltaTime) override;
	// �p�b�h���͏���
	virtual void pad_input(float deltaTime) override;
private:
	virtual void onInit() {}
	virtual void onUpdate(float deltaTime) {}
	virtual void onCollide(const Actor & other) {}
	virtual void onEnd() {}
	virtual void onKeyInput(float deltaTime) {}
	virtual void onPadInput(float deltaTime) {}
private:
	// �ړ�����
	void move(float deltaTime);
	// �A�j���[�V�������]
	void flip_animation();
};