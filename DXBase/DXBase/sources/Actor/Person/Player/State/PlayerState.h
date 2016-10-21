#pragma once

#include "Base/IState.h"
#include "../PlayerBody.h"
#include "../Player.h"

// �e�v���C���[�X�e�[�g�̊��N���X
class PlayerState : public IState {
public:
	// �R���X�g���N�^
	PlayerState();
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
	Player::PlayerBodyPtr compareMax(Player::PlayerBodyPtr p1, Player::PlayerBodyPtr p2);
	// �v���C���[�̍��E��r(������Ԃ�)
	Player::PlayerBodyPtr compareMin(Player::PlayerBodyPtr p1, Player::PlayerBodyPtr p2);
protected:
	// �X�e�[�g�̗v�f
	StateElement element_;
	// �X�e�[�g���I���������ۂ�
	bool isEnd_;
	// �v���C���[�|�C���^
	Player* player_;
	// main�ƂȂ镔��
	Player::PlayerBodyPtr main_body_;
	// sub �ƂȂ镔��
	Player::PlayerBodyPtr sub_body_;
};