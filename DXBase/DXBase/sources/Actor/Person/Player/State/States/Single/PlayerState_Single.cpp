#include "PlayerState_Single.h"

// �R���X�g���N�^
PlayerState_Single::PlayerState_Single() :
	element_(-1),
	next_element_(-1),
	timer_(0),
	isEnd_(false) {
}

// �S�ẴX�e�[�g�ɋ��ʂ��鏉��������
void PlayerState_Single::common_init(Actor& actor, ActionType type) {
	element_ = StateElement(-1, type);
	timer_ = 0;
	isEnd_ = false;

	//player_body_ = std::dynamic_pointer_cast<PlayerBody>(actor);
	player_body_ = dynamic_cast<PlayerBody*>(&actor);
}

void PlayerState_Single::input(){
	InputMgr::GetInstance().isConnectGamePad() ? pad_input() : key_input();
}

// �X�e�[�g�̕ύX����
void PlayerState_Single::change(StateElement element) {
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

void PlayerState_Single::key_input(){}

void PlayerState_Single::pad_input(){}

