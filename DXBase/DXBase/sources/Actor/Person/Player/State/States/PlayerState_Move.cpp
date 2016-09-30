#include "PlayerState_Move.h"
#include "../Player_EnumState.h"

PlayerState_Move::PlayerState_Move(){}

void PlayerState_Move::init(Actor & actor){
	isEndRequest = false;
	actor.setMotion(7);
}

void PlayerState_Move::update(Actor & actor, float deltaTime){
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::Z)) change((unsigned int)Player_EnumState::ATTACK);
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::X)) change((unsigned int)Player_EnumState::ATTACK);

	if (move(actor, deltaTime)) {
		change((unsigned int)Player_EnumState::IDLE);
	}
}

void PlayerState_Move::change(unsigned int nextState) {
	nextState_ = nextState;
	isEndRequest = true;
}

bool PlayerState_Move::isEnd(){
	return isEndRequest;
}

unsigned int PlayerState_Move::next() const{
	return (unsigned int)nextState_;
}

void PlayerState_Move::end(){

}

bool PlayerState_Move::move(Actor & actor, float deltaTime) {
	float forward_speed = 0.0f;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::UP)) {
		forward_speed = -1.0f;
	}
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::DOWN)) {
	//	forward_speed = 1.0f;
	//}
	//float left_speed = 0.0f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::LEFT))left_speed = 1.0f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::RIGHT))left_speed = -1.0f;
	float yaw = 0.0f;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::LEFT))yaw = -1.0f;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::RIGHT))yaw = 1.0f;
	//float pitch = 0.0f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::UP))pitch = 1.0f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::DOWN))pitch = -1.0f;

	Vector3 position = actor.getPosition();
	Matrix rotation = actor.getRotate();

	rotation *= Matrix::CreateFromAxisAngle(rotation.Up(), yaw * 2);
	//rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Left(), pitch);
	rotation.NormalizeRotationMatrix();
	position += rotation.Forward() * forward_speed * 2;
	//position_ += rotation_.Left() * left_speed;
	position += rotation.Down();

	actor.setTransform(position, rotation);

	if (forward_speed == 0.0f && yaw == 0.0f) return true;
	return false;
}
