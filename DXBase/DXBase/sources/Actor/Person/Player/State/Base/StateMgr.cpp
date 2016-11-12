#include "StateMgr.h"

// �R���X�g���N�^
StateMgr::StateMgr() {}

// �X�V����
void StateMgr::action(Actor & actor, float deltaTime) {
	// �X�V����
	currentState_->update(actor, deltaTime);
	currentState_->end();
	// �I�����肪true�ɂȂ����ꍇ�X�e�[�g��ύX
	if (currentState_->isEnd()) changeState(actor, currentState_->next());
}

// �X�e�[�g�̕ύX����
void StateMgr::changeState(Actor & actor, IState::StateElement element) {
	// ���̃X�e�[�g������
	currentStateName_ = element.state_;
	// ���s�X�e�[�g��ύX
	currentState_ = states_[currentStateName_];
	// ���ʂ̏�����
	currentState_->common_init(actor, element.action_type_);
	// �ŗL�̏�����
	currentState_->unique_init(actor);
}

// �X�e�[�g�̒ǉ�
void StateMgr::add(unsigned int state, const IStatePtr& scene) {
	states_[(unsigned int)state] = scene;
}

// ���݂̃X�e�[�g
bool StateMgr::currentState(unsigned int state) {
	return currentStateName_ == state;
}

