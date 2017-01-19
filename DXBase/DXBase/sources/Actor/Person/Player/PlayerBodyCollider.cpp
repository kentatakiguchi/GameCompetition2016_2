#include "PlayerBodyCollider.h"

PlayerBodyCollider::PlayerBodyCollider(IWorld * world, std::string& name):
	Actor(world, name + "Collider", Vector2::Zero, CollisionBase(Vector2(0, 0), PLAYER_COLLIDER_RADIUS)){
}

PlayerBodyCollider::~PlayerBodyCollider(){}

void PlayerBodyCollider::onUpdate(float deltaTime){
	opponent_ = HitOpponent::NONE;

	other_velocity_ = Vector2::Zero;
}

void PlayerBodyCollider::onDraw() const{
}

void PlayerBodyCollider::onCollide(Actor & other) {
	if (other.getName() == "MovelessFloor"  ||
		other.getName() == "MoveFloorUpDown" || other.getName() == "MoveFloorRightLeft" ||
		other.getName() == "TurnFloor" || other.getName() == "TranslessTurnFloor") {
		opponent_ = HitOpponent::FLOOR_HIT;
		other_velocity_ = other.getBody().GetColliderVelocity();
		other_position_ = other.getBody().GetBox().position_;
	}
	if (other.getName() == "SegmentCollider") {
		opponent_ = HitOpponent::FLOOR_HIT;
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

void PlayerBodyCollider::reset_velocity() {
	other_velocity_ = Vector2::Zero;
}

Vector2 PlayerBodyCollider::other_position(){
	return other_position_;
}

HitOpponent PlayerBodyCollider::opponent(){
	return opponent_;
}
