#include "PlayerState_Attack.h"

#include <algorithm>

PlayerState_Attack::PlayerState_Attack(const PlayerPtr& player) : PlayerState_Union(player) {}

void PlayerState_Attack::unique_init(){
	struct_.butty()->reset_velocity();
	struct_.retty()->reset_velocity();

	struct_.butty()->reset_opponent();
	struct_.retty()->reset_opponent();

	dump_ = 0;
	if (element_.action_type_ == ActionType::Right) {
		dir_ = Vector2::Normalize(struct_.retty()->getPosition() - struct_.butty()->getPosition());
		struct_.butty()->launch(dir_ * power_);
		struct_.butty()->create_attack_collider_();
	}
	if (element_.action_type_ == ActionType::Left) {
		dir_ = Vector2::Normalize(struct_.butty()->getPosition() - struct_.retty()->getPosition());
		struct_.retty()->launch(dir_ * power_);
		struct_.retty()->create_attack_collider_();
	}
	power_ = PLAYER_LAUNCH_POWER;
	dir_easeing_ = 0;
	gra_easeing_ = 0;
}

void PlayerState_Attack::update(float deltaTime) {
	timer_ += deltaTime;
	//timer_ = std::min<float>(timer_ + deltaTime, 60);

	dir_easeing_ = EasingOutExpo(timer_ * 0.2f);
	gra_easeing_ = EasingInExpo(timer_ * 0.2f);

	dir_ *= -dir_easeing_ + 1;

	dir_.y += 0.1f * gra_easeing_;
	
	if (element_.action_type_ == ActionType::Right) {
		struct_.butty()->launch(dir_ * power_);
		struct_.retty()->chase();
	}
	if (element_.action_type_ == ActionType::Left) {
		struct_.retty()->launch(dir_ * power_);
		struct_.butty()->chase();
	}

	struct_.butty()->gravity();
	struct_.retty()->gravity();

	if (struct_.butty()->is_hit() || struct_.retty()->is_hit()) power_ = 0;

	if (struct_.butty()->is_hit() && struct_.retty()->is_hit()) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
	}

	InputMgr::GetInstance().isConnectGamePad() ? pad_update() : key_update();
}

void PlayerState_Attack::end(){
	if (element_.action_type_ == ActionType::Right) {
		struct_.butty()->delete_attack_collider_();
	}
	if (element_.action_type_ == ActionType::Left) {
		struct_.retty()->delete_attack_collider_();
	}
}

void PlayerState_Attack::key_update() {
	//if (compare_H() == 0) {

	//}
	//else if (compare_H() == 1) {
	//	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && main_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	//	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && sub_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
	//}
	//else if (compare_H() == 2) {
	//	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && sub_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));

	//	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && main_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));

	//}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && struct_.butty()->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && struct_.retty()->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));

}

void PlayerState_Attack::pad_update() {
	//if (compare_H() == 0) {

	//}
	//else if (compare_H() == 1) {
	//	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1) && main_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	//	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1) && sub_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
	//}
	//else if (compare_H() == 2) {
	//	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1) && sub_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));

	//	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1) && main_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));

	//}

	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1) && struct_.butty()->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1) && struct_.retty()->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));

}

int PlayerState_Attack::compare_V(){
	//// 同じ
	//if (struct_.butty()->getPosition().y == sub_body_->getPosition().y) {
	//	return 0;
	//}
	//// メインが↑
	//else if (main_body_->getPosition().y > sub_body_->getPosition().y) {
	//	return 1;
	//}
	//// メインが↓
	//else if (main_body_->getPosition().y < sub_body_->getPosition().y) {
	//	return 2;
	//}
	return -1;
}

int PlayerState_Attack::compare_H(){
	//// 同じ
	//if (main_body_->getPosition().x == sub_body_->getPosition().x) {
	//	return 0;
	//}
	//// メインが→
	//else if (main_body_->getPosition().x > sub_body_->getPosition().x) {
	//	return 1;
	//}
	//// メインが←
	//else if (main_body_->getPosition().x < sub_body_->getPosition().x) {
	//	return 2;
	//}
	return -1;
}






