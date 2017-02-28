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
	// �X�e�[�g�̒ǉ�
	template <class STATE>
	void add(const STATE id, const IStatePtr& state);
	// �X�e�[�g�̕ύX����
	template <class STATE>
	void change(Actor & actor, const STATE id, const ActionType type = ActionType::None);
private:
	// �R�s�[�֎~
	StateMgr(const StateMgr& other) = delete;
	StateMgr& operator = (const StateMgr& other) = delete;
private:
	// �X�e�[�g�o�^�pmap
	std::unordered_map<int, IStatePtr> states_;
	// ���݂̃X�e�[�g
	IStatePtr currentState_;
	// ���݂̗v�f
	IState::StateElement element_;
};

template<class STATE>
inline void StateMgr::add(const STATE id, const IStatePtr & state){
	states_[static_cast<int>(id)] = state;
}

template<class STATE>
inline void StateMgr::change(Actor & actor, const STATE id, const ActionType type){
	// �O�X�e�[�g�̏I������
	currentState_->end();
	// �v�f�̊i�[
	element_.state_ = static_cast<int>(id);
	element_.type_ = type;
	// ���s�X�e�[�g��ύX
	currentState_ = states_[element_.state_];
	// ���ʂ̏�����
	currentState_->common_init(actor, element_);
	// �ŗL�̏�����
	currentState_->unique_init();
}
