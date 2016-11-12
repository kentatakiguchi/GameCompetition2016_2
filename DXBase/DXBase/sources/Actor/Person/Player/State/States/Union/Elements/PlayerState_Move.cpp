#include "PlayerState_Move.h"

PlayerState_Move::PlayerState_Move(){}

void PlayerState_Move::unique_init(Actor & actor){
}

void PlayerState_Move::update(Actor & actor, float deltaTime){
	move(actor, deltaTime);
	key_update();
	//pad_update();	
}

void PlayerState_Move::end(){ }

void PlayerState_Move::move(Actor & actor, float deltaTime) {
	main_body_->chase();
	sub_body_->chase();
	main_body_->gravity();
	sub_body_->gravity();
}

void PlayerState_Move::key_update(){
	main_body_->move(InputMgr::GetInstance().KeyVector_R().Horizontal());
	sub_body_->move(InputMgr::GetInstance().KeyVector_L().Horizontal());

	if (InputMgr::GetInstance().KeyVector_L().Length() <= 0 && InputMgr::GetInstance().KeyVector_R().Length() <= 0) {
		change((unsigned int)PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

void PlayerState_Move::pad_update(){
	main_body_->move(InputMgr::GetInstance().AnalogPadVectorL());
	sub_body_->move(InputMgr::GetInstance().AnalogPadVectorR());

	if (InputMgr::GetInstance().AnalogPadVectorL().Length() <= 0 &&	InputMgr::GetInstance().AnalogPadVectorR().Length() <= 0) {
		change((unsigned int)PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R2)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L2)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

