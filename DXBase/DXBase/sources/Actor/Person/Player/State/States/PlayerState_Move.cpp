#include "PlayerState_Move.h"
#include "../Player_EnumState.h"

PlayerState_Move::PlayerState_Move(){}

void PlayerState_Move::unique_init(Actor & actor){
}

void PlayerState_Move::update(Actor & actor, float deltaTime){
	move(actor, deltaTime);

	if (InputMgr::GetInstance().IsKeyUp(KeyCode::RIGHT)) change((unsigned int)Player_EnumState::IDLE);

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT)) change(StateElement((unsigned int)Player_EnumState::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) change(StateElement((unsigned int)Player_EnumState::HOLD, ActionType::Left));
}

void PlayerState_Move::end(){
}

void PlayerState_Move::move(Actor & actor, float deltaTime) {
	main_body_->move();
	main_body_->gravity();
	sub_body_->gravity();
	sub_body_->chase();
}

