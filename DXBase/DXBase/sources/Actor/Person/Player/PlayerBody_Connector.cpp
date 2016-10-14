#include "PlayerBody_Connector.h"

PlayerBody_Connector::PlayerBody_Connector(IWorld * world, const Vector3 & position) :
	Actor(world, "PlayerBody_Connector", position, BoundingSphere(10.0f)){
}

PlayerBody_Connector::~PlayerBody_Connector(){
}

void PlayerBody_Connector::onUpdate(float deltaTime){
}

void PlayerBody_Connector::onDraw() const{
	DrawLine(position_.x, position_.y, body_.component_.radius_, body_.component_.radius_, GetColor(255, 255, 255));
}

void PlayerBody_Connector::onCollide(Actor & other)
{
}

void PlayerBody_Connector::changeMotion(float deltaTime)
{
}
