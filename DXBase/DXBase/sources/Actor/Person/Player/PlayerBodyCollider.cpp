#include "PlayerBodyCollider.h"

PlayerBodyCollider::PlayerBodyCollider(IWorld * world, std::string& name, PlayerBodyPtr parent)	:
	Actor(world, name + "Collider", Vector2::Zero, CollisionBase(Vector2(0, 0), PLAYER_COLLIDER_RADIUS)),
	parent_(parent){
}

PlayerBodyCollider::~PlayerBodyCollider(){}

void PlayerBodyCollider::onUpdate(float deltaTime){
	opponent_ = HitOpponent::NONE;

	//other_velocity_ = Vector2::Zero;
}

void PlayerBodyCollider::onDraw() const{
	body_.draw(inv_);
}

void PlayerBodyCollider::onCollide(Actor & other) {
	if (other.getName() == "MovelessFloor" ||
		other.getName() == "MoveFloorUpDown" || other.getName() == "MoveFloorRightLeft" ||
		other.getName() == "TurnFloor" || other.getName() == "TranslessTurnFloor") {
		opponent_ = HitOpponent::FLOOR_HIT;
		other_velocity_ = other.getBody().GetColliderVelocity();
		other_position_ = other.getBody().GetBox().position_;
	}
}

void PlayerBodyCollider::pos_update(){
	position_ = parent_->getPosition();
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
