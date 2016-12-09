#include "PlayerState_MoveBoth.h"

PlayerState_MoveBoth::PlayerState_MoveBoth()
{
}

void PlayerState_MoveBoth::unique_init()
{
}

void PlayerState_MoveBoth::update(float deltaTime){
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

	if (InputMgr::GetInstance().KeyVector_R().Length() <= 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE, ActionType::Left));
	}
	if (InputMgr::GetInstance().KeyVector_L().Length() <= 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE, ActionType::Right));
	}
}

void PlayerState_MoveBoth::pad_input(){
	butty_->move(InputMgr::GetInstance().AnalogPadVectorR().Horizontal());
	retty_->move(InputMgr::GetInstance().AnalogPadVectorL().Horizontal());

	if (InputMgr::GetInstance().AnalogPadVectorR().Length() <= 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE, ActionType::Left));
	}
	if (InputMgr::GetInstance().AnalogPadVectorL().Length() <= 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE, ActionType::Right));
	}
}
