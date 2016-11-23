#include "PlayerState_Move.h"

PlayerState_Move::PlayerState_Move(){}

void PlayerState_Move::unique_init(){
}

void PlayerState_Move::update(float deltaTime){
	InputMgr::GetInstance().isConnectGamePad() ? pad_update() : key_update();

	move(deltaTime);
}

void PlayerState_Move::end(){ }

void PlayerState_Move::move(float deltaTime) {
	player_->body_chase();
	player_->body_gravity();
}

void PlayerState_Move::key_update(){
	butty_->move(InputMgr::GetInstance().KeyVector_R().Horizontal());
	retty_->move(InputMgr::GetInstance().KeyVector_L().Horizontal());

	if (InputMgr::GetInstance().KeyVector_L().Length() <= 0 && InputMgr::GetInstance().KeyVector_R().Length() <= 0) {
		change((unsigned int)PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

void PlayerState_Move::pad_update(){
	butty_->move(InputMgr::GetInstance().AnalogPadVectorL().Horizontal());
	retty_->move(InputMgr::GetInstance().AnalogPadVectorR().Horizontal());

	if (InputMgr::GetInstance().AnalogPadVectorL().Length() <= 0 &&	InputMgr::GetInstance().AnalogPadVectorR().Length() <= 0) {
		change((unsigned int)PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

