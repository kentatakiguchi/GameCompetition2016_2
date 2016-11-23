#pragma once

#include "IState.h"

class State_Dammy : public IState {
public:
	State_Dammy(){}

	// �S�ẴX�e�[�g�ɋ��ʂ��鏉��������
	virtual void common_init(Actor& actor, ActionType type) override {}
	// �X�e�[�g�̕ύX����
	virtual void change(StateElement element) override {}
	// �X�e�[�g���I���������ۂ�
	virtual bool isEnd() override { return false; }
	// ���̃X�e�[�g�̗v�f
	virtual StateElement next() const override { return StateElement(-1); }

	virtual void unique_init() override{}

	virtual void update(float deltaTime) override{}

	virtual void end() override{}
};
