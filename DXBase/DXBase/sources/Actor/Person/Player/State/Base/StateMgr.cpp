#include "StateMgr.h"

#include "State_Dammy.h"

// �R���X�g���N�^
StateMgr::StateMgr() : currentState_(std::make_shared<State_Dammy>()), element_(-1){}

StateMgr::~StateMgr()
{
}

// �X�V����
void StateMgr::action(Actor& actor, float deltaTime) {
	// ���͏���
	currentState_->input(deltaTime);
	// �X�V����
	currentState_->update(deltaTime);
	// �X�V����
	currentState_->common_update(deltaTime);
	// �I�����肪true�ɂȂ����ꍇ�X�e�[�g��ύX
	if (currentState_->isEnd()) changeState(actor, currentState_->next());
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

// �X�e�[�g�̒ǉ�
void StateMgr::addState(const int& state, const IStatePtr& scene) {
	states_[(unsigned int)state] = scene;
}

// �X�e�[�g�̕ύX����
void StateMgr::changeState(Actor& actor, const IState::StateElement& element) {
	// �O�X�e�[�g�̏I������
	currentState_->end();
	// �v�f�̊i�[
	element_ = element;
	// ���s�X�e�[�g��ύX
	currentState_ = states_[element_.state_];
	// ���ʂ̏�����
	currentState_->common_init(actor, element_.type_);
	// �ŗL�̏�����
	currentState_->unique_init();
}

// ���݂̃X�e�[�g
bool StateMgr::currentState(const int& state) const {
	return element_.state_ == state;
}

bool StateMgr::currentActionType(const ActionType& type){
	return element_.type_ == type;
}

IState::StateElement StateMgr::currentElement(){
	return element_;
}

