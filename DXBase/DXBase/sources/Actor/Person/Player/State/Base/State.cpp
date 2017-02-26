#include "State.h"

#include "../../../../../Math/Math.h"
#include "../../../../../Define.h"

// �R���X�g���N�^
State::State() :
	element_(-1),
	next_element_(-1),
	timer_(0),
	isEnd_(false){}

// �X�e�[�g�̕ύX����
void State::request(const StateElement & element){
	if (element_.state_ == element.state_)return;
	next_element_ = element;
	isEnd_ = true;
}

// �X�e�[�g���I���������ۂ�
bool State::isEnd(){
	return isEnd_;
}

// ���̃X�e�[�g�̗v�f
IState::StateElement State::next() const{
	return next_element_;
}

// �d��
Vector2 State::gravity(float deltaTime) const{
	return 	Vector2::Up * GRAVITY * time(deltaTime);
}

// ����
float State::time(float deltaTime) const{
	return deltaTime * static_cast<float>(GetRefreshRate());
}
