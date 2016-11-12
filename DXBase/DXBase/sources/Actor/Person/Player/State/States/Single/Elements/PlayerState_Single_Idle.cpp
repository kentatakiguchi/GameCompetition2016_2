#include "PlayerState_Single_Idle.h"

PlayerState_Single_Idle::PlayerState_Single_Idle(){
}

void PlayerState_Single_Idle::unique_init(Actor & actor){
}

void PlayerState_Single_Idle::update(Actor & actor, float deltaTime){
	
	move(actor, deltaTime);

	if (InputMgr::GetInstance().IsKeyDown(player_body_->get_keys().up))change(StateElement((unsigned int)PlayerState_Enum_Single::JUMP));
}

void PlayerState_Single_Idle::end(){
}

void PlayerState_Single_Idle::move(Actor & actor, float deltaTime){
	Vector2 vector = InputMgr::GetInstance().KeyVector(player_body_->get_keys().right, player_body_->get_keys().left);
	player_body_->move(vector.Horizontal());
	player_body_->gravity();
}
