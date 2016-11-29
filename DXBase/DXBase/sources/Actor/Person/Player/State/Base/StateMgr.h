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
public:
	// �X�V����
	void action(Actor& actor, float deltaTime) ;
	// �X�e�[�g�̕ύX����
	void changeState(Actor& actor, IState::StateElement element);
	// �X�e�[�g�̒ǉ�
	void add(unsigned int state, const IStatePtr& scene);
	// ���݂̃X�e�[�g
	bool currentState(unsigned int state = 0);
	// ���݂̃X�e�[�g
	bool currentActionType(ActionType action_type = ActionType::None);
	// ���݂̏�Ԃ̗v�f
	IState::StateElement currentElement();
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
