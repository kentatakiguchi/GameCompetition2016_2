#include "PlayerState_Idle.h"

#include <algorithm>

PlayerState_Idle::PlayerState_Idle(){
}

void PlayerState_Idle::unique_init(Actor & actor){
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::RIGHT)) change((unsigned int)Player_EnumState::MOVE_R);
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::LEFT)) change((unsigned int)Player_EnumState::MOVE_L);
}

void PlayerState_Idle::update(Actor & actor, float deltaTime){
	main_body_->gravity();
	sub_body_->gravity();
	main_body_->chase();
	sub_body_->chase();
	main_body_->circleClamp();
	sub_body_->circleClamp();

	if (InputMgr::GetInstance().IsMoving(KeyCode::W, KeyCode::S, KeyCode::D, KeyCode::A)) change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE));
	if (InputMgr::GetInstance().IsMoving(KeyCode::UP, KeyCode::DOWN, KeyCode::RIGHT, KeyCode::LEFT)) change(StateElement((unsigned int)PlayerState_Enum_Union::MOVE));

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) change(StateElement((unsigned int)PlayerState_Enum_Union::HOLD, ActionType::Left));
}

void PlayerState_Idle::end(){
}
