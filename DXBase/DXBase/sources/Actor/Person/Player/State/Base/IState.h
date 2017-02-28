#pragma once

#include "ActionType.h"

class Actor;

class IState {
public:
	// �X�e�[�g�̗v�f
	struct StateElement {
		// �X�e�[�g
		int state_;
		// �^�C�v
		ActionType type_;
		// �R���X�g���N�^
		StateElement(const int& state, const ActionType& type = ActionType::None) : state_(state), type_(type){}
	};
public:
	// ���z�f�X�g���N�^
	virtual ~IState() {}
	// �S��ԋ��ʂ̏�����
	virtual void common_init(Actor& actor, const StateElement& element = StateElement({ -1, ActionType::None })) = 0;
	// �e��ԓƎ��̏�����
	virtual void unique_init() = 0;
	// ���͏���
	virtual void input(float deltaTime) = 0;
	// �X�V����
	virtual void update(float deltaTime) = 0;
	// �X�V����
	virtual void common_update(float deltaTime) = 0;
	// �Փˏ���
	virtual void collide(const Actor& other) = 0;
	// �`�揈��
	virtual void draw()const = 0;
	// �I�����̏���
	virtual void end() = 0;
	// �I����Ԃ�
	virtual bool isEnd() = 0;
	// ��Ԃ̕ύX
	virtual void request(const StateElement& element) = 0;
	// ���̃X�e�[�g�̗v�f
	virtual StateElement next() const = 0;
};
