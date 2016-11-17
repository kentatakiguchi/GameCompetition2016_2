#include "PlayerState_Attack.h"

#include <algorithm>

PlayerState_Attack::PlayerState_Attack() {}

void PlayerState_Attack::unique_init(Actor & actor){
	main_body_ = player_->getMainBody();
	sub_body_ = player_->getSubBody();

	main_body_->reset_velocity();
	sub_body_->reset_velocity();

	main_body_->reset_opponent();
	sub_body_->reset_opponent();

	dump_ = 0;
	dir_ = Vector2::Normalize(sub_body_->getPosition() - main_body_->getPosition());
	power_ = PLAYER_LAUNCH_POWER;
	dir_easeing_ = 0;
	gra_easeing_ = 0;
	main_body_->launch(dir_ * power_);

	main_body_->create_attack_collider_();
}

void PlayerState_Attack::update(Actor & actor, float deltaTime) {
	timer_ += deltaTime;
	//timer_ = std::min<float>(timer_ + deltaTime, 60);

	dir_easeing_ = EasingOutExpo(timer_ * 0.2f);
	gra_easeing_ = EasingInExpo(timer_ * 0.2f);

	dir_ *= -dir_easeing_ + 1;

	dir_.y += 0.1f * gra_easeing_;
	
	main_body_->launch(dir_ * power_);

	sub_body_->chase();

	main_body_->gravity();
	sub_body_->gravity();

	if (main_body_->is_hit() ||	sub_body_->is_hit()) power_ = 0;

	if (main_body_->is_hit() &&	sub_body_->is_hit()) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
	}

	//key_update();

	pad_update();
}

void PlayerState_Attack::end(){
	main_body_->delete_attack_collider_();

}

void PlayerState_Attack::key_update() {
	if (compare_H() == 0) {

	}
	else if (compare_H() == 1) {
		if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && main_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
		if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && sub_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
	}
	else if (compare_H() == 2) {
		if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && sub_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));

		if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && main_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));

	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && main_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && main_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));

}

void PlayerState_Attack::pad_update() {
	if (compare_H() == 0) {

	}
	else if (compare_H() == 1) {
		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1) && main_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1) && sub_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
	}
	else if (compare_H() == 2) {
		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1) && sub_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));

		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1) && main_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));

	}

	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1) && main_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1) && main_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));

}

int PlayerState_Attack::compare_V(){
	// 同じ
	if (main_body_->getPosition().y == sub_body_->getPosition().y) {
		return 0;
	}
	// メインが↑
	else if (main_body_->getPosition().y > sub_body_->getPosition().y) {
		return 1;
	}
	// メインが↓
	else if (main_body_->getPosition().y < sub_body_->getPosition().y) {
		return 2;
	}
	return -1;
}

int PlayerState_Attack::compare_H(){
	// 同じ
	if (main_body_->getPosition().x == sub_body_->getPosition().x) {
		return 0;
	}
	// メインが→
	else if (main_body_->getPosition().x > sub_body_->getPosition().x) {
		return 1;
	}
	// メインが←
	else if (main_body_->getPosition().x < sub_body_->getPosition().x) {
		return 2;
	}
	return -1;
}






