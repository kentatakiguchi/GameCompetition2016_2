#include "PlayerState_Attack.h"

#include <algorithm>

PlayerState_Attack::PlayerState_Attack() {}

void PlayerState_Attack::unique_init(){
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_SHOT), DX_PLAYTYPE_BACK);

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
	chase_power_ = PLAYER_LAUNCH_POWER * 0.75f;
	launch_dir_easeing_ = 0;
	chase_dir_easeing_ = 0;
	gra_easeing_ = 0;
}

void PlayerState_Attack::update(float deltaTime) {
	timer_ += deltaTime;
	//timer_ = std::min<float>(timer_ + deltaTime, 1);

	launch_dir_easeing_ = -EasingOutExpo(timer_ * 0.7f) + 1;
	chase_dir_easeing_ = EasingSinCurve(std::max<float>(timer_ - 0.1f, 0) * 5);
	gra_easeing_ = EasingInExpo(timer_ * 0.2f);

	launch_dir_.y += 0.1f * gra_easeing_;
	chase_dir_.y  += 0.1f * gra_easeing_;

	if (element_.type_ == ActionType::Right) {
		butty_->launch(launch_dir_ * launch_dir_easeing_ * launch_power_);
		retty_->launch(chase_dir_ * chase_dir_easeing_ * chase_power_);
	}
	if (element_.type_ == ActionType::Left) {
		retty_->launch(launch_dir_ * launch_dir_easeing_ * launch_power_);
		butty_->launch(chase_dir_ * chase_dir_easeing_ * chase_power_);
	}

	butty_->gravity();
	retty_->gravity();

	if (butty_->able_to_hold() && retty_->able_to_hold()) {
		change(PlayerState_Enum_Union::FREEZE);
	}

	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);
}

void PlayerState_Attack::end(){
	if (element_.type_ == ActionType::Right) {
		butty_->delete_attack_collider_();
	}
	if (element_.type_ == ActionType::Left) {
		retty_->delete_attack_collider_();
	}
	butty_->reset_enemy();
	retty_->reset_enemy();
}

void PlayerState_Attack::key_input(){
	if (launch_dir_easeing_ >= 0.15f) {
		butty_->move(InputMgr::GetInstance().KeyVector_R().Horizontal() / 2);
		retty_->move(InputMgr::GetInstance().KeyVector_L().Horizontal() / 2);
	}

	if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) change(PlayerState_Enum_Union::HOLD_AIR, ActionType::Left);
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT)) change(PlayerState_Enum_Union::HOLD_AIR, ActionType::Right);
}

void PlayerState_Attack::pad_input(){
	if (launch_dir_easeing_ >= 0.15f) {
		butty_->move(InputMgr::GetInstance().AnalogPadVectorR().Horizontal() / 2);
		retty_->move(InputMgr::GetInstance().AnalogPadVectorL().Horizontal() / 2);
	}

	if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);

	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1)) change(PlayerState_Enum_Union::HOLD_AIR, ActionType::Left);
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1)) change(PlayerState_Enum_Union::HOLD_AIR, ActionType::Right);
}
