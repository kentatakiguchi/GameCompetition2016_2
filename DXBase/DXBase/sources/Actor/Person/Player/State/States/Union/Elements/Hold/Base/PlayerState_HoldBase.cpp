#include "PlayerState_HoldBase.h"

PlayerState_HoldBase::PlayerState_HoldBase(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_Union(butty, retty) {}

void PlayerState_HoldBase::unique_init(){
	onInit();
}

void PlayerState_HoldBase::update(float deltaTime){
	onUpdate(deltaTime);

	move(deltaTime);
}

void PlayerState_HoldBase::end(){
	onEnd();
}

void PlayerState_HoldBase::key_input(float deltaTime){
	if (element_.type_ == ActionType::Right) retty_->position() += InputMgr::GetInstance().KeyVector(KeyCode::D, KeyCode::A, KeyCode::W, KeyCode::S) * 7.5f * speed_r(deltaTime);
	if (element_.type_ == ActionType::Left)  butty_->position() += InputMgr::GetInstance().KeyVector() * 7.5f * speed_b(deltaTime);

	if (element_.type_ == ActionType::Right) {
		if (InputMgr::GetInstance().KeyVector_L().x > 0) retty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
		if (InputMgr::GetInstance().KeyVector_L().x < 0) retty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);
	}
	if (element_.type_ == ActionType::Left) {
		if (InputMgr::GetInstance().KeyVector_R().x > 0) butty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
		if (InputMgr::GetInstance().KeyVector_R().x < 0) butty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);
	}

	if (InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && element_.type_ == ActionType::Left) {
		if (butty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH);
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && element_.type_ == ActionType::Right) {
		if (retty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH);
	}

	onKeyInput(deltaTime);
}

void PlayerState_HoldBase::pad_input(float deltaTime){
	if (element_.type_ == ActionType::Right) retty_->position() += InputMgr::GetInstance().AnalogPadVectorL() * 7.5f * speed_r(deltaTime);
	if (element_.type_ == ActionType::Left)  butty_->position() += InputMgr::GetInstance().AnalogPadVectorR() * 7.5f * speed_b(deltaTime);;

	if (element_.type_ == ActionType::Right) {
		if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
		if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);
	}
	if (element_.type_ == ActionType::Left) {
		if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
		if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);
	}

	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && element_.type_ == ActionType::Left) {
		if (butty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH);
	}
	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && element_.type_ == ActionType::Right) {
		if (retty_->able_to_hold()) change(PlayerState_Enum_Union::HOLD_BOTH);
	}

	onPadInput(deltaTime);
}

void PlayerState_HoldBase::move(float deltaTime) {
	
	onMove(deltaTime);

	//Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());
	//if (element_.type_ == ActionType::Left) {
	//	if (InputMgr::GetInstance().AnalogPadVectorR().Length() > 0) {
	//		gravity = Vector2::Zero;
	//	}
	//	butty_->position() += gravity * butty_->velocity();
	//}
	//if (element_.type_ == ActionType::Right) {
	//	if (InputMgr::GetInstance().AnalogPadVectorL().Length() > 0) {
	//		gravity = Vector2::Zero;
	//	}
	//	retty_->position() += gravity * retty_->velocity();
	//}

	if (element_.type_ == ActionType::Left) {
		butty_->position() = clamp(butty_->position(), 0);
	}
	if (element_.type_ == ActionType::Right) {
		retty_->position() = clamp(retty_->position(), PLAYER_CNTR_DIV_NUM - 1);
	}

	retty_->reset_slope();
	butty_->reset_slope();
}

void PlayerState_HoldBase::onInit(){}

void PlayerState_HoldBase::onUpdate(float deltaTime){}

void PlayerState_HoldBase::onEnd(){}

void PlayerState_HoldBase::onKeyInput(float deltaTime){}

void PlayerState_HoldBase::onPadInput(float deltaTime){}

void PlayerState_HoldBase::onMove(float deltaTime){}

