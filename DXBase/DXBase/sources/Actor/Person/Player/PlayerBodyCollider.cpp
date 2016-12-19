#include "PlayerBodyCollider.h"

PlayerBodyCollider::PlayerBodyCollider(IWorld * world, std::string& name):
	Actor(world, name + "Collider", Vector2::Zero, std::make_shared<BoundingCircle>(Vector2::Zero, Matrix::Identity, PLAYER_COLLIDER_RADIUS, true)){
}

PlayerBodyCollider::~PlayerBodyCollider(){}

void PlayerBodyCollider::onUpdate(float deltaTime){
	opponent_ = HitOpponent::NONE;

	other_velocity_ = Vector2::Zero;
}

void PlayerBodyCollider::onDraw() const{
}

void PlayerBodyCollider::onCollide(Actor & other) {
	if (other.getName() == "MovelessFloor" || other.getName() == "SegmentCollider" ||
		other.getName() == "MoveFloorUpDown" || other.getName() == "MoveFloorRightLeft" ||
		other.getName() == "TurnFloor" || other.getName() == "TranslessTurnFloor") {
		opponent_ = HitOpponent::FLOOR_HIT;
		other_velocity_ = other.getBody()->velocity();
		other_position_ = other.getBody()->cur_pos();
	}
}

void PlayerBodyCollider::pos_update(Vector2 parent_pos){
	position_ = parent_pos;
}

void PlayerBodyCollider::reset_pos(){
	other_position_ = Vector2::Zero;
}

Vector2 PlayerBodyCollider::other_velocity(){
	return other_velocity_;
}

Vector2 PlayerBodyCollider::other_position(){
	return other_position_;
}

HitOpponent PlayerBodyCollider::opponent(){
	return opponent_;
}
