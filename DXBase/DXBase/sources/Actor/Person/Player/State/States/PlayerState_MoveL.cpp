#include "PlayerState_MoveL.h"
#include "../Player_EnumState.h"

PlayerState_MoveL::PlayerState_MoveL(){}

void PlayerState_MoveL::unique_init(Actor & actor){
}

void PlayerState_MoveL::update(Actor & actor, float deltaTime){
	move(actor, deltaTime);

	if (InputMgr::GetInstance().IsKeyUp(KeyCode::LEFT)) change((unsigned int)Player_EnumState::IDLE);

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT)) change(StateElement((unsigned int)Player_EnumState::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) change(StateElement((unsigned int)Player_EnumState::HOLD, ActionType::Left));
}

void PlayerState_MoveL::end(){
}

void PlayerState_MoveL::move(Actor & actor, float deltaTime) {
	main_body_->move();
	main_body_->gravity();
	sub_body_->gravity();
	sub_body_->chase();
}

