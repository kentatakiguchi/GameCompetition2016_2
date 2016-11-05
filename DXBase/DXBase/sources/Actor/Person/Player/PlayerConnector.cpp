#include "PlayerConnector.h"
#include"../../Body/CollisionBase.h"

#include "PlayerBody_Point.h"

PlayerConnector::PlayerConnector(){}

PlayerConnector::PlayerConnector(IWorld * world, PlayerBodyPtr main, PlayerBodyPtr sub) :
	Actor(world, "PlayerConnector", Vector2::Zero, CollisionBase(Vector2(0, 0), Vector2(0, 0))) {
	start_point_ = main;
	end_point_ = sub;

	points = std::vector<Vector2>(3);

	create_point(3);
}

PlayerConnector::~PlayerConnector(){}

void PlayerConnector::onUpdate(float deltaTime){

	for (int i = 0; i < 3; i++) {
		auto player = world_->findActor("Body_Point" + std::to_string(i + 1));
		points[i] = player->getPosition();
	}

	bezier_.set(start_point_->getPosition(), end_point_->getPosition(), points, 100);
}

void PlayerConnector::onLateUpdate(float deltaTime){}

void PlayerConnector::onDraw() const{
	body_.draw();
	bezier_.draw(100);
}

void PlayerConnector::onCollide(Actor & other){
	if (other.getName() == "MapChip") {
		map_chip_ = other.getBody().GetBox();
	}
}

void PlayerConnector::create_point(int point_num) {
	//points.push_back(std::make_shared<PlayerBody_Point>(world_, "Body_Point", point_num, 0, start_point_, end_point_));
	//addChild(points[0]);
	for (int i = 0; i < point_num; i++) {
		//points.push_back(std::make_shared<PlayerBody_Point>(world_, "Body_Point", point_num + 1, i + 1, start_point_, end_point_));
		addChild(std::make_shared<PlayerBody_Point>(world_, "Body_Point", point_num + 1, i + 1, start_point_, end_point_));
	}
	//points.push_back(std::make_shared<PlayerBody_Point>(world_, "Body_Point", point_num, points.size, start_point_, end_point_));
	//addChild(points[points.size]);
}
