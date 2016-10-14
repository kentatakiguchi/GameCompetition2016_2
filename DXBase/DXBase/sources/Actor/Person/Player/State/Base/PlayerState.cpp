#include "PlayerState.h"


//#include <iostream>

PlayerState::PlayerState() :
	element_(-1),
	isEnd_(false){
}

void PlayerState::common_init(Actor & actor, ActionType type){
	element_ = StateElement(-1, type);
	isEnd_ = false;

	player_ = dynamic_cast<Player*>(&actor);
	main_body_ = player_->getMainBody();
	sub_body_ = player_->getSubBody();

	if (main_body_ != nullptr || sub_body_ != nullptr)return;

	auto body1_ = std::static_pointer_cast<PlayerBody>(actor.findCildren((const std::string)"PlayerBody1"));
	auto body2_ = std::static_pointer_cast<PlayerBody>(actor.findCildren((const std::string)"PlayerBody2"));

	main_body_ = body1_;
	sub_body_ = body2_;

	player_->setBody(main_body_, sub_body_);

	main_body_->target(sub_body_);
	sub_body_->target(main_body_);

	//if (type == ActionType::None) {
	//	main_body_ = body1_;
	//	sub_body_ = body2_;
	//}
	//else if (type == ActionType::Right) {
	//	main_body_ = compareMax(body1_, body2_);
	//	sub_body_  = compareMin(body1_, body2_);
	//}
	//else if (type == ActionType::Left) {
	//	main_body_ = compareMin(body1_, body2_);
	//	sub_body_  = compareMax(body1_, body2_);
	//}
	//main_body_->target(sub_body_);
	//sub_body_->target(main_body_);
}

void PlayerState::change(StateElement element){
	element_ = element;
	isEnd_ = true;
}

bool PlayerState::isEnd(){
	return isEnd_;
}

IState::StateElement PlayerState::next() const{
	return element_;
}

Player::PlayerBodyPtr PlayerState::compareMax(Player::PlayerBodyPtr p1, Player::PlayerBodyPtr p2){
	if (p1->getPosition().x >= p2->getPosition().x) return p1;
	else return p2;
	return nullptr;
}

Player::PlayerBodyPtr PlayerState::compareMin(Player::PlayerBodyPtr p1, Player::PlayerBodyPtr p2){
	if (p1->getPosition().x <= p2->getPosition().x) return p1;
	else return p2;
	return nullptr;
}

