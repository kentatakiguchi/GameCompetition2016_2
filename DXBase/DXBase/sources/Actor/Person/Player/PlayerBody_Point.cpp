#include "PlayerBody_Point.h"

PlayerBody_Point::PlayerBody_Point(IWorld * world, const std::string& name, const int& point_num) :
	Actor(world, name + std::to_string(point_num) , Vector2::Zero, CollisionBase(Vector2(0, 0), PLAYER_RADIUS)),
	num_(point_num){
}

PlayerBody_Point::~PlayerBody_Point(){}

void PlayerBody_Point::onUpdate(float deltaTime){

}

void PlayerBody_Point::onDraw() const{
	
}

void PlayerBody_Point::onLateUpdate(float deltaTime){

}

void PlayerBody_Point::onCollide(Actor & other){

}

void PlayerBody_Point::move(KeyCode up, KeyCode down, KeyCode right, KeyCode left){

}
