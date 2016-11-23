#include "PlayerState_Single_Idle.h"

PlayerState_Single_Idle::PlayerState_Single_Idle() {}

void PlayerState_Single_Idle::unique_init(){
}

void PlayerState_Single_Idle::update(float deltaTime){
	
	InputMgr::GetInstance().isConnectGamePad() ? pad_update() : key_update();

	move();

}

void PlayerState_Single_Idle::end(){
}

void PlayerState_Single_Idle::move(){

	player_body_->gravity();
}

void PlayerState_Single_Idle::key_update(){
	Vector2 vector = InputMgr::GetInstance().KeyVector(player_body_->get_keys().right, player_body_->get_keys().left);
	player_body_->move(vector.Horizontal());

	if (InputMgr::GetInstance().IsKeyDown(player_body_->get_keys().up))change(StateElement((unsigned int)PlayerState_Enum_Single::JUMP));

}

void PlayerState_Single_Idle::pad_update(){
	Vector2 vector = Vector2::Zero;
	if (player_body_->get_keys().right == KeyCode::RIGHT)vector = InputMgr::GetInstance().AnalogPadVectorR();
	if (player_body_->get_keys().right == KeyCode::D)vector = InputMgr::GetInstance().AnalogPadVectorL();
	player_body_->move(vector.Horizontal());


	if (player_body_->get_keys().right == KeyCode::RIGHT) {
		if (InputMgr::GetInstance().AnalogPadVectorR().y <= -1)change(StateElement((unsigned int)PlayerState_Enum_Single::JUMP));
	}
	if (player_body_->get_keys().right == KeyCode::D) {
		if (InputMgr::GetInstance().AnalogPadVectorL().y <= -1)change(StateElement((unsigned int)PlayerState_Enum_Single::JUMP));
	}

}
