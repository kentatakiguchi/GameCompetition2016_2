#include "PlayerBodyPoint.h"

PlayerBodyPoint::PlayerBodyPoint(IWorld * world, const int& point_num, const int& point_index, PlayerConnector& cntr) :
	Actor(world, "BodyPoint" + std::to_string(point_index) , Vector2::Zero, CollisionBase(Vector2(0, 0), PLAYER_RADIUS)),
	num_(point_num),
	index_(point_index){
}

PlayerBodyPoint::~PlayerBodyPoint(){}

void PlayerBodyPoint::onUpdate(float deltaTime) {
	auto cntr = std::dynamic_pointer_cast<PlayerConnector>(world_->findActor("PlayerConnector"));

	Vector2 vec = cntr->composed_vector(position_, index_);

	position_ = Vector2::Lerp(position_, vec, 1.0f);
}

void PlayerBodyPoint::onDraw() const{
	body_.draw(inv_);
}

void PlayerBodyPoint::onLateUpdate(float deltaTime){

}

void PlayerBodyPoint::onCollide(Actor & other){
	if (other.getName() == "MovelessFloor") {
		auto pos = body_.GetCircle().previousPosition_;

		auto t_left = other.getBody().GetBox().component_.point[0];
		auto t_right = other.getBody().GetBox().component_.point[1];
		auto b_left = other.getBody().GetBox().component_.point[2];
		auto b_right = other.getBody().GetBox().component_.point[3];

		auto m_top = (t_left + t_right) / 2;
		auto m_bot = (b_left + b_right) / 2;
		auto m_left = (t_left + b_left) / 2;
		auto m_right = (t_right + b_right) / 2;

		auto top = Vector2::Cross((t_left - t_right).Normalize(), (pos - t_right));
		auto right = Vector2::Cross((t_right - b_right).Normalize(), (pos - b_right));
		auto bottom = Vector2::Cross((b_right - b_left).Normalize(), (pos - b_left));
		auto left = Vector2::Cross((b_left - t_left).Normalize(), (pos - t_left));
		auto up_down = Vector2::Cross(m_left - m_right, (pos - m_right));
		auto right_left = Vector2::Cross(m_top - m_bot, (pos - m_bot));

		if (top > 0 && left <= 0 && right <= 0) {
			position_.y = t_left.y - body_.GetCircle().component_.radius;
		}
		if (bottom > 0 && left <= 0 && right <= 0) {
			position_.y = b_right.y + body_.GetCircle().component_.radius;
		}
		if (right > 0 && top <= 0 && bottom <= 0) {
			position_.x = t_right.x + body_.GetCircle().component_.radius;
		}
		if (left > 0 && top <= 0 && bottom <= 0) {
			position_.x = b_left.x - body_.GetCircle().component_.radius;
		}

		opponent_ = Opponent::FLOOR;
	}
}

void PlayerBodyPoint::move(KeyCode up, KeyCode down, KeyCode right, KeyCode left){

}
