#include "PlayerBodyPoint.h"

#include "PlayerConnector.h"

// コンストラクタ
PlayerBodyPoint::PlayerBodyPoint(IWorld * world, const Vector2 & position, const int& index) :
	Actor(world, "BodyPoint" , position, CollisionBase(Vector2(0, 0), PLAYER_RADIUS * 0.2f)), index_(index),
	stiffness_(4.0f),
	friction_(0.1f),
	mass_(0.8f) {
}

// デストラクタ
PlayerBodyPoint::~PlayerBodyPoint(){}

// 更新処理
void PlayerBodyPoint::onUpdate(float deltaTime) {
	//attract_update(deltaTime);
}

// 描画処理
void PlayerBodyPoint::onDraw() const{
	body_.draw(inv_);
}

// 衝突処理
void PlayerBodyPoint::onCollide(Actor & other){
	if (other.getName() == "MovelessFloor") {
		auto pos = body_.GetCircle().previousPosition_;

		auto t_left = other.getBody().GetBox().component_.point[0];
		auto t_right = other.getBody().GetBox().component_.point[1];
		auto b_left = other.getBody().GetBox().component_.point[2];
		auto b_right = other.getBody().GetBox().component_.point[3];

		auto center = t_left + other.getBody().GetBox().getSize() / 2;

		auto top = Vector2::Cross((t_left - t_right).Normalize(), (pos - t_right));
		auto right = Vector2::Cross((t_right - b_right).Normalize(), (pos - b_right));
		auto bottom = Vector2::Cross((b_right - b_left).Normalize(), (pos - b_left));
		auto left = Vector2::Cross((b_left - t_left).Normalize(), (pos - t_left));

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
		if (left <= 0 && right <= 0 && top <= 0 && bottom <= 0) {
			Vector2 vec = (pos - center).Normalize();
			position_ = center + vec * (t_left - center).Length();
			if (vec.Length() <= 0) position_ = center + Vector2::Down * (t_left - center).Length();
		}
	}
}

// 引力更新処理
void PlayerBodyPoint::attract_update(float deltaTime){
	//attraction(index_ + 1, v2_);
	//attraction(index_ - 1, v1_);
	//position_ += v1_ + v2_ + Vector2(0, 9.8f) / 10;

	auto cntr = std::dynamic_pointer_cast<PlayerConnector>(world_->findActor("PlayerConnector"));
	if (cntr == nullptr)return;
	//if (cntr->length_sum() > PLAYER_MAX_NORMAL_LENGTH) {
	v1_ = Vector2::Spring_v(position_, cntr->get_point(index_ + 1), v1_, stiffness_, friction_, mass_);
	v2_ = Vector2::Spring_v(position_, cntr->get_point(index_ - 1), v2_, stiffness_, friction_, mass_);
	//}
	position_ += (v1_ + v2_ + Vector2(0, 9.8f) / 5) * deltaTime * 60;

	position_ = Vector2::ClampTarget(position_, cntr->get_point(index_ + 1), PLAYER_MAX_DIV_LENGTH);
	position_ = Vector2::ClampTarget(position_, cntr->get_point(index_ - 1), PLAYER_MAX_DIV_LENGTH);


	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::Z))stiffness_ += 0.01f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::X))stiffness_ -= 0.01f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::C))friction_ += 0.01f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::V))friction_ -= 0.01f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::B))mass_ += 0.01f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::N))mass_ -= 0.01f;

	//if (InputMgr::GetInstance().IsKeyDown(KeyCode::M)) {
	//	stiffness_ = 3.0f;
	//	friction_ = 0.1f;
	//	mass_ = 0.8f;
	//}
}

// 引力
void PlayerBodyPoint::attraction(const int index, Vector2 & velocity){
	auto cntr = std::dynamic_pointer_cast<PlayerConnector>(world_->findActor("PlayerConnector"));
	//if ((position_ - cntr->get_point(index)).Length() <= PLAYER_MIN_DIV_LENGTH)return;
	velocity  = Vector2::Spring_v(position_, cntr->get_point(index), velocity, stiffness_, friction_, mass_);
	position_ = Vector2::ClampTarget(position_, cntr->get_point(index), PLAYER_MAX_DIV_LENGTH);
}


