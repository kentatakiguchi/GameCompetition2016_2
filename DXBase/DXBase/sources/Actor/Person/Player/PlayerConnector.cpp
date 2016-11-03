#include "PlayerConnector.h"
#include"../../Body/CollisionBase.h"

#include "PlayerBody_Point.h"

PlayerConnector::PlayerConnector()
{
}

PlayerConnector::PlayerConnector(IWorld * world, PlayerBodyPtr main, PlayerBodyPtr sub) :
	Actor(world, "PlayerConnector", Vector2::Zero, CollisionBase(Vector2(0, 0), Vector2(0, 0))) {
	//start_point_ = Vector2::Zero;
	//end_point_ = Vector2::Zero;
	points = std::vector<Vector2>();

}

PlayerConnector::~PlayerConnector(){}

void PlayerConnector::onUpdate(float deltaTime){
	auto player = world_->findActor("Player");
	if (player == nullptr) return;

	//auto player_ptr = std::static_pointer_cast<Player>(player);
	//Vector2 main_pos = player_ptr->getMainBody()->getPosition();
	//Vector2 sub_pos = player_ptr->getSubBody()->getPosition();
	//position_ = (main_pos + sub_pos) / 2;
	//body_.RotateSegment(main_pos - position_, sub_pos - position_);
	//start_point_ = main_pos;
	//end_point_ = sub_pos;

	//Vector2 input_ = Vector2::Zero;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::L)) input_.x = 1;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::J)) input_.x = -1;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::I)) input_.y = -1;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::K)) input_.y = 1;
	//position_ += input_ * 10;

	//points[0] = start_point_;
	////points[1] = start_point_;
	////points[2] = start_point_;

	//if (map_chip_ == nullptr) {
	//	points[0] = center + (inter - center).Normalize() * width * 2;

	//}
	//else {
	//	float height = map_chip_.getHeight();
	//	float width = map_chip_.getHeight();
	//	Vector2 pos = map_chip_.component_.point[0];
	//	Vector2 center = pos + Vector2(width, height) / 2;
	//	Vector2 segment = (start_point_ - end_point_).Normalize();
	//	Vector2 m_center = center - end_point_;
	//	float length = Vector2::Dot(segment, m_center);
	//	Vector2 inter = end_point_ + segment * length;

	//	points[0] = center + (inter - center).Normalize() * width * 2;

	//}

	//bezier_.set(start_point_->getPosition(), end_point_->getPosition(), points, 0);

}

void PlayerConnector::onLateUpdate(float deltaTime){}

void PlayerConnector::onDraw() const{
	body_.draw();
	//bezier_.draw(100);
}

void PlayerConnector::onCollide(Actor & other){
	if (other.getName() == "MapChip") {
		map_chip_ = other.getBody().GetBox();
	}
}

void PlayerConnector::changeMotion(float deltaTime){
}

void PlayerConnector::set_point(PlayerBodyPtr start, PlayerBodyPtr end){
	start_point_ = start;
	end_point_ = end;
}

void PlayerConnector::create_point(int point_num) {
	for (int i = 0; i < point_num; i++) {
		points.push_back(start_point_->getPosition());
		addChild(std::make_shared<PlayerBody_Point>(world_, "Body_Point", i + 1));
	}
}
