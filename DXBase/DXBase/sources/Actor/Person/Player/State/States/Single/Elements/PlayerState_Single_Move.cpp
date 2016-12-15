#include "PlayerState_Single_Move.h"

PlayerState_Single_Move::PlayerState_Single_Move(const Keys& keys) : PlayerState_Single(keys) {
}

void PlayerState_Single_Move::unique_init(){
	body_->animation().change(PlayerAnimID::DIV_MOVE);
}

void PlayerState_Single_Move::update(float deltaTime){
	if (InputMgr::GetInstance().AnalogPadVectorR().x > 0 && is_butty()) body_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorR().x < 0 && is_butty()) body_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);
	if (InputMgr::GetInstance().AnalogPadVectorL().x > 0 && is_retty()) body_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Right);
	if (InputMgr::GetInstance().AnalogPadVectorL().x < 0 && is_retty()) body_->animation().change_dir(PlayerAnimID::SWIM_TURN, ActionType::Left);

	body_->count_dead_limit(deltaTime);
	body_->gravity();
}

void PlayerState_Single_Move::end(){
	//body_->init_state();
	//body_->reset_enemy();
	//body_->reset_dead_limit();
	//body_->reset_partner();
}

void PlayerState_Single_Move::key_input(){
	body_->move(InputMgr::GetInstance().KeyVector(keys_.right, keys_.left, keys_.up, keys_.down).Horizontal());

	if (InputMgr::GetInstance().IsKeyDown(keys_.up))change(StateElement((unsigned int)PlayerState_Enum_Single::JUMP));
}

void PlayerState_Single_Move::pad_input(){
	Vector2 vector = Vector2::Zero;
	if (is_butty())vector = InputMgr::GetInstance().AnalogPadVectorR();
	if (is_retty())vector = InputMgr::GetInstance().AnalogPadVectorL();
	body_->move(vector.Horizontal());

	if (InputMgr::GetInstance().AnalogPadVectorR().y <= -1 && is_butty()) change(StateElement((unsigned int)PlayerState_Enum_Single::JUMP));
	if (InputMgr::GetInstance().AnalogPadVectorL().y <= -1 && is_retty()) change(StateElement((unsigned int)PlayerState_Enum_Single::JUMP));
}
