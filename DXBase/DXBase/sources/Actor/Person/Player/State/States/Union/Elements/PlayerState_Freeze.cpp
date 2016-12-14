#include "PlayerState_Freeze.h"

PlayerState_Freeze::PlayerState_Freeze(){}

void PlayerState_Freeze::unique_init(){
	timer_ = 0;
}

void PlayerState_Freeze::update(float deltaTime){
	timer_ += deltaTime;

	//butty_->clamp();
	//retty_->clamp();

	if (timer_ >= PLAYER_FREEZE_TIME) change(PlayerState_Enum_Union::IDLE);
}

void PlayerState_Freeze::end(){}

void PlayerState_Freeze::key_input(){
	butty_->move(InputMgr::GetInstance().KeyVector_R().Horizontal());
	retty_->move(InputMgr::GetInstance().KeyVector_L().Horizontal());

	if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

void PlayerState_Freeze::pad_input(){
	butty_->move(InputMgr::GetInstance().AnalogPadVectorR().Horizontal());
	retty_->move(InputMgr::GetInstance().AnalogPadVectorL().Horizontal());

	if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

