#include "PlayerState_Union.h"

// �R���X�g���N�^
PlayerState_Union::PlayerState_Union(const PlayerPtr& player) : 
	player_(player),
	struct_(player->getStruct()),
	element_(-1),
	timer_(0),
	isEnd_(false){
}

// �S�ẴX�e�[�g�ɋ��ʂ��鏉��������
void PlayerState_Union::common_init(ActionType type){
	element_ = StateElement(-1, type);
	timer_ = 0;
	isEnd_ = false;

	//auto player = std::dynamic_pointer_cast<Player>(actor);
	//struct_ = ;


	//main_body_ = player_->getMainBody();
	//sub_body_ = player_->getSubBody();

	// �����ꂩ��Body��null�łȂ��ꍇreturn
	//if (main_body_ != nullptr || sub_body_ != nullptr)return;

	//auto body1_ = std::static_pointer_cast<PlayerBody>(actor.findCildren((const std::string)"PlayerBody1"));
	//auto body2_ = std::static_pointer_cast<PlayerBody>(actor.findCildren((const std::string)"PlayerBody2"));

	//main_body_ = body1_;
	//sub_body_ = body2_;

	//player_->setBody(main_body_, sub_body_);

	//main_body_->set_partner(sub_body_);
	//sub_body_->set_partner(main_body_);
}

// �X�e�[�g�̕ύX����
void PlayerState_Union::change(StateElement element){
	element_ = element;
	isEnd_ = true;
}

// �X�e�[�g���I���������ۂ�
bool PlayerState_Union::isEnd(){
	return isEnd_;
}

// ���̃X�e�[�g�̗v�f
IState::StateElement PlayerState_Union::next() const{
	return element_;
}

//// �v���C���[�̍��E��r(�E����Ԃ�)
//PlayerBodyPtr PlayerState_Union::compareMax_H(PlayerBodyPtr p1, PlayerBodyPtr p2){
//	if (p1->getPosition().x > p2->getPosition().x) return p1;
//	else if (p1->getPosition().x < p2->getPosition().x) return p2;
//	else return compareMin_V(p1, p2);
//	return nullptr;
//}
//
//// �v���C���[�̍��E��r(������Ԃ�)
//PlayerBodyPtr PlayerState_Union::compareMin_H(PlayerBodyPtr p1, PlayerBodyPtr p2){
//	if (p1->getPosition().x < p2->getPosition().x) return p1;
//	else if (p1->getPosition().x > p2->getPosition().x) return p2;
//	else return compareMin_V(p1, p2);
//	return nullptr;
//}
//
//PlayerBodyPtr PlayerState_Union::compareMin_V(PlayerBodyPtr p1, PlayerBodyPtr p2){
//	if (p1->getPosition().y >= p2->getPosition().y) return p1;
//	else return p2;
//	return nullptr;
//}


