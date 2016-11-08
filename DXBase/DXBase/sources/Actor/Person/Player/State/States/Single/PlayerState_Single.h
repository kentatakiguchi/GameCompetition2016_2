#pragma once

#include "../../Base/IState.h"
#include "../../../PlayerBody.h"
#include "../../../Player.h"
#include "../../PlayerState_Enum.h"

// �e�v���C���[�X�e�[�g�̊��N���X
class PlayerState_Single : public IState {
public:
	// �R���X�g���N�^
	PlayerState_Single();
	// �S�ẴX�e�[�g�ɋ��ʂ��鏉��������
	virtual void common_init(Actor & actor, ActionType type) override;
	// �X�e�[�g�̕ύX����
	virtual void change(StateElement element) override;
	// �X�e�[�g���I���������ۂ�
	virtual bool isEnd() override;
	// ���̃X�e�[�g�̗v�f
	virtual StateElement next() const override;
protected:
	// �X�e�[�g�̗v�f
	StateElement element_;
	// �X�e�[�g���I���������ۂ�
	bool isEnd_;
	// �v���C���[�|�C���^
	PlayerBody* player_body_;
	// �^�C�}�[
	float timer_;
}; 