#pragma once

#include "IStatePtr.h"
#include "IState.h"
#include "../../../../Base/Actor.h"
#include <unordered_map>

// �X�e�[�g�̏����Ǘ�
class StateMgr{
public:
	// �R���X�g���N�^
	StateMgr();
	// �R���X�g���N�^
	virtual ~StateMgr();
public:
	// �X�V����
	void action(Actor& actor, float deltaTime) ;
	// �Փˏ���
	void collide(const Actor & other);
	// �`�揈��
	void draw()const;
	// ���݂̃X�e�[�g
	bool currentState(const int& state = 0)const;
	// ���݂̃X�e�[�g
	bool currentActionType(const ActionType& type = ActionType::None);
	// ���݂̏�Ԃ̗v�f
	IState::StateElement currentElement();
protected:
	// �X�e�[�g�̒ǉ�
	void addState(const int& id, const IStatePtr& state);
	// �X�e�[�g�̕ύX����
	void changeState(Actor& actor, const IState::StateElement& element);
private:
	// �R�s�[�֎~
	StateMgr(const StateMgr& other) = delete;
	StateMgr& operator = (const StateMgr& other) = delete;
private:
	// �X�e�[�g�o�^�pmap
	std::unordered_map<unsigned int, IStatePtr> states_;
	// ���݂̃X�e�[�g
	IStatePtr currentState_;
	// ���݂̗v�f
	IState::StateElement element_;
};
