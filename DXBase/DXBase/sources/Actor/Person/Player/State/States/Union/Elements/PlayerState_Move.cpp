#include "PlayerState_Move.h"

PlayerState_Move::PlayerState_Move(){}

void PlayerState_Move::unique_init(Actor & actor){
}

void PlayerState_Move::update(Actor & actor, float deltaTime){
	move(actor, deltaTime);

	if (InputMgr::GetInstance().IsStoped(KeyCode::W, KeyCode::S, KeyCode::D, KeyCode::A) &&
		InputMgr::GetInstance().IsStoped(KeyCode::UP, KeyCode::DOWN, KeyCode::RIGHT, KeyCode::LEFT)) {
		change((unsigned int)PlayerState_Enum_Union::IDLE);
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

void PlayerState_Move::end(){ }

void PlayerState_Move::move(Actor & actor, float deltaTime) {
	main_body_->move_hor();
	sub_body_->move_hor(KeyCode::D, KeyCode::A);
	main_body_->chase();
	sub_body_->chase();
	main_body_->gravity();
	sub_body_->gravity();
}

