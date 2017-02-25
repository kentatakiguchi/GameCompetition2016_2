#pragma once

#include "../../../PlayerState_Union.h"

// �v���C���[�������x�[�X
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
	// ���͏���
	virtual void input(float deltaTime) override;
private:
	// �ړ�����
	void move(float deltaTime);
private:
	// �ړ����x�v�Z
	Vector2 input_vector(const Vector2& input, float deltaTime);
protected:
	// �������{�^�������ꂽ���ǂ���
	bool hold_released();
private:
	// ������
	virtual void onInit() = 0;
	// �X�V����	
	virtual void onUpdate(float deltaTime) = 0;
	// �I��������
	virtual void onEnd() = 0;
	// �p�b�h���͏���
	virtual void onInput(float deltaTime) = 0;
	// �ړ�����
	virtual void onMove(float deltaTime) = 0;
protected:
	// �v���C���[�|�C���^(�������Ă���)
	PlayerBodyPtr holdBody_;
	// �v���C���[�|�C���^(�ړ��\��Body)
	PlayerBodyPtr moveBody_;
};