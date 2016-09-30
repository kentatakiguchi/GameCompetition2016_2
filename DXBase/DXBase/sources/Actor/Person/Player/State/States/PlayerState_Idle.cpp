#include "PlayerState_Idle.h"

PlayerState_Idle::PlayerState_Idle() :
	nextState_(0),
	isEndRequest(false){

}

void PlayerState_Idle::init(Actor & actor){
	isEndRequest = false;
	actor.setMotion(3);
}

void PlayerState_Idle::update(Actor & actor, float deltaTime){

	Vector3 position = actor.getPosition();
	Matrix rotation = actor.getRotate();

	//position += rotation.Down() / 2;

	if (InputMgr::GetInstance().IsMoving()) change((unsigned int)Player_EnumState::MOVE);

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::SPACE)) change((unsigned int)Player_EnumState::JUMP);
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::Z)) change((unsigned int)Player_EnumState::ATTACK);
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::X)) change((unsigned int)Player_EnumState::ATTACK2);
}

void PlayerState_Idle::change(unsigned int nextState) {
	nextState_ = nextState;
	isEndRequest = true;
}

bool PlayerState_Idle::isEnd(){
	return isEndRequest;
}

unsigned int PlayerState_Idle::next() const{
	return (unsigned int)nextState_;
}

void PlayerState_Idle::end(){
}






