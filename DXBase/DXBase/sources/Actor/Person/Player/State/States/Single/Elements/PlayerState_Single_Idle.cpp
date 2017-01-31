#include "PlayerState_Single_Idle.h"

PlayerState_Single_Idle::PlayerState_Single_Idle(const Keys& keys) : PlayerState_Single(keys) {}

void PlayerState_Single_Idle::unique_init(){
	body_->reset_enemy();
	body_->reset_partner();
	body_->animation().change(PlayerAnimID::DIV_IDLE);
}

void PlayerState_Single_Idle::update(float deltaTime){
	body_->count_dead_limit(deltaTime);

	move(deltaTime);
}

void PlayerState_Single_Idle::end(){}

void PlayerState_Single_Idle::key_input(float deltaTime){
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) || InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) {
		body_->position() += body_->get_partner_vector() * 20 * deltaTime * static_cast<float>(GetRefreshRate()); //move(body_->get_partner_vector() * 2);
	}

	if (InputMgr::GetInstance().KeyVector(keys_.right, keys_.left, keys_.up, keys_.down).Length() > 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Single::MOVE));
	}
}

void PlayerState_Single_Idle::pad_input(float deltaTime) {
	if (is_retty())return;
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1) || InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1)) {
		body_->position() += body_->get_partner_vector() * 20 * deltaTime * static_cast<float>(GetRefreshRate()); //move(body_->get_partner_vector() * 2);
	}

	if (InputMgr::GetInstance().AnalogPadVectorR().Length() > 0 && is_butty()) change(StateElement((unsigned int)PlayerState_Enum_Single::MOVE));
	if (InputMgr::GetInstance().AnalogPadVectorL().Length() > 0 && is_retty()) change(StateElement((unsigned int)PlayerState_Enum_Single::MOVE));
}

void PlayerState_Single_Idle::move(float deltaTime){
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());

	body_->position() += gravity;
}

