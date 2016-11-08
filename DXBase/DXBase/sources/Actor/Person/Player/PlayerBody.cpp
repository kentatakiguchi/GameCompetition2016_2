#include "PlayerBody.h"

#include"../../Body/CollisionBase.h"

//#include "State/States/State_Dammy.h"
#include "State/States/Single/Elements/PlayerState_Single_StandBy.h"
#include "State/States/Single/Elements/PlayerState_Single_Idle.h"
#include "State/States/Single/Elements/PlayerState_Single_Jump.h"

PlayerBody::PlayerBody(){}

PlayerBody::PlayerBody(IWorld * world, const std::string name, const Vector2 & position) :
	Actor(world, name, position, CollisionBase(Vector2(0, 0), PLAYER_RADIUS)),
	is_single_(false){
	keys_ = SingleKeys();
	if (name == "PlayerBody2")keys_ = SingleKeys(KeyCode::W, KeyCode::S, KeyCode::D, KeyCode::A);

	stateMgr_.add((unsigned int)PlayerState_Enum_Single::STAND_BY, std::make_shared<PlayerState_Single_StandBy>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Single::IDLE, std::make_shared<PlayerState_Single_Idle>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Single::JUMP, std::make_shared<PlayerState_Single_Jump>());
	//stateMgr_.add((unsigned int)PlayerState_Enum_Single::MOVE, std::make_shared<PlayerState_Single_Idle>());
	stateMgr_.changeState(*this, IState::StateElement((unsigned int)PlayerState_Enum_Single::STAND_BY));

}

PlayerBody::~PlayerBody(){}

void PlayerBody::onUpdate(float deltaTime){
	position_ += input_ * PLAYER_SPEED  + launch_ + gravity_;
	velocity_ = position_ - body_.GetCircle().previousPosition_;

	opponent_ = Opponent::NONE;
}

void PlayerBody::onDraw() const{
	//if (name_ == "PlayerBody1")	DrawFormatString(25, 25, GetColor(255, 255, 255), "1 : x->%d, y->%d", (int)velocity_.x, (int)velocity_.y);
	//if (name_ == "PlayerBody2")	DrawFormatString(25, 50, GetColor(255, 255, 255), "2 : x->%d, y->%d", (int)velocity_.x, (int)velocity_.y);

	body_.draw(/*inv()*/);

	if (opponent_ == Opponent::NONE)DrawFormatString(25, 75, GetColor(255, 255, 255), "NONE");
	else if (opponent_ == Opponent::FLOOR) DrawFormatString(25, 100, GetColor(255, 255, 255), "FLOOR");
}

void PlayerBody::onLateUpdate(float deltaTime){
	input_ = Vector2::Zero;
	gravity_ = Vector2::Zero;
	launch_ = Vector2::Zero;
}

void PlayerBody::onCollide(Actor & other){
	
	if (other.getName() == "MovelessFloor") {
		auto pos = body_.GetCircle().previousPosition_;

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
	if (other.getName() == "NavChip" && opponent_ != Opponent::FLOOR) {
		auto pos = body_.GetCircle().previousPosition_;

		auto box = other.getBody().GetBox();
		Vector2 center = box.component_.point[0] + Vector2(box.getWidth(), box.getHeight()) / 2;
		oppenent_pos_ = center;		
		DrawPixel(center.x, center.y, GetColor(0, 255, 0));
		//if(Vector2::Distance(pos, oppenent_pos_) <= 12)opponent_ = Opponent::FLOOR;
	}

	//if(other.)
}

void PlayerBody::changeMotion(float deltaTime){
}

void PlayerBody::move(KeyCode up, KeyCode down, KeyCode right, KeyCode left){
	if (distance() > PLAYER_MAX_STRETCH_LENGTH) {	}

	input_ = Vector2::Zero;
	if (InputMgr::GetInstance().IsKeyOn(right)) input_.x = 1;
	if (InputMgr::GetInstance().IsKeyOn(left)) 	input_.x = -1;
	if (InputMgr::GetInstance().IsKeyOn(up)) 	input_.y = -1;
	if (InputMgr::GetInstance().IsKeyOn(down)) 	input_.y = 1;
	
	//position_ += input_ * SPEED;
}

void PlayerBody::move_ver(KeyCode up, KeyCode down, KeyCode right, KeyCode left){
	if (distance() > PLAYER_MAX_STRETCH_LENGTH) {	}

	if (InputMgr::GetInstance().IsKeyOn(down))	input_.y = 1;
	if (InputMgr::GetInstance().IsKeyOn(up))	input_.y = -1;
}

void PlayerBody::move_hor(KeyCode right, KeyCode left){

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
}

void PlayerBody::sprit_move(KeyCode up, KeyCode down, KeyCode right, KeyCode left){
	input_ = Vector2::Zero;
	if (InputMgr::GetInstance().IsKeyOn(right)) input_.x = 1;
	if (InputMgr::GetInstance().IsKeyOn(left)) 	input_.x = -1;
	
	if (InputMgr::GetInstance().IsKeyDown(up)) 	jump_power_ = 30;

	gravity_ -= Vector2(0, 1) * jump_power_ - 0.01f;
}

void PlayerBody::chase() {
	if (target_ == nullptr || Vector2::Distance(Vector2::Zero, input_) > 0)return;
	if (distance() <= PLAYER_MAX_NORMAL_LENGTH) return;
	auto vec = Vector2::Normalize(position_ - target_->getPosition()) * PLAYER_MAX_NORMAL_LENGTH;
	position_ = Vector2::Lerp(position_, target_->getPosition() + vec, 0.2f);
}

void PlayerBody::gravity(){
	if (opponent_ == Opponent::FLOOR)gravity_ = Vector2(0, 5);
	else gravity_ = Vector2(0, 5);
}

void PlayerBody::acc_gravity(){

}

void PlayerBody::hold_gravity(){
	if (Vector2::Distance(Vector2::Zero, input_) > 0)return;
	gravity();
}

void PlayerBody::circleClamp() {
	if (distance() > PLAYER_MAX_STRETCH_LENGTH) {
		Vector2	vec = Vector2::Normalize(position_ - target_->getPosition());
		position_ = target_->getPosition() + vec * PLAYER_MAX_STRETCH_LENGTH;
	}
}

void PlayerBody::launch(Vector2 dir){
	launch_ = dir;
}

PlayerBody::Opponent PlayerBody::hitOpponent(){
	return opponent_;
}

void PlayerBody::reset_opponent(){
	opponent_ = Opponent::NONE;
}

void PlayerBody::reset_velocity(){
	input_ = Vector2::Zero;
}

void PlayerBody::pre_vector(){
	last_pos_ = position_;
}

float PlayerBody::distance(){
	return Vector2::Distance(position_, target_->getPosition());
}

void PlayerBody::target(std::shared_ptr<PlayerBody> target){
	target_ = target;
}

void PlayerBody::single_action(float deltaTime){
	stateMgr_.action(*this, deltaTime);
}

PlayerBody::SingleKeys PlayerBody::get_keys(){
	return keys_;
}


