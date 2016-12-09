#include "PlayerState_Hold.h"

PlayerState_Hold::PlayerState_Hold() {}

void PlayerState_Hold::unique_init(){
	if (element_.type_ == ActionType::Right) {
		butty_->animation().change(PlayerAnimID::HOLD);
		retty_->animation().change(PlayerAnimID::SWIM);
	}
	if (element_.type_ == ActionType::Left) {
		retty_->animation().change(PlayerAnimID::HOLD);
		butty_->animation().change(PlayerAnimID::SWIM);
	}
}

void PlayerState_Hold::update(float deltaTime) {
	move();
}

void PlayerState_Hold::end(){}

void PlayerState_Hold::key_input(){
	if (element_.type_ == ActionType::Right) {
		retty_->move(InputMgr::GetInstance().KeyVector(KeyCode::D, KeyCode::A, KeyCode::W, KeyCode::S));
	}
	if (element_.type_ == ActionType::Left) {
		butty_->move(InputMgr::GetInstance().KeyVector());
	}

	if (InputMgr::GetInstance().IsKeyUp(KeyCode::R_SHIFT) && element_.type_ == ActionType::Right) {
		if (retty_->distance() >= PLAYER_MAX_STRETCH_LENGTH * 0.9f)change(StateElement((unsigned int)PlayerState_Enum_Union::ATTACK, ActionType::Right));
		else change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
	}
	if (InputMgr::GetInstance().IsKeyUp(KeyCode::L_SHIFT) && element_.type_ == ActionType::Left) {
		if (butty_->distance() >= PLAYER_MAX_STRETCH_LENGTH * 0.9f)change(StateElement((unsigned int)PlayerState_Enum_Union::ATTACK, ActionType::Left));
		else change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && element_.type_ == ActionType::Left) {
		if (butty_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD_BOTH));
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && element_.type_ == ActionType::Right) {
		if (retty_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD_BOTH));
	}
}

void PlayerState_Hold::pad_input(){
	if (element_.type_ == ActionType::Right) retty_->move(InputMgr::GetInstance().AnalogPadVectorL());
	if (element_.type_ == ActionType::Left)  butty_->move(InputMgr::GetInstance().AnalogPadVectorR());

	if (InputMgr::GetInstance().IsButtonUp(Buttons::BUTTON_R1) && element_.type_ == ActionType::Right) {
		if (retty_->distance() >= PLAYER_MAX_STRETCH_LENGTH * 0.9f)change(StateElement((unsigned int)PlayerState_Enum_Union::ATTACK, ActionType::Right));
		else change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
	}
	if (InputMgr::GetInstance().IsButtonUp(Buttons::BUTTON_L1) && element_.type_ == ActionType::Left) {
		if (butty_->distance() >= PLAYER_MAX_STRETCH_LENGTH * 0.9f)change(StateElement((unsigned int)PlayerState_Enum_Union::ATTACK, ActionType::Left));
		else change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
	}

	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1) && element_.type_ == ActionType::Left) {
		if (butty_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD_BOTH));
	}
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1) && element_.type_ == ActionType::Right) {
		if (retty_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD_BOTH));
	}
}

void PlayerState_Hold::move(){
	if (element_.type_ == ActionType::Left) {
		butty_->hold_gravity();
		butty_->clamp();
	}
	if (element_.type_ == ActionType::Right) {
		retty_->hold_gravity();
		retty_->clamp();
	}
}

