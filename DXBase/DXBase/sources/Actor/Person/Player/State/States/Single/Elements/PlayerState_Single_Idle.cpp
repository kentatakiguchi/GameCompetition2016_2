#include "PlayerState_Single_Idle.h"

PlayerState_Single_Idle::PlayerState_Single_Idle(const Keys& keys) : PlayerState_Single(keys) {}

void PlayerState_Single_Idle::unique_init(){
	body_->reset_enemy();
	body_->reset_partner();
	body_->animation().change(PlayerAnimID::DIV_IDLE);
}

void PlayerState_Single_Idle::update(float deltaTime){
	body_->count_dead_limit(deltaTime);

	move();
}

void PlayerState_Single_Idle::end(){}

void PlayerState_Single_Idle::key_input(){
	if (InputMgr::GetInstance().KeyVector(keys_.right, keys_.left, keys_.up, keys_.down).Length() > 0) {
		change(StateElement((unsigned int)PlayerState_Enum_Single::MOVE));
	}
	if (InputMgr::GetInstance().IsKeyDown(keys_.up))change(StateElement((unsigned int)PlayerState_Enum_Single::JUMP));
}

void PlayerState_Single_Idle::pad_input() {
	if (InputMgr::GetInstance().AnalogPadVectorR().Length() > 0 && is_butty()) change(StateElement((unsigned int)PlayerState_Enum_Single::MOVE));
	if (InputMgr::GetInstance().AnalogPadVectorL().Length() > 0 && is_retty()) change(StateElement((unsigned int)PlayerState_Enum_Single::MOVE));
	if (InputMgr::GetInstance().AnalogPadVectorR().y <= -1 && is_butty()) change(StateElement((unsigned int)PlayerState_Enum_Single::JUMP));
	if (InputMgr::GetInstance().AnalogPadVectorL().y <= -1 && is_retty()) change(StateElement((unsigned int)PlayerState_Enum_Single::JUMP));
}

void PlayerState_Single_Idle::move(){
	body_->gravity();
}

