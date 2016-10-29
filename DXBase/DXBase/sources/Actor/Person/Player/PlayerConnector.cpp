#include "PlayerConnector.h"
#include "Player.h"
#include "PlayerBody.h"
#include"../../Body/CollisionBase.h"

PlayerConnector::PlayerConnector(IWorld * world) :
	Actor(world, "PlayerConnector", Vector2::Zero, CollisionBase(Vector2(0, 0), Vector2(0, 0))) {
	start_point_ = Vector2::Zero;
	end_point_ = Vector2::Zero;
	points = std::vector<Vector2>();
	points.push_back(start_point_);
	//points.push_back(start_point_);
	//points.push_back(start_point_);
}

PlayerConnector::~PlayerConnector(){}

void PlayerConnector::onUpdate(float deltaTime){
	auto player = world_->findActor("Player");

	auto body1 = player->findCildren((const std::string)"PlayerBody1");
	auto body2 = player->findCildren((const std::string)"PlayerBody2");

	Vector2 input_ = Vector2::Zero;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L)) input_.x = 1;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::J)) input_.x = -1;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::I)) 	input_.y = -1;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::K)) input_.y = 1;
	position_ += input_ * 10;

	points[0] = (start_point_ + end_point_) / 2 + position_;
	//points[1] = start_point_;
	//points[2] = start_point_;
	bezier_.set(start_point_, end_point_, points, 0);
	//body_.draw();
}

void PlayerConnector::onLateUpdate(float deltaTime){}

void PlayerConnector::onDraw() const{
	bezier_.draw(100);
}

void PlayerConnector::onCollide(Actor & other){
	if (other.getName() == "TestColl") {
		auto pos = Vector2(position_.x, position_.y);
	}
}

void PlayerConnector::changeMotion(float deltaTime){
}

void PlayerConnector::set_point(const Vector2 & start, const Vector2 & end){
	start_point_ = start;
	end_point_ = end;
}
