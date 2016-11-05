#pragma once

#include "../../Base/IState.h"
#include "../../../PlayerBody.h"
#include "../../../Player.h"
#include "../../PlayerState_Enum.h"

// �e�v���C���[�X�e�[�g�̊��N���X
class PlayerState_Union : public IState {
public:
	// �R���X�g���N�^
	PlayerState_Union();
	// �S�ẴX�e�[�g�ɋ��ʂ��鏉��������
	virtual void common_init(Actor & actor, ActionType type) override;
	// �X�e�[�g�̕ύX����
	virtual void change(StateElement element) override;
	// �X�e�[�g���I���������ۂ�
	virtual bool isEnd() override;
	// ���̃X�e�[�g�̗v�f
	virtual StateElement next() const override;
protected:
	// �v���C���[�̍��E��r(�E����Ԃ�)
	PlayerBodyPtr compareMax(PlayerBodyPtr p1, PlayerBodyPtr p2);
	// �v���C���[�̍��E��r(������Ԃ�)
	PlayerBodyPtr compareMin(PlayerBodyPtr p1, PlayerBodyPtr p2);
protected:
	// �X�e�[�g�̗v�f
	StateElement element_;
	// �X�e�[�g���I���������ۂ�
	bool isEnd_;
	// �v���C���[�|�C���^
	Player* player_;
	// main�ƂȂ镔��
	PlayerBodyPtr main_body_;
	// sub �ƂȂ镔��
	PlayerBodyPtr sub_body_;
	// �^�C�}�[
	float timer_;
};