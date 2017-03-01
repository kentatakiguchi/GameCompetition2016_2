#include "StateMgr.h"

#include "State_Dammy.h"

#include "../../../../../World/IWorld.h"

// �R���X�g���N�^
StateMgr::StateMgr() : currentState_(std::make_shared<State_Dammy>()), element_(-1){}

StateMgr::~StateMgr(){}

// �X�V����
void StateMgr::action(Actor& actor, float deltaTime) {
	// ���͏���
	if(!actor.getWorld()->GetPlayerNotMove()) currentState_->input(deltaTime);
	// �X�V����
	currentState_->update(deltaTime);
	// �X�V����
	currentState_->common_update(deltaTime);
	// �I�����肪true�ɂȂ����ꍇ�X�e�[�g��ύX
	if (currentState_->isEnd()) change(actor, currentState_->next().state_, currentState_->next().type_);
}

// �Փˏ���
void StateMgr::collide(const Actor & other){
	// �Փˏ���
	currentState_->collide(other);
}

// �`�揈��
void StateMgr::draw() const{
	// �`�揈��
	currentState_->draw();
}

// ���݂̃X�e�[�g
bool StateMgr::currentState(const int& state) const {
	return element_.state_ == state;
}

bool StateMgr::currentActionType(const ActionType& type){
	return element_.type_ == type;
}


