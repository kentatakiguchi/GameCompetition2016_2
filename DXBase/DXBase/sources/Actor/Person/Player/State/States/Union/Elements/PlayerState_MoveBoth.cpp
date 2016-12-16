#include "PlayerState_MoveBoth.h"

PlayerState_MoveBoth::PlayerState_MoveBoth(){}

void PlayerState_MoveBoth::unique_init(){
	if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);
	
	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);
	
}

void PlayerState_MoveBoth::update(float deltaTime){
	if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);


	butty_->clamp();
	retty_->clamp();
	butty_->gravity();
	retty_->gravity();
}

void PlayerState_MoveBoth::end(){
}

void PlayerState_MoveBoth::key_input(){
	butty_->move(InputMgr::GetInstance().KeyVector_R().Horizontal());
	retty_->move(InputMgr::GetInstance().KeyVector_L().Horizontal());

	if (!move_keyR()) change(PlayerState_Enum_Union::MOVE, ActionType::Left);
	if (!move_keyL()) change(PlayerState_Enum_Union::MOVE, ActionType::Right);

	if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);

}

void PlayerState_MoveBoth::pad_input(){
	butty_->move(InputMgr::GetInstance().AnalogPadVectorR().Horizontal());
	retty_->move(InputMgr::GetInstance().AnalogPadVectorL().Horizontal());

	if (!move_padR()) change(PlayerState_Enum_Union::MOVE, ActionType::Left);
	if (!move_padL()) change(PlayerState_Enum_Union::MOVE, ActionType::Right);

	if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}
