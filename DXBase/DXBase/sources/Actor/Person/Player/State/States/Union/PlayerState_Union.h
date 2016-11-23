#pragma once

#include "../../Base/IState.h"
#include "../../../PlayerBody.h"
#include "../../../Player.h"
#include "../../PlayerState_Enum.h"

#include "../../../PlayerStruct.h"

// �e�v���C���[�X�e�[�g�̊��N���X
class PlayerState_Union : public IState {
public:
	// �R���X�g���N�^
	PlayerState_Union();
	// �S�ẴX�e�[�g�ɋ��ʂ��鏉��������
	virtual void common_init(Actor& actor, ActionType type) override;
	// �X�e�[�g�̕ύX����
	virtual void change(StateElement element) override;
	// �X�e�[�g���I���������ۂ�
	virtual bool isEnd() override;
	// ���̃X�e�[�g�̗v�f
	virtual StateElement next() const override;
//protected:
	//// �v���C���[�̍��E��r(�E����Ԃ�)
	//PlayerBodyPtr compareMax_H(PlayerBodyPtr p1, PlayerBodyPtr p2);
	//// �v���C���[�̍��E��r(������Ԃ�)
	//PlayerBodyPtr compareMin_H(PlayerBodyPtr p1, PlayerBodyPtr p2);
	//// �v���C���[�̏㉺��r(�㑤��Ԃ�)
	//PlayerBodyPtr compareMin_V(PlayerBodyPtr p1, PlayerBodyPtr p2);
	//// �������W
	//bool compare_pos(PlayerBodyPtr p1, PlayerBodyPtr p2);
protected:
	// �X�e�[�g�̗v�f
	StateElement element_;
	// �X�e�[�g���I���������ۂ�
	bool isEnd_;
	// �v���C���[�|�C���^
	Player* player_;
	// �v���C���[�|�C���^
	PlayerBodyPtr butty_;
	// �v���C���[�|�C���^
	PlayerBodyPtr retty_;
	// �v���C���[�|�C���^
	PlayerCntrPtr cntr_;
	// �^�C�}�[
	float timer_;
};