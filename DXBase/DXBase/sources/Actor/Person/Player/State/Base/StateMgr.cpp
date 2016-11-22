#include "StateMgr.h"

#include "State_Dammy.h"

// �R���X�g���N�^
StateMgr::StateMgr() : currentState_(std::make_shared<State_Dammy>()){}

// �X�V����
void StateMgr::action(float deltaTime) {
	// �X�V����
	currentState_->update(deltaTime);
	// �I�����肪true�ɂȂ����ꍇ�X�e�[�g��ύX
	if (currentState_->isEnd()) changeState(currentState_->next());
}

// �X�e�[�g�̕ύX����
void StateMgr::changeState(IState::StateElement element) {
	// �O�X�e�[�g�̏I������
	currentState_->end();
	// ���̃X�e�[�g������
	currentStateName_ = element.state_;
	// ���s�X�e�[�g��ύX
	currentState_ = states_[currentStateName_];
	// ���ʂ̏�����
	currentState_->common_init(element.action_type_);
	// �ŗL�̏�����
	currentState_->unique_init();
}

// �X�e�[�g�̒ǉ�
void StateMgr::add(unsigned int state, const IStatePtr& scene) {
	states_[(unsigned int)state] = scene;
}

// ���݂̃X�e�[�g
bool StateMgr::currentState(unsigned int state) {
	return currentStateName_ == state;
}

