#include "PlayerState_Freeze.h"

PlayerState_Freeze::PlayerState_Freeze(){}

void PlayerState_Freeze::unique_init(){
	timer_ = 0;
}

void PlayerState_Freeze::update(float deltaTime){
	//InputMgr::GetInstance().isConnectGamePad() ? pad_update() : key_update();
	timer_ += deltaTime;

	if (timer_ >= PLAYER_FREEZE_TIME) change(StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
}

void PlayerState_Freeze::end(){
}

void PlayerState_Freeze::key_input(){
	butty_->move(InputMgr::GetInstance().KeyVector_R().Horizontal());
	retty_->move(InputMgr::GetInstance().KeyVector_L().Horizontal());

	if (holdable_keyR()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (holdable_keyL()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

void PlayerState_Freeze::pad_input(){
	butty_->move(InputMgr::GetInstance().AnalogPadVectorR().Horizontal());
	retty_->move(InputMgr::GetInstance().AnalogPadVectorL().Horizontal());

	if (holdable_padR()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (holdable_padL()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

