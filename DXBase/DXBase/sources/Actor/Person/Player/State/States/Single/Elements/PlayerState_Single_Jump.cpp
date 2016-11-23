#include "PlayerState_Single_Jump.h"

PlayerState_Single_Jump::PlayerState_Single_Jump() {}

void PlayerState_Single_Jump::unique_init(){
	player_body_->reset_velocity();
	player_body_->reset_opponent();

	dump_ = 0;
	dir_ = Vector2::Down;
	power_ = PLAYER_JUMP_POWER;
	dir_easeing_ = 0;
	gra_easeing_ = 0;
	player_body_->launch(dir_ * power_);
}

void PlayerState_Single_Jump::update(float deltaTime){
	timer_ += deltaTime;

	//gra_easeing_ = EasingInExpo(timer_);

	dir_.y += 0.1f/* * gra_easeing_*/;

	player_body_->launch(dir_ * power_);



	InputMgr::GetInstance().isConnectGamePad() ? pad_update() : key_update();

	move();

	if (player_body_->able_to_jump()) change((unsigned int)PlayerState_Enum_Single::IDLE);
}

void PlayerState_Single_Jump::end(){}

void PlayerState_Single_Jump::move(){}

void PlayerState_Single_Jump::key_update(){
	Vector2 vector = InputMgr::GetInstance().KeyVector(player_body_->get_keys().right, player_body_->get_keys().left);
	player_body_->move(vector.Horizontal());
}

void PlayerState_Single_Jump::pad_update(){
	Vector2 vector = Vector2::Zero;
	if (player_body_->get_keys().right == KeyCode::RIGHT)vector = InputMgr::GetInstance().AnalogPadVectorR();
	if (player_body_->get_keys().right == KeyCode::D)vector = InputMgr::GetInstance().AnalogPadVectorL();
	player_body_->move(vector.Horizontal());
}
