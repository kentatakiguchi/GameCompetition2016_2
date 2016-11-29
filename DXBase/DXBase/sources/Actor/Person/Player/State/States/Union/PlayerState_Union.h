#pragma once

#include "../../Base/IState.h"

#include "../../PlayerState_Enum.h"

#include "../../../PlayerPtr.h"
#include "../../../Player.h"
#include "../../../PlayerBody.h"

// �e�v���C���[�X�e�[�g�̊��N���X
class PlayerState_Union : public IState {
public:
	// �R���X�g���N�^
	PlayerState_Union();
	// �S�ẴX�e�[�g�ɋ��ʂ��鏉��������
	virtual void common_init(Actor& actor, ActionType type) override;
	// ���͏���
	virtual void input() override;
	// �X�e�[�g�̕ύX����
	virtual void change(StateElement element) override;
	// �X�e�[�g���I���������ۂ�
	virtual bool isEnd() override;
	// ���̃X�e�[�g�̗v�f
	virtual StateElement next() const override;
private:
	// �L�[���͏���
	virtual void key_input();
	// �p�b�h���͏���
	virtual void pad_input();
protected:
	bool holdable_keyR();
	bool holdable_keyL();
	bool holdable_padR();
	bool holdable_padL();
protected:
	// �X�e�[�g�̗v�f
	StateElement element_;
	// �X�e�[�g�̗v�f
	StateElement next_element_;
	// �X�e�[�g���I���������ۂ�
	bool isEnd_;
	// �^�C�}�[
	float timer_;
	// �v���C���[�|�C���^
	Player* player_;
	// �v���C���[�|�C���^
	PlayerBodyPtr butty_;
	// �v���C���[�|�C���^
	PlayerBodyPtr retty_;
	// �v���C���[�|�C���^
	PlayerCntrPtr cntr_;
};