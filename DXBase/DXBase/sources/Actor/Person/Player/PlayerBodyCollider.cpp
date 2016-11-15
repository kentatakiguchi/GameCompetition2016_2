#include "PlayerBodyCollider.h"

PlayerBodyCollider::PlayerBodyCollider(IWorld * world, std::string& name, PlayerBodyPtr parent)	:
	Actor(world, name + "Collider", Vector2::Zero, CollisionBase(Vector2(0, 0), PLAYER_COLLIDER_RADIUS)),
	parent_(parent){
}

PlayerBodyCollider::~PlayerBodyCollider(){}

void PlayerBodyCollider::onUpdate(float deltaTime){
	opponent_ = HitOpponent::NONE;
}

void PlayerBodyCollider::onDraw() const{
	//body_.draw(inv_);
}

void PlayerBodyCollider::onCollide(Actor & other) {
	if (other.getName() == "MovelessFloor") {
		opponent_ = HitOpponent::FLOOR_HIT;
	}
}

void PlayerBodyCollider::pos_update(){
	position_ = parent_->getPosition();
}

HitOpponent PlayerBodyCollider::opponent(){
	return opponent_;
}
