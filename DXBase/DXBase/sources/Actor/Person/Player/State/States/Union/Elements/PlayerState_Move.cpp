#include "PlayerState_Move.h"

PlayerState_Move::PlayerState_Move(){}

void PlayerState_Move::unique_init(){
	butty_->animation().change(PlayerAnimID::MOVE, 2.0f);
	retty_->animation().change(PlayerAnimID::MOVE, 2.0f);

	//if (element_.type_ == ActionType::Right) {
	//	if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(ActionType::Right);
	//	if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(ActionType::Left);
	//}
	//if (element_.type_ == ActionType::Left) {
	//	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(ActionType::Right);
	//	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(ActionType::Left);
	//}

	if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

}

void PlayerState_Move::update(float deltaTime){
	//if (element_.type_ == ActionType::Right) {
	//	if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(ActionType::Right);
	//	if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(ActionType::Left);
	//}
	//if (element_.type_ == ActionType::Left) {
	//	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(ActionType::Right);
	//	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(ActionType::Left);
	//}

	if (InputMgr::GetInstance().AnalogPadVectorR().x > 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorR().x < 0) butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0) retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);

	if (element_.type_ == ActionType::Right) {
		if (butty_->getPosition().x > retty_->getPosition().x) {
			retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
		}
		else {
			retty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);
		}
	}
	if (element_.type_ == ActionType::Left) {
		if (butty_->getPosition().x > retty_->getPosition().x) {
			butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Left);
		}
		else {
			butty_->animation().change_dir(PlayerAnimID::TURN, ActionType::Right);
		}
	}
	move(deltaTime);

	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);
}

void PlayerState_Move::end(){ }

void PlayerState_Move::key_input(){
	if (element_.type_ == ActionType::Right) butty_->move(InputMgr::GetInstance().KeyVector_R().Horizontal());
	if (element_.type_ == ActionType::Left)  retty_->move(InputMgr::GetInstance().KeyVector_L().Horizontal());

	if (!move_keyR() && !move_keyL()) change(PlayerState_Enum_Union::IDLE);
	else if (jump_key()) change(PlayerState_Enum_Union::JUMP);
	else if (element_.type_ == ActionType::Right && move_keyL())	change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (element_.type_ == ActionType::Left  && move_keyR()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_keyR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_keyL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

void PlayerState_Move::pad_input(){
	if (element_.type_ == ActionType::Right) butty_->move(InputMgr::GetInstance().AnalogPadVectorR().Horizontal());
	if (element_.type_ == ActionType::Left)  retty_->move(InputMgr::GetInstance().AnalogPadVectorL().Horizontal());
	
	if (!move_padR() && !move_padL()) change(PlayerState_Enum_Union::IDLE);
	else if (jump_pad()) change(PlayerState_Enum_Union::JUMP);
	else if (element_.type_ == ActionType::Right && move_padL()) change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (element_.type_ == ActionType::Left  && move_padR())	change(PlayerState_Enum_Union::MOVE_BOTH);
	else if (holdable_padR()) change(PlayerState_Enum_Union::HOLD, ActionType::Right);
	else if (holdable_padL()) change(PlayerState_Enum_Union::HOLD, ActionType::Left);
}

void PlayerState_Move::move(float deltaTime) {
	if (element_.type_ == ActionType::Right) retty_->chase();
	if (element_.type_ == ActionType::Left)  butty_->chase();

	butty_->clamp();
	retty_->clamp();

	butty_->gravity();
	retty_->gravity();
}

