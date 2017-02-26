#pragma once

#include "IState.h"

struct Vector2;

// �e�v���C���[�X�e�[�g�̊��N���X
class State : public IState {
public:
	// �R���X�g���N�^
	State();
protected:
	// �X�e�[�g�̕ύX����
	virtual void request(const StateElement& element) override;
	// �X�e�[�g���I���������ۂ�
	virtual bool isEnd() override;
	// ���̃X�e�[�g�̗v�f
	virtual StateElement next() const override;
protected:
	// �d��
	Vector2 gravity(float deltaTime) const;
	// ����
	float time(float deltaTime) const;
protected:
	// �X�e�[�g�̗v�f
	StateElement element_;
	// �X�e�[�g�̗v�f
	StateElement next_element_;
	// �X�e�[�g���I���������ۂ�
	bool isEnd_;
	// �^�C�}�[
	float timer_;
};