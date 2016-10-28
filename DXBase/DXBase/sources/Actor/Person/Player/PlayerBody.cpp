#include "PlayerBody.h"
#include"../../Body/CollisionBase.h"

const float SPEED = 3.0f;
const float MAX_NORMAL_LENGTH = 100.0f;
const float MAX_STRETCH_LENGTH = 150.0f;

PlayerBody::PlayerBody(IWorld * world, const std::string name, const Vector3 & position) :
	Actor(world, name, position, CollisionBase(Vector2(0, 0), 20.0f)) {
}

PlayerBody::~PlayerBody(){}

void PlayerBody::onUpdate(float deltaTime){
	velocity_ = input_ * SPEED + gravity_ + launch_;

	position_ += velocity_;

	position_ = Vector3::Clamp(position_, Vector3::Zero, Vector3(3000, 1000, 0));

}

void PlayerBody::onDraw() const{
	if (name_ == "PlayerBody1")	DrawFormatString(25, 25, GetColor(255, 255, 255), "1 : x->%d, y->%d", (int)velocity_.x, (int)velocity_.y);
	if (name_ == "PlayerBody2")	DrawFormatString(25, 50, GetColor(255, 255, 255), "2 : x->%d, y->%d", (int)velocity_.x, (int)velocity_.y);

	body_.draw();

	if (opponent_ == Opponent::NONE)DrawFormatString(25, 75, GetColor(255, 255, 255), "NONE");
	else if (opponent_ == Opponent::FLOOR) DrawFormatString(25, 100, GetColor(255, 255, 255), "FLOOR");
}

void PlayerBody::onLateUpdate(float deltaTime){

	input_ = Vector3::Zero;
	gravity_ = Vector3::Zero;
	launch_ = Vector3::Zero;
}

void PlayerBody::onCollide(Actor & other){

	if (other.getName() == "MapChip") {
		auto pos = Vector2(position_.x, position_.y);

		auto t_left =  other.getBody().GetBox().component_.point[0];
		auto t_right = other.getBody().GetBox().component_.point[1];
		auto b_left = other.getBody().GetBox().component_.point[2];
		auto b_right = other.getBody().GetBox().component_.point[3];

		auto m_top = (t_left + t_right) / 2;
		auto m_bot = (b_left + b_right) / 2;
		auto m_left = (t_left + b_left) / 2;
		auto m_right = (t_right + b_right) / 2;

		auto top    = Vector2::Cross((t_left - t_right).Normalize(), (pos - t_right));
		auto right  = Vector2::Cross((t_right - b_right).Normalize(), (pos - b_right));
		auto bottom = Vector2::Cross((b_right - b_left).Normalize(), (pos - b_left));
		auto left = Vector2::Cross((b_left - t_left).Normalize(), (pos - t_left));
		auto up_down = Vector2::Cross(m_left - m_right, (pos - m_right));
		auto right_left = Vector2::Cross(m_top - m_bot, (pos - m_bot));

		auto vec = pos - Vector2(last_pos_.x, last_pos_.y);

		//if (up_down > 0 && left <= 0 && right <= 0) {
		//	//auto ca = t_left - Vector2(last_pos_.x, last_pos_.y);
		//	//auto cb = t_left - Vector2(position_.x, position_.y);
		//	//auto cd = t_left - t_right;
		//	//auto ratio1 = Vector2::Cross(ca, cd);
		//	//auto ratio2 = Vector2::Cross(cb, cd);
		//	//x = Vector2::Zero;
		//	//x = Vector2(last_pos_.x, last_pos_.y) + vec * ratio1 / (ratio1 + ratio2);
		//	//
		//	//position_.y = x.y - body_.GetCapsule().component_.radius;
		//	
		//	position_.y = t_left.y - body_.GetCircle().component_.radius;
		//}

		//if (up_down < 0 && left <= 0 && right <= 0) {

		//	position_.y = t_left.y - body_.GetCapsule().component_.radius;
		//}

		if (top > 0 && left <= 0 && right <= 0) {
			position_.y = t_left.y - body_.GetCircle().component_.radius;
		}
		else if (bottom > 0 && left <= 0 && right <= 0) {

			position_.y = b_right.y + body_.GetCircle().component_.radius;
		}
		else if (right > 0 && top <= 0 && bottom <= 0) {

			position_.x = t_right.x + body_.GetCircle().component_.radius;
		}
		else if (left > 0 && top <= 0 && bottom <= 0) {

			position_.x = b_left.x - body_.GetCircle().component_.radius;
		}

		opponent_ = Opponent::FLOOR;
	}
	else if (other.getName() == "item") {
		opponent_ = Opponent::ITEM;
	}
}

