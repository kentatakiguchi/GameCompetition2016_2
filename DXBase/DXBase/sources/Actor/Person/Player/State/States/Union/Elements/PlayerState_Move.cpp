#include "PlayerState_Move.h"

PlayerState_Move::PlayerState_Move(){}

void PlayerState_Move::unique_init(){
}

void PlayerState_Move::update(float deltaTime){
	move(deltaTime);
}

void PlayerState_Move::end(){ }

void PlayerState_Move::key_input(){
	if (element_.type_ == ActionType::Right) butty_->move(InputMgr::GetInstance().KeyVector_R().Horizontal());
	if (element_.type_ == ActionType::Left)  retty_->move(InputMgr::GetInstance().KeyVector_L().Horizontal());

	if (element_.type_ == ActionType::Left  && InputMgr::GetInstance().KeyVector_R().Length() > 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE_BOTH));
	}
	if (element_.type_ == ActionType::Right && InputMgr::GetInstance().KeyVector_L().Length() > 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE_BOTH));
	}

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

void PlayerState_Move::pad_input(){
	if (element_.type_ == ActionType::Right) butty_->move(InputMgr::GetInstance().AnalogPadVectorR().Horizontal());
	if (element_.type_ == ActionType::Left)  retty_->move(InputMgr::GetInstance().AnalogPadVectorL().Horizontal());

	if (element_.type_ == ActionType::Left  && InputMgr::GetInstance().AnalogPadVectorR().Length() > 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE_BOTH));
	}
	if (element_.type_ == ActionType::Right && InputMgr::GetInstance().AnalogPadVectorL().Length() > 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE_BOTH));
	}

	if (InputMgr::GetInstance().AnalogPadVectorL().Length() <= 0 && InputMgr::GetInstance().AnalogPadVectorR().Length() <= 0) {
		change((unsigned int)PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().AnalogPadVectorR().y <= Vector2::Down.y &&
		InputMgr::GetInstance().AnalogPadVectorL().y <= Vector2::Down.y) {
		change(StateElement((unsigned int)PlayerState_Enum_Union::JUMP));
	}

	if (holdable_padR()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (holdable_padL()) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));

}

void PlayerState_Move::move(float deltaTime) {
	if (element_.type_ == ActionType::Right) {
		retty_->chase();
		retty_->clamp();
		//butty_->clamp();

	}
	if (element_.type_ == ActionType::Left) {
		butty_->chase();
		butty_->clamp();
		//retty_->clamp();
	}
	butty_->gravity();
	retty_->gravity();
}

