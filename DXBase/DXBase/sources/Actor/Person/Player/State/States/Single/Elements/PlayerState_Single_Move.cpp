#include "PlayerState_Single_Move.h"

PlayerState_Single_Move::PlayerState_Single_Move(const Keys& keys) : PlayerState_Single(keys) {
}

void PlayerState_Single_Move::unique_init(){}

void PlayerState_Single_Move::update(float deltaTime){
	body_->count_dead_limit(deltaTime);
}

void PlayerState_Single_Move::end(){
	//butty_->init_state();
	//retty_->init_state();
	//butty_->reset_enemy();
	//retty_->reset_enemy();
	//retty_->reset_dead_limit();
	//butty_->reset_dead_limit();
	//butty_->reset_partner();
	//retty_->reset_partner();
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