void PlayerBody::changeMotion(float deltaTime){
}

void PlayerBody::move(KeyCode up, KeyCode down, KeyCode right, KeyCode left){
	if (distance() > MAX_STRETCH_LENGTH) {	}

	input_ = Vector3::Zero;
	if (InputMgr::GetInstance().IsKeyOn(right)) input_.x = 1;
	if (InputMgr::GetInstance().IsKeyOn(left)) 	input_.x = -1;
	if (InputMgr::GetInstance().IsKeyOn(up)) 	input_.y = -1;
	if (InputMgr::GetInstance().IsKeyOn(down)) 	input_.y = 1;
	
	//position_ += input_ * SPEED;
}

void PlayerBody::move_ver(KeyCode up, KeyCode down, KeyCode right, KeyCode left){
	if (distance() > MAX_STRETCH_LENGTH) {	}

	if (InputMgr::GetInstance().IsKeyOn(down))	input_.y = 1;
	if (InputMgr::GetInstance().IsKeyOn(up))	input_.y = -1;

	//position_ += input_ * SPEED;
}

void PlayerBody::move_hor(KeyCode up, KeyCode down, KeyCode right, KeyCode left){

	if (InputMgr::GetInstance().IsKeyOn(right)) input_.x = 1;
	if (InputMgr::GetInstance().IsKeyOn(left)) 	input_.x = -1;

	//if (distance() >= MAX_STRETCH_LENGTH) {
	//	//auto vec = Vector3::Normalize(position_ - target_->getPosition()) * MAX_STRETCH_LENGTH;
	//	//position_ = target_->getPosition() + vec;
	//	velocity_ = Vector3::Zero;

	//	//position_ = last_pos_;
	//	return;
	//}
	//if (distance() >= MAX_STRETCH_LENGTH) {
	//}

	//position_ += input_ * SPEED;
}

void PlayerBody::chase() {
	if (target_ == nullptr || Vector3::Distance(Vector3::Zero, input_) > 0)return;
	if (distance() <= MAX_NORMAL_LENGTH) return;
	auto vec = Vector3::Normalize(position_ - target_->getPosition()) * MAX_NORMAL_LENGTH;
	position_ = Vector3::Lerp(position_, target_->getPosition() + vec, 0.2f);
}

void PlayerBody::gravity(){
	if (opponent_ == Opponent::FLOOR)gravity_ = Vector3(0, 5, 0);
	else gravity_ = Vector3(0, 5, 0);
}

void PlayerBody::acc_gravity(){

}

void PlayerBody::hold_gravity(){
	if (Vector3::Distance(Vector3::Zero, input_) > 0)return;
	gravity();
}

void PlayerBody::circleClamp() {
	if (distance() > MAX_STRETCH_LENGTH) {
		Vector3	vec = Vector3::Normalize(position_ - target_->getPosition());
		position_ = target_->getPosition() + vec * MAX_STRETCH_LENGTH;
	}
}

void PlayerBody::launch(Vector3 dir){
	launch_ = dir;
}

PlayerBody::Opponent PlayerBody::hitOpponent(){
	return opponent_;
}

void PlayerBody::reset_opponent(){
	opponent_ = Opponent::NONE;
}

void PlayerBody::reset_velocity(){
	input_ = Vector3::Zero;
}

void PlayerBody::pre_vector(){
	last_pos_ = position_;
}

float PlayerBody::distance(){
	return Vector3::Distance(position_, target_->getPosition());
}

void PlayerBody::target(std::shared_ptr<PlayerBody> target){
	target_ = target;
}

void PlayerBody::set_name(std::string name){
	name_1_ = name;
}

