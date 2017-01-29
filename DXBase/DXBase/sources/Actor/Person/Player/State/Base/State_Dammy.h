#pragma once

#include "IState.h"

class State_Dammy : public IState {
public:
	// �R���X�g���N�^
	State_Dammy(){}
	// �S�ẴX�e�[�g�ɋ��ʂ��鏉��������
	virtual void common_init(Actor& actor, const ActionType& type) override {}
	// ���͏���
	virtual void input(float deltaTime) override {}
	// �X�e�[�g�̕ύX����
	virtual void change(const StateElement& element) override {}
	// �X�e�[�g���I���������ۂ�
	virtual bool isEnd() override { return false; }
	// ���̃X�e�[�g�̗v�f
	virtual StateElement next() const override { return StateElement(-1); }

	virtual void unique_init() override{}

	virtual void update(float deltaTime) override {}
	
	virtual void common_update(float deltaTime) override {}

	virtual void end() override {}
};
