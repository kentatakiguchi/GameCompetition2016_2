#include "PlayerState_Move.h"
#include "../Player_EnumState.h"

PlayerState_Move::PlayerState_Move(){}

void PlayerState_Move::unique_init(Actor & actor){
}

void PlayerState_Move::update(Actor & actor, float deltaTime){
	move(actor, deltaTime);

	if (InputMgr::GetInstance().IsStoped(KeyCode::W, KeyCode::S, KeyCode::D, KeyCode::A) &&
		InputMgr::GetInstance().IsStoped(KeyCode::UP, KeyCode::DOWN, KeyCode::RIGHT, KeyCode::LEFT)) {
		change((unsigned int)Player_EnumState::IDLE);
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT)) change(StateElement((unsigned int)Player_EnumState::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) change(StateElement((unsigned int)Player_EnumState::HOLD, ActionType::Left));
}

void PlayerState_Move::end(){ }

void PlayerState_Move::move(Actor & actor, float deltaTime) {
	main_body_->move_ver();
	sub_body_->move_ver(KeyCode::W, KeyCode::S, KeyCode::D, KeyCode::A);

	main_body_->chase();
	sub_body_->chase();
}

