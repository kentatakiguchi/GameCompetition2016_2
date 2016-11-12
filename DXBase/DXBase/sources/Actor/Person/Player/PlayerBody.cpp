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
	init_state();

	other_ = "";
}

PlayerBody::~PlayerBody(){}

void PlayerBody::onUpdate(float deltaTime){
	position_ += input_ * PLAYER_SPEED  + launch_ + gravity_ * deltaTime * static_cast<float>(GetRefreshRate());
	velocity_ = position_ - body_.GetCircle().previousPosition_;

	isOnFloor_ = false;
}

void PlayerBody::onDraw() const{
	body_.draw(inv_);
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

		if (top >= 0 && left <= 0 && right <= 0) {
			position_.y = t_left.y - (body_.GetCircle().component_.radius + 5);
		}
		if (bottom >= 0 && left <= 0 && right <= 0) {
			position_.y = b_right.y + (body_.GetCircle().component_.radius + 5);
		}
		if (right >= 0 && top <= 0 && bottom <= 0) {
			position_.x = t_right.x + (body_.GetCircle().component_.radius + 5);
		}
		if (left >= 0 && top <= 0 && bottom <= 0) {
			position_.x = b_left.x - (body_.GetCircle().component_.radius + 5);
		}

		isOnFloor_ = true;
	}
	if (other.getName() == "NavChip" && !isOnFloor_) {
		auto pos = body_.GetCircle().previousPosition_;

		auto box = other.getBody().GetBox();
		Vector2 center = box.component_.point[0] + Vector2(box.getWidth(), box.getHeight()) / 2;
		oppenent_pos_ = center;		
		DrawPixel(center.x, center.y, GetColor(0, 255, 0));
		//if(Vector2::Distance(pos, oppenent_pos_) <= 12)opponent_ = Opponent::FLOOR;
	}

	if (other.getName() == "BaseEnemy") {
		opponent_ = Opponent::ENEMY;
	}

	if (other.getName() == "PlayerBody2")/* ||
		(name_ == "PlayerBody2" && other.getName() == "PlayerBody1")*/ {
		/*if()*/ opponent_ = Opponent::PARTNER;
	}

	//if (this == nullptr)return;
	other_ = other.getName().c_str();

}

void PlayerBody::init_state(){
	stateMgr_.changeState(*this, IState::StateElement((unsigned int)PlayerState_Enum_Single::STAND_BY));
}

void PlayerBody::move(Vector2 vector){
	if (distance() >= PLAYER_MAX_STRETCH_LENGTH && stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::STAND_BY)) return;
	
	input_ = vector;
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
	position_ = Vector2::Lerp(position_, target_->getPosition() + vec, 0.3f);
}

void PlayerBody::gravity(){
	if (isOnFloor_)gravity_ = Vector2(0, 9.8f);
	else gravity_ = Vector2(0, 9.8f);
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

bool PlayerBody::isOnFloor()
{
	return isOnFloor_;
}

bool PlayerBody::isDead(){
	return dead_limit_ >= PLAYER_DEAD_LIMIT;
}

void PlayerBody::single_action(float deltaTime){
	stateMgr_.action(*this, deltaTime);
}

PlayerBody::SingleKeys PlayerBody::get_keys(){
	return keys_;
}


