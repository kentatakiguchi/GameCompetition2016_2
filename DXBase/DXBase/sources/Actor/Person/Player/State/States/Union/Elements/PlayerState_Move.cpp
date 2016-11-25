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

	if (InputMgr::GetInstance().KeyVector_R().y <= Vector2::Down.y &&
		InputMgr::GetInstance().KeyVector_L().y <= Vector2::Down.y) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::JUMP));
	}

	if (holdable_keyR()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (holdable_keyL()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

void PlayerState_Move::pad_update(){
	butty_->move(InputMgr::GetInstance().AnalogPadVectorR().Horizontal());
	retty_->move(InputMgr::GetInstance().AnalogPadVectorL().Horizontal());

	if (InputMgr::GetInstance().AnalogPadVectorL().Length() <= 0 &&	InputMgr::GetInstance().AnalogPadVectorR().Length() <= 0) {
		change((unsigned int)PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().AnalogPadVectorR().y <= Vector2::Down.y &&
		InputMgr::GetInstance().AnalogPadVectorL().y <= Vector2::Down.y) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::JUMP));
	}

	if (holdable_padR()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (holdable_padL()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

