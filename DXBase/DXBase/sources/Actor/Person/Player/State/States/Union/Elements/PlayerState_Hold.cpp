#include "PlayerState_Hold.h"

PlayerState_Hold::PlayerState_Hold(){}

void PlayerState_Hold::unique_init(Actor & actor){

	if (element_.action_type_ == ActionType::None) main_body_ = player_->getMainBody();
	else if (element_.action_type_ == ActionType::Right) main_body_ = compareMax_H(player_->getMainBody(), player_->getSubBody());
	else if (element_.action_type_ == ActionType::Left) main_body_ = compareMin_H(player_->getMainBody(), player_->getSubBody());
	
	sub_body_ = main_body_->get_partner();

	player_->setBody(main_body_, sub_body_);

	if (!main_body_->able_to_hold())change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
}

void PlayerState_Hold::update(Actor & actor, float deltaTime) {

	//key_update();

	pad_update();

	move();
}

void PlayerState_Hold::end(){

}

void PlayerState_Hold::move(){
	sub_body_->hold_gravity();
	sub_body_->circleClamp();
}

void PlayerState_Hold::key_update(){
	Vector2 vector = Vector2::Zero;

	if (element_.action_type_ == ActionType::Right) {
		vector = InputMgr::GetInstance().KeyVector(KeyCode::D, KeyCode::A, KeyCode::W, KeyCode::S);
		sub_body_->move_hold(vector);
	}
	if (element_.action_type_ == ActionType::Left) {
		vector = InputMgr::GetInstance().KeyVector();
		sub_body_->move_hold(vector);
	}

	if (InputMgr::GetInstance().IsKeyUp(KeyCode::R_SHIFT) && element_.action_type_ == ActionType::Right || 
		InputMgr::GetInstance().IsKeyUp(KeyCode::L_SHIFT) && element_.action_type_ == ActionType::Left) {
		if (sub_body_->distance() >= PLAYER_MAX_STRETCH_LENGTH * 0.9f)change(StateElement((unsigned int)PlayerState_Enum_Union::ATTACK));
		else change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && element_.action_type_ == ActionType::Left ||
		InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && element_.action_type_ == ActionType::Right) {
		if(sub_body_->able_to_hold()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD_BOTH));
	}
}

void PlayerState_Hold::pad_update(){
	Vector2 vector = Vector2::Zero;

	if (element_.action_type_ == ActionType::Right) {
		sub_body_->move_hold(InputMgr::GetInstance().AnalogPadVectorL());
	}
	if (element_.action_type_ == ActionType::Left) {
		sub_body_->move_hold(InputMgr::GetInstance().AnalogPadVectorR());
	}

	if (element_.action_type_ == ActionType::Left)sub_body_->move(InputMgr::GetInstance().AnalogPadVectorR());
	if (element_.action_type_ == ActionType::Right)sub_body_->move(InputMgr::GetInstance().AnalogPadVectorL());



	if (InputMgr::GetInstance().IsButtonUp(Buttons::BUTTON_R1) && element_.action_type_ == ActionType::Right ||
		InputMgr::GetInstance().IsButtonUp(Buttons::BUTTON_L1) && element_.action_type_ == ActionType::Left) {
		if (sub_body_->distance() >= PLAYER_MAX_STRETCH_LENGTH * 0.9f)change(StateElement((unsigned int)PlayerState_Enum_Union::ATTACK));
		else change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
	}

	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1) && element_.action_type_ == ActionType::Left ||
		InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1) && element_.action_type_ == ActionType::Right) {
		if (sub_body_->able_to_hold())	change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD_BOTH));
	}
}
