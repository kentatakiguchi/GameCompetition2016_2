#include "PlayerState_Single_Idle.h"

PlayerState_Single_Idle::PlayerState_Single_Idle(){
}

void PlayerState_Single_Idle::unique_init(Actor & actor){
}

void PlayerState_Single_Idle::update(Actor & actor, float deltaTime){


	move(actor, deltaTime);
}

void PlayerState_Single_Idle::end(){
}

void PlayerState_Single_Idle::move(Actor & actor, float deltaTime){
}
