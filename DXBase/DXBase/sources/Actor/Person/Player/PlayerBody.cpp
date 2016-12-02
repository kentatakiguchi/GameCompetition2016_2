#include "PlayerBody.h"

#include"../../Body/CollisionBase.h"

//#include "State/States/State_Dammy.h"
#include "State/States/Single/Elements/PlayerState_Single_StandBy.h"
#include "State/States/Single/Elements/PlayerState_Single_LeanBack.h"
#include "State/States/Single/Elements/PlayerState_Single_Idle.h"
#include "State/States/Single/Elements/PlayerState_Single_Jump.h"

#include "PlayerBodyCollider.h"

PlayerBody::PlayerBody(){}

PlayerBody::PlayerBody(IWorld * world, const std::string name, const Vector2 & position) :
	Actor(world, name, position, CollisionBase(Vector2(0, 0), PLAYER_RADIUS)),
	is_single_(false),
	dead_limit_(0){
	keys_ = SingleKeys();
	if (name == "PlayerBody2")keys_ = SingleKeys(KeyCode::W, KeyCode::S, KeyCode::D, KeyCode::A);

	stateMgr_.add((unsigned int)PlayerState_Enum_Single::STAND_BY, std::make_shared<PlayerState_Single_StandBy>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Single::LEAN_BACK, std::make_shared<PlayerState_Single_LeanBack>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Single::IDLE, std::make_shared<PlayerState_Single_Idle>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Single::JUMP, std::make_shared<PlayerState_Single_Jump>());
	init_state();

	auto collider = std::make_shared<PlayerBodyCollider>(world_, name_);
	world_->addActor(ActorGroup::Player_Collider, collider);
	collider_ = collider;

	// グラフィックのロード
	animation_ = PlayerAnimation2D();
	animation_.add(PlayerAnimID::IDLE, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_BUTTY_IDLE), 256, 8, 4, 1);
	animation_.change(PlayerAnimID::IDLE, 2.0f);
}

PlayerBody::~PlayerBody(){}

void PlayerBody::onUpdate(float deltaTime){
	position_ += (input_ * PLAYER_SPEED  + launch_ + gravity_ + collider_->other_velocity()) * deltaTime * static_cast<float>(GetRefreshRate());
	velocity_ = position_ - body_.GetCircle().previousPosition_;

	opponent_ = HitOpponent::NONE;

	draw_pos_ = position_ * inv_;

	animation_.update(deltaTime);
}

void PlayerBody::onDraw() const{
	body_.draw(inv_);

	SetFontSize(32);
	DrawFormatString(static_cast<int>(draw_pos_.x) + 30, static_cast<int>(draw_pos_.y), GetColor(255,255,255), "%f", dead_limit_);
	
	Vector3 color = Vector3::Zero;
	if (name_ == "PlayerBody1")color = Vector3(255, 255, 255);
	if (name_ == "PlayerBody2")color = Vector3(255, 255, 255);
	animation_.draw(draw_pos_, Vector2::One * 128, 0.5f, 0, color, ActionType::Right);
}

void PlayerBody::onLateUpdate(float deltaTime){
	collider_->pos_update(position_);
	if(attack_collider_ != nullptr)attack_collider_->pos_update(position_);
	input_ = Vector2::Zero;
	gravity_ = Vector2::Zero;
	launch_ = Vector2::Zero;
}

void PlayerBody::onCollide(Actor & other){
	
	if (other.getName() == "MovelessFloor" || other.getName() == "SticklessFloor" || 
		other.getName() == "MoveFloorUpDown" || other.getName() == "MoveFloorRightLeft" || 
		other.getName() == "TurnFloor" || other.getName() == "TranslessTurnFloor") {
		auto pos = body_.GetCircle().previousPosition_;

		auto t_left =  other.getBody().GetBox().component_.point[0];
		auto t_right = other.getBody().GetBox().component_.point[1];
		auto b_left = other.getBody().GetBox().component_.point[2];
		auto b_right = other.getBody().GetBox().component_.point[3];
		
		auto center = t_left + other.getBody().GetBox().getSize() / 2;

		auto top    = Vector2::Cross((t_left - t_right).Normalize(), (pos - t_right));
		auto right  = Vector2::Cross((t_right - b_right).Normalize(), (pos - b_right));
		auto bottom = Vector2::Cross((b_right - b_left).Normalize(), (pos - b_left));
		auto left = Vector2::Cross((b_left - t_left).Normalize(), (pos - t_left));

		opponent_ = HitOpponent::FLOOR_HIT;

		if (top >= 0 && left <= 0 && right <= 0) {
			position_.y = t_left.y - PLAYER_RADIUS;
			opponent_ = HitOpponent::FLOOR_TOP;
		}
		if (bottom >= 0 && left <= 0 && right <= 0) {
			position_.y = b_right.y + PLAYER_RADIUS;
		}
		if (right >= 0 && top <= 0 && bottom <= 0) {
			position_.x = t_right.x + PLAYER_RADIUS;
		}
		if (left >= 0 && top <= 0 && bottom <= 0) {
			position_.x = b_left.x - PLAYER_RADIUS;
		}
		if (left <= 0 && right <= 0 && top <= 0 && bottom <= 0) {
			Vector2 vec = (pos - center).Normalize();
			position_ = center + vec * (t_left - center).Length();
			if(vec.Length() <= 0) position_ = center + Vector2::Down * (t_left - center).Length();
		}
	}
	if (other.getName() == "StageClearPoint") {
		hit_enemy_ = HitOpponent::CLEAR;
	}
	if (other.getName() == "BaseEnemy" || other.getName() == "GameOverPoint") {
		if (stateMgr_.currentState((unsigned int)PlayerState_Enum_Single::STAND_BY)) {
			hit_enemy_ = HitOpponent::ENEMY;
			dead_limit_ = 0;
		}
	}

	if ((getName() == "PlayerBody1" && other.getName() == "PlayerBody2Collider") ||
		(getName() == "PlayerBody2" && other.getName() == "PlayerBody1Collider")) {
		if (stateMgr_.currentState((unsigned int)PlayerState_Enum_Single::IDLE) ||
			stateMgr_.currentState((unsigned int)PlayerState_Enum_Single::JUMP)) {
			hit_partner_ = HitOpponent::PARTNER;
		}
	}
}

