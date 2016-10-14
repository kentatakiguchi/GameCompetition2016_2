#include "PlayerBody.h"

const float SPEED = 1.0f;
const float MAX_NORMAL_LENGTH = 100.0f;
const float MAX_STRETCH_LENGTH = 150.0f;

PlayerBody::PlayerBody(IWorld * world, const std::string name, const Vector3 & position) :
	Actor(world, name, position, BoundingSphere(10.0f)){
	selected_ = false;
}

PlayerBody::~PlayerBody(){
}

void PlayerBody::onUpdate(float deltaTime){
	//// プレーヤを検索
	//auto player = world_->findActor("PlayerBody_Connector");
	//// プレーヤがいない
	//if (player == nullptr) return;

	position_ = Vector3::Clamp(position_, Vector3::Zero, Vector3(640, 480, 0) - Vector3(50, 50, 0));


}

void PlayerBody::onDraw() const{
	if (!selected_) {
		DrawCircle(position_.x, position_.y, body_.component_.radius_, GetColor(0, 0, 255), FALSE);
	}
	else {
		DrawCircle(position_.x, position_.y, body_.component_.radius_, GetColor(0, 255, 0), FALSE);
	}
}

void PlayerBody::onCollide(Actor & other){
}

void PlayerBody::changeMotion(float deltaTime){
}

void PlayerBody::move(KeyCode up, KeyCode down, KeyCode right, KeyCode left){
	//if (distance() > MAX_STRETCH_LENGTH) position_ = lastPos_;
	//
	//lastPos_ = position_;

	velocity_ = Vector3::Zero;
	if (InputMgr::GetInstance().IsKeyOn(right)) {
		velocity_.x = 1;
	}
	if (InputMgr::GetInstance().IsKeyOn(left)) {
		velocity_.x = -1;
	}
	if (InputMgr::GetInstance().IsKeyOn(up)) {
		velocity_.y = -1;
	}
	if (InputMgr::GetInstance().IsKeyOn(down)) {
		velocity_.y = 1;
	}
	position_ += velocity_ * SPEED;

	selected_ = true;
}

void PlayerBody::chase() {
	if (target_ == nullptr || Vector3::Distance(Vector3::Zero, velocity_) > 0)return;
	Vector3 targetPos = target_->getPosition();
	if (distance() <= MAX_NORMAL_LENGTH) return;
	Vector3 vec = Vector3::Normalize(position_ - targetPos) * MAX_NORMAL_LENGTH;
	position_ = Vector3::Lerp(position_, targetPos + vec, 0.05f);

	selected_ = false;
}

void PlayerBody::gravity(){
	position_ += Vector3(0, 10, 0) / 2;
}

void PlayerBody::circleClamp() {
	//if (target_ == nullptr)return;
	if (distance() > MAX_STRETCH_LENGTH) {
		Vector3	vec = Vector3::Normalize(position_ - target_->getPosition());
		position_ = target_->getPosition() + vec * MAX_STRETCH_LENGTH;
		//position_ = lastPos_;
	}
	//lastPos_ = position_;
}

void PlayerBody::launch(Vector3 dir){
	position_ += dir;
}

float PlayerBody::distance(){
	return Vector3::Distance(position_, target_->getPosition());
}

void PlayerBody::target(std::shared_ptr<PlayerBody> target){
	target_ = target;
}

