#include "PlayerState_Idle.h"

#include <algorithm>

PlayerState_Idle::PlayerState_Idle(){
}

void PlayerState_Idle::unique_init(Actor & actor){
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::RIGHT)) change((unsigned int)Player_EnumState::MOVE_R);
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::LEFT)) change((unsigned int)Player_EnumState::MOVE_L);
}

void PlayerState_Idle::update(Actor & actor, float deltaTime){
	//Vector3 position = actor.getPosition();
	//Matrix rotation = actor.getRotate();
	//actor.setTransform(position, rotation);
	

	main_body_->gravity();
	sub_body_->gravity();
	main_body_->move();
	sub_body_->move(KeyCode::W, KeyCode::S, KeyCode::D, KeyCode::A);
	main_body_->chase();
	sub_body_->chase();
	sub_body_->circleClamp();
	main_body_->circleClamp();

	//if (InputMgr::GetInstance().IsKeyDown(KeyCode::RIGHT)) change(StateElement((unsigned int)Player_EnumState::MOVE_R, ActionType::Right));
	//if (InputMgr::GetInstance().IsKeyDown(KeyCode::LEFT )) change(StateElement((unsigned int)Player_EnumState::MOVE_L, ActionType::Left));

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT)) change(StateElement((unsigned int)Player_EnumState::HOLD, ActionType::Right));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) change(StateElement((unsigned int)Player_EnumState::HOLD, ActionType::Left));
}

void PlayerState_Idle::end(){
}