void PlayerBody::init_state(){
	stateMgr_.changeState(*this, IState::StateElement((unsigned int)PlayerState_Enum_Single::STAND_BY));
}

void PlayerBody::move(Vector2 vector){
	if (distance() >= PLAYER_MAX_STRETCH_LENGTH && stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::STAND_BY)) return;
	
	input_ = vector;
}

void PlayerBody::move_hold(Vector2 vector){
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
	if (partner_ == nullptr || Vector2::Distance(Vector2::Zero, input_) > 0)return;
	if (distance() <= PLAYER_MAX_NORMAL_LENGTH) return;
	auto vec = Vector2::Normalize(position_ - partner_->getPosition()) * PLAYER_MAX_NORMAL_LENGTH;
	position_ = Vector2::Lerp(position_, partner_->getPosition() + vec, 0.3f);
}

void PlayerBody::gravity(){
	if (opponent_ == HitOpponent::FLOOR_TOP)gravity_ = Vector2(0, 9.8f);
	else gravity_ = Vector2(0, 9.8f);
}

void PlayerBody::acc_gravity(){

}

bool PlayerBody::able_to_hold(){
	return	collider_->opponent() == HitOpponent::FLOOR_HIT;
}

bool PlayerBody::able_to_jump() {
	return opponent_ == HitOpponent::FLOOR_TOP;
}

bool PlayerBody::is_hit(){
	return opponent_ == HitOpponent::FLOOR_TOP || opponent_ == HitOpponent::FLOOR_HIT;
}

void PlayerBody::hold_gravity(){
	if (Vector2::Distance(Vector2::Zero, input_) <= 0)gravity();
}

void PlayerBody::circleClamp(Vector2 target) {
	float distance = (target - position_).Length();
	if (distance > PLAYER_MAX_STRETCH_LENGTH / PLAYER_CNTR_DIV_NUM) {
		Vector2	vec = Vector2::Normalize(position_ - target);
		position_ = target + vec * PLAYER_MAX_STRETCH_LENGTH / PLAYER_CNTR_DIV_NUM;
	}
}

void PlayerBody::launch(Vector2 dir){
	launch_ = dir;
}

HitOpponent PlayerBody::hitOpponent(){
	return opponent_;
}

HitOpponent PlayerBody::hit_partner(){
	return hit_partner_;
}

HitOpponent PlayerBody::hit_enemy()
{
	return hit_enemy_;
}

void PlayerBody::reset_opponent(){
	opponent_ = HitOpponent::NONE;
}

void PlayerBody::reset_partner(){
	hit_partner_ = HitOpponent::NONE;
}

void PlayerBody::reset_enemy(){
	hit_enemy_ = HitOpponent::NONE;

}

void PlayerBody::reset_velocity(){
	input_ = Vector2::Zero;
}

float PlayerBody::distance(){
	return Vector2::Distance(position_, partner_->getPosition());
}

void PlayerBody::set_partner(PlayerBodyPtr partner){
	partner_ = partner;
}

void PlayerBody::set_hold_point(){
	position_ = collider_->other_position() + (position_ - collider_->other_position()).Normalize() + CHIPSIZE / 2 ;
	collider_->reset_pos();
}

PlayerBodyPtr PlayerBody::get_partner(){
	return partner_;
}

bool PlayerBody::isDead(){
	return dead_limit_ >= PLAYER_DEAD_LIMIT;
}

bool PlayerBody::isInv(){
	return dead_limit_ <= PLAYER_INV_TIME;
}

void PlayerBody::single_action(float deltaTime){
	stateMgr_.action(*this, deltaTime);
}

PlayerBody::SingleKeys PlayerBody::get_keys(){
	return keys_;
}

Vector2 PlayerBody::get_partner_vector(){
	return (partner_->getPosition() - position_).Horizontal().Normalize();
}

void PlayerBody::create_attack_collider_(){
	auto collider = std::make_shared<PlayerBodyCollider>(world_, std::string("PlayerAttack"));
	world_->addActor(ActorGroup::Player_Collider, collider);
	attack_collider_ = collider;
}

void PlayerBody::delete_attack_collider_(){
	attack_collider_->dead();
}

void PlayerBody::reset_dead_limit(){
	dead_limit_ = 0;
}

void PlayerBody::count_dead_limit(float deltaTime) {
	if (stateMgr_.currentState((unsigned int)PlayerState_Enum_Single::STAND_BY) ||
		stateMgr_.currentState((unsigned int)PlayerState_Enum_Single::LEAN_BACK))return;
		dead_limit_ += deltaTime;
}


