#include "PlayerState_Single.h"

#include "../../../../../../Input/InputMgr.h"

#include "../../../Effect/PlayerEffectObj.h"

// �R���X�g���N�^
PlayerState_Single::PlayerState_Single(const Keys& keys) :
	element_(-1),
	next_element_(-1),
	timer_(0),
	isEnd_(false),
	keys_(keys) {
}

// �S�ẴX�e�[�g�ɋ��ʂ��鏉��������
void PlayerState_Single::common_init(Actor & actor, const StateElement & element){
	element_ = element;
	timer_ = 0;
	isEnd_ = false;

	body_ = dynamic_cast<PlayerBody*>(&actor);
}

void PlayerState_Single::input(float deltaTime){
	InputMgr::GetInstance().isConnectGamePad() ? pad_input(deltaTime) : key_input(deltaTime);
}

void PlayerState_Single::common_update(float deltaTime){

	timer_ += deltaTime;


	body_->collider();
	body_->velocity() = Vector2::One;
}

// �Փˏ���

void PlayerState_Single::collide(const Actor & other) {}

// �`�揈��

void PlayerState_Single::draw() const {}

// �X�e�[�g�̕ύX����
void PlayerState_Single::change(const StateElement& element) {
	next_element_ = element;
	isEnd_ = true;
}

// �X�e�[�g���I���������ۂ�
bool PlayerState_Single::isEnd() {
	return isEnd_;
}

// ���̃X�e�[�g�̗v�f
IState::StateElement PlayerState_Single::next() const {
	return next_element_;
}

bool PlayerState_Single::is_butty() const{
	return keys_.right == KeyCode::RIGHT;
}

bool PlayerState_Single::is_retty()const {
	return keys_.right == KeyCode::D;
}

void PlayerState_Single::key_input(float deltaTime){}

void PlayerState_Single::pad_input(float deltaTime){}

