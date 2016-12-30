#include "PlayerState_EventTime.h"

PlayerState_EventTime::PlayerState_EventTime(){}

void PlayerState_EventTime::unique_init(){

}

void PlayerState_EventTime::update(float deltaTime){
	if (cntr_->getWorld()->isLetOuted()) change(PlayerState_Enum_Union::LEAN_BACK);
}

void PlayerState_EventTime::end(){
	butty_->reset_enemy();
	retty_->reset_enemy();
}

void PlayerState_EventTime::key_input(){

}

void PlayerState_EventTime::pad_input(){

}
