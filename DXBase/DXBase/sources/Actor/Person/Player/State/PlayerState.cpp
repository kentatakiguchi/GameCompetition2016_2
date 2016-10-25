#include "PlayerState.h"

// �R���X�g���N�^
PlayerState::PlayerState() :
	element_(-1),
	timer_(0),
	isEnd_(false){
}

// �S�ẴX�e�[�g�ɋ��ʂ��鏉��������
void PlayerState::common_init(Actor & actor, ActionType type){
	element_ = StateElement(-1, type);
	timer_ = 0;
	isEnd_ = false;

	player_ = dynamic_cast<Player*>(&actor);
	main_body_ = player_->getMainBody();
	sub_body_ = player_->getSubBody();

	// �����ꂩ��Body��null�łȂ��ꍇreturn
	if (main_body_ != nullptr || sub_body_ != nullptr)return;

	auto body1_ = std::static_pointer_cast<PlayerBody>(actor.findCildren((const std::string)"PlayerBody1"));
	auto body2_ = std::static_pointer_cast<PlayerBody>(actor.findCildren((const std::string)"PlayerBody2"));

	main_body_ = body1_;
	sub_body_ = body2_;

	player_->setBody(main_body_, sub_body_);

	main_body_->target(sub_body_);
	sub_body_->target(main_body_);
}

// �X�e�[�g�̕ύX����
void PlayerState::change(StateElement element){
	element_ = element;
	isEnd_ = true;
}

// �X�e�[�g���I���������ۂ�
bool PlayerState::isEnd(){
	return isEnd_;
}

// ���̃X�e�[�g�̗v�f
IState::StateElement PlayerState::next() const{
	return element_;
}

// �v���C���[�̍��E��r(�E����Ԃ�)
Player::PlayerBodyPtr PlayerState::compareMax(Player::PlayerBodyPtr p1, Player::PlayerBodyPtr p2){
	if (p1->getPosition().x >= p2->getPosition().x) return p1;
	else return p2;
	return nullptr;
}

// �v���C���[�̍��E��r(������Ԃ�)
Player::PlayerBodyPtr PlayerState::compareMin(Player::PlayerBodyPtr p1, Player::PlayerBodyPtr p2){
	if (p1->getPosition().x <= p2->getPosition().x) return p1;
	else return p2;
	return nullptr;
}

