#pragma once

#include "State.h"

class State_Dammy : public State {
public:
	// �R���X�g���N�^
	State_Dammy(){}
	// �S�ẴX�e�[�g�ɋ��ʂ��鏉��������
	virtual void common_init(Actor& actor, const StateElement& element) override {}
	// ���͏���
	virtual void input(float deltaTime) override {}
	// �e��ԓƎ��̏�����
	virtual void unique_init() override{}
	// �X�V����
	virtual void update(float deltaTime) override {}
	// �X�V����
	virtual void common_update(float deltaTime) override {}
	// �Փˏ���
	virtual void collide(const Actor & other) override {}
	// �`�揈��
	virtual void draw()const override{}
	// �I�����̏���
	virtual void end() override {}
};
