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

	stateMgr_.add((unsigned int)PlayerState_Enum_Single::STAND_BY, std::make_shared<PlayerState_Single_StandBy>(std::shared_ptr<PlayerBody>(this)));
	stateMgr_.add((unsigned int)PlayerState_Enum_Single::LEAN_BACK, std::make_shared<PlayerState_Single_LeanBack>(std::shared_ptr<PlayerBody>(this)));
	stateMgr_.add((unsigned int)PlayerState_Enum_Single::IDLE, std::make_shared<PlayerState_Single_Idle>(std::shared_ptr<PlayerBody>(this)));
	stateMgr_.add((unsigned int)PlayerState_Enum_Single::JUMP, std::make_shared<PlayerState_Single_Jump>(std::shared_ptr<PlayerBody>(this)));
	init_state();

	auto collider = std::make_shared<PlayerBodyCollider>(world_, name_, (PlayerBodyPtr)this);
	world_->addActor(ActorGroup::Player_Collider, collider);
	collider_ = collider;


	// グラフィックのロード
	animation_ = Animation2D(ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_PUYOTA), 3, 3);
}

PlayerBody::~PlayerBody(){}

void PlayerBody::onUpdate(float deltaTime){
	position_ += (input_ * PLAYER_SPEED  + launch_ + gravity_ + other_velocity_) * deltaTime * static_cast<float>(GetRefreshRate());
	velocity_ = position_ - body_.GetCircle().previousPosition_;

	opponent_ = HitOpponent::NONE;

	draw_pos_ = Vector3(position_.x, position_.y) * inv_;

	animation_.update(deltaTime);

}

void PlayerBody::onDraw() const{
	body_.draw(inv_);

	SetFontSize(32);
	DrawFormatString(draw_pos_.x, draw_pos_.y, GetColor(255,255,255), "%f", dead_limit_);

	animation_.draw(Vector2(draw_pos_.x, draw_pos_.y), Vector2::One * 48, 2);
}

void PlayerBody::onLateUpdate(float deltaTime){
	collider_->pos_update();
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
		hit_enemy_ = HitOpponent::ENEMY;
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
	stateMgr_.changeState(IState::StateElement((unsigned int)PlayerState_Enum_Single::STAND_BY));
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

void PlayerBody::circleClamp() {
	if (distance() > PLAYER_MAX_STRETCH_LENGTH) {
		Vector2	vec = Vector2::Normalize(position_ - partner_->getPosition());
		position_ = partner_->getPosition() + vec * PLAYER_MAX_STRETCH_LENGTH;
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

void PlayerBody::reset_enemy()
{
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
	stateMgr_.action(deltaTime);
}

PlayerBody::SingleKeys PlayerBody::get_keys(){
	return keys_;
}

Vector2 PlayerBody::get_partner_vector(){
	return (partner_->getPosition() - position_).Horizontal().Normalize();
}

void PlayerBody::create_attack_collider_(){
	//auto collider = std::make_shared<PlayerBodyCollider>(world_, std::string("PlayerAttack"), (PlayerBodyPtr)this);
	//world_->addActor(ActorGroup::Player_AttackRange, collider);
	//attack_collider_ = collider;
}

void PlayerBody::delete_attack_collider_(){
	//attack_collider_->dead();
}

void PlayerBody::reset_dead_limit(){
	dead_limit_ = 0;
}

void PlayerBody::count_dead_limit(float deltaTime) {
	if (stateMgr_.currentState((unsigned int)PlayerState_Enum_Single::STAND_BY) ||
		stateMgr_.currentState((unsigned int)PlayerState_Enum_Single::LEAN_BACK))return;
		dead_limit_ += deltaTime;
}


