#include "PlayerConnector.h"
#include "Player.h"
#include "PlayerBody.h"

#include"../../Body/CollisionBase.h"

PlayerConnector::PlayerConnector(IWorld * world) :
	Actor(world, "PlayerConnector", Vector3::Zero, CollisionBase(Vector2::Zero, Vector2::Zero)){

}

PlayerConnector::~PlayerConnector(){
}

void PlayerConnector::onUpdate(float deltaTime){
	auto player = world_->findActor("Player");

	auto body1 = player->findCildren((const std::string)"PlayerBody1");
	auto body2 = player->findCildren((const std::string)"PlayerBody2");

	Vector2 pos1 = Vector2(body1->getPosition().x, body1->getPosition().y);
	Vector2 pos2 = Vector2(body2->getPosition().x, body2->getPosition().y);
	body_.transform(pos1, pos2);
}

void PlayerConnector::onLateUpdate(float deltaTime){
	auto player = world_->findActor("Player");

	auto body1 = player->findCildren((const std::string)"PlayerBody1");
	auto body2 = player->findCildren((const std::string)"PlayerBody2");

	Vector2 pos1 = Vector2(body1->getPosition().x, body1->getPosition().y);
	Vector2 pos2 = Vector2(body2->getPosition().x, body2->getPosition().y);

	body_.transform(pos1, pos2);
	body_.draw();
}

void PlayerConnector::onDraw() const{
}

void PlayerConnector::onCollide(Actor & other){
	if (other.getName() == "TestColl") {
		auto pos = Vector2(position_.x, position_.y);

	}
}

void PlayerConnector::changeMotion(float deltaTime){
}
