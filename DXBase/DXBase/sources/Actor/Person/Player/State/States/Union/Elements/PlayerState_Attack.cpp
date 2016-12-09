#include "PlayerState_Attack.h"

#include <algorithm>

PlayerState_Attack::PlayerState_Attack() {}

void PlayerState_Attack::unique_init(){
	butty_->reset_opponent();
	retty_->reset_opponent();

	if (element_.type_ == ActionType::Right) {
		launch_dir_ = Vector2::Normalize(retty_->getPosition() - butty_->getPosition());
		chase_dir_ = Vector2::Normalize(retty_->getPosition() - butty_->getPosition());

		//butty_->launch(dir_ * power_);
		butty_->create_attack_collider_();
	}
	if (element_.type_ == ActionType::Left) {
		launch_dir_ = Vector2::Normalize(butty_->getPosition() - retty_->getPosition());
		chase_dir_ = Vector2::Normalize(butty_->getPosition() - retty_->getPosition());
		//retty_->launch(dir_ * power_);
		retty_->create_attack_collider_();
	}
	launch_power_ = PLAYER_LAUNCH_POWER;
	chase_power_ = 75.0f;
	launch_dir_easeing_ = 0;
	chase_dir_easeing_ = 0;
	gra_easeing_ = 0;
}

void PlayerState_Attack::update(float deltaTime) {
	//InputMgr::GetInstance().isConnectGamePad() ? pad_update() : key_update();

	timer_ += deltaTime;
	//timer_ = std::min<float>(timer_ + deltaTime, 60);

	launch_dir_easeing_ = EasingOutExpo(timer_ * 0.1f);
	chase_dir_easeing_ = EasingOutExpo(timer_ * 0.1f);
	gra_easeing_ = EasingInExpo(timer_ * 0.2f);

	launch_dir_ *= -launch_dir_easeing_ + 1;
	launch_dir_.y += 0.1f * gra_easeing_;

	chase_dir_ *= -chase_dir_easeing_ + 1;
	chase_dir_.y += 0.1f * gra_easeing_;

	if (element_.type_ == ActionType::Right) {
		butty_->launch(launch_dir_ * launch_power_);
		retty_->launch(chase_dir_ * chase_power_);
		retty_->chase();

		if (butty_->is_hit()) launch_power_ = 0;
		if (retty_->is_hit()) chase_power_ = 0;
	}
	if (element_.type_ == ActionType::Left) {
		retty_->launch(launch_dir_ * launch_power_);
		butty_->launch(chase_dir_ * chase_power_);
		butty_->chase();

		if (butty_->is_hit()) chase_power_ = 0;
		if (retty_->is_hit()) launch_power_ = 0;
	}

	butty_->gravity();
	retty_->gravity();


	if (butty_->able_to_hold() && retty_->able_to_hold()) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::FREEZE));
	}
}

void PlayerState_Attack::end(){
	if (element_.type_ == ActionType::Right) {
		butty_->delete_attack_collider_();
	}
	if (element_.type_ == ActionType::Left) {
		retty_->delete_attack_collider_();
	}
}

void PlayerState_Attack::key_input(){
	if (launch_dir_easeing_ >= 0.15f) {
		butty_->move(InputMgr::GetInstance().KeyVector_R().Horizontal() / 2);
		retty_->move(InputMgr::GetInstance().KeyVector_L().Horizontal() / 2);
	}

	if (holdable_keyR()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (holdable_keyL()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));

}

void PlayerState_Attack::pad_input(){
	if (launch_dir_easeing_ >= 0.15f) {
		butty_->move(InputMgr::GetInstance().AnalogPadVectorR().Horizontal() / 2);
		retty_->move(InputMgr::GetInstance().AnalogPadVectorL().Horizontal() / 2);
	}

	if (holdable_padR()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (holdable_padL()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

//#include "PlayerState_Attack.h"
//
//#include <algorithm>
//
//PlayerState_Attack::PlayerState_Attack() {}
//
//void PlayerState_Attack::unique_init() {
//	butty_->reset_velocity();
//	retty_->reset_velocity();
//
//	dump_ = 0;
//	if (element_.action_type_ == ActionType::Right) {
//		dir_ = Vector2::Normalize(retty_->getPosition() - butty_->getPosition());
//		butty_->launch(dir_ * power_);
//		butty_->create_attack_collider_();
//	}
//	if (element_.action_type_ == ActionType::Left) {
//		dir_ = Vector2::Normalize(butty_->getPosition() - retty_->getPosition());
//		retty_->launch(dir_ * power_);
//		retty_->create_attack_collider_();
//	}
//	power_ = PLAYER_LAUNCH_POWER;
//	dir_easeing_ = 0;
//	gra_easeing_ = 0;
//}
//
//void PlayerState_Attack::update(float deltaTime) {
//	InputMgr::GetInstance().isConnectGamePad() ? pad_update() : key_update();
//
//	timer_ += deltaTime;
//	//timer_ = std::min<float>(timer_ + deltaTime, 60);
//
//	dir_easeing_ = EasingOutExpo(timer_ * 0.01f);
//	gra_easeing_ = EasingInExpo(timer_ * 0.2f);
//
//	dir_ *= -dir_easeing_ + 1;
//
//	dir_.y += 0.1f * gra_easeing_;
//
//	if (element_.action_type_ == ActionType::Right) {
//		butty_->launch(dir_ * power_);
//		retty_->chase();
//	}
//	if (element_.action_type_ == ActionType::Left) {
//		retty_->launch(dir_ * power_);
//		butty_->chase();
//	}
//
//	butty_->gravity();
//	retty_->gravity();
//
//	if (butty_->is_hit() || retty_->is_hit()) power_ = 0;
//
//	if (butty_->is_hit() && retty_->is_hit()) {
//		change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
//	}
//
//}
//
//void PlayerState_Attack::end() {
//	if (element_.action_type_ == ActionType::Right) {
//		butty_->delete_attack_collider_();
//	}
//	if (element_.action_type_ == ActionType::Left) {
//		retty_->delete_attack_collider_();
//	}
//}
//
//void PlayerState_Attack::key_update() {
//	if (dir_easeing_ >= 0.15f) {
//		butty_->move(InputMgr::GetInstance().KeyVector_R().Horizontal() / 2);
//		retty_->move(InputMgr::GetInstance().KeyVector_L().Horizontal() / 2);
//	}
//
//	if (holdable_keyR()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
//	if (holdable_keyL()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
//
//}
//
//void PlayerState_Attack::pad_update() {
//	if (dir_easeing_ >= 0.15f) {
//		butty_->move(InputMgr::GetInstance().AnalogPadVectorR().Horizontal() / 2);
//		retty_->move(InputMgr::GetInstance().AnalogPadVectorL().Horizontal() / 2);
//	}
//
//	if (holdable_padR()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
//	if (holdable_padL()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
//
//}
