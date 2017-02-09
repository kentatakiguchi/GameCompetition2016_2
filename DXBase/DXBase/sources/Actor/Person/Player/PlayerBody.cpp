#include "PlayerBody.h"

#include"../../Body/CollisionBase.h"

#include "PlayerBodyCollider.h"
#include "PlayerConnector.h"
#include "../../../Field/Field.h"

#include "../../../Game/Time.h"

#include "../../../Define.h"

#include <algorithm>

PlayerBody::PlayerBody() {}

PlayerBody::PlayerBody(IWorld * world, const std::string name, const Vector2 & position) :
	Actor(world, name, position, CollisionBase(Vector2(0, 0), PLAYER_RADIUS)),
	timer_(0),
	stiffness_(4.0f),
	friction_(0.1f),
	mass_(0.8f),
	stateMgr_(name),
	bodyDump_(1){
	change_state(PlayerState_Enum_Single::STAND_BY);

	auto collider = std::make_shared<PlayerBodyCollider>(world_, name_);
	world_->addActor(ActorGroup::Player_Collider, collider);
	collider_ = collider;

	// グラフィックのロード
	animation_ = PlayerAnimation2D(name_);
	animation_.change(PlayerAnimID::IDLE, 2.0f);

	alpha_ = 255;
}

PlayerBody::~PlayerBody() {
	StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_NOBI));
}

void PlayerBody::onUpdate(float deltaTime) {

	//position_ += velocity_;

	//velocity_ = (input_ * PLAYER_SPEED + launch_ + gravity_ + slope_ + collider_->other_velocity()) * deltaTime * static_cast<float>(GetRefreshRate());
	//slope_.Length() > 0 ? slope_ -= slope_ / 20 : slope_ = Vector2::Zero;

	//opponent_ = HitOpponent::NONE;

	animation_.update(deltaTime);

	if (!stateMgr_.currentState((unsigned int)PlayerState_Enum_Single::STAND_BY)) {

	}

	if (bodyDump_ != 1.0f) {
		dumpTimer_ += deltaTime * static_cast<float>(GetRefreshRate());
		if (dumpTimer_ >= 5.0f) {
			bodyDump_ = 1.0f;
			dumpTimer_ = 0;
			animation_.change(PlayerAnimID::IDLE);
		}
	}

}

void PlayerBody::onDraw() const {
	//DrawCircle((position_ * inv_).x, (position_ * inv_).y, PLAYER_RADIUS, GetColor(255, 255, 255), 0);

	//body_.draw(inv_);

	if (world_->isEntered())return;
	if (stateMgr_.currentState((unsigned int)PlayerState_Enum_Single::STAND_BY)) return;
	drawBody();
}

void PlayerBody::onCollide(Actor & other) {
	stateMgr_.collide(other);

	commonCollide(other);

	if (stateMgr_.get_state(PlayerState_Enum_Single::STAND_BY)) unionCollide(other);
}

void PlayerBody::hitField(const FieldPtr& field){
	//field->calcColl(position_, body_.GetCircle().previousPosition_, velocity_);
}

void PlayerBody::drawBody() const{
	stateMgr_.draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
	animation_.draw(position_ * inv_, Vector2::One * 128, 0.5f);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void PlayerBody::commonCollide(Actor & other){
	//if (stateMgr_.get_state(PlayerState_Enum_Single::IDLE) && name_ == "PlayerBody1")return;

	if (other.getName() == "MovelessFloor" || other.getName() == "SticklessFloor" ||
		other.getName() == "MoveFloorUpDown" || other.getName() == "MoveFloorRightLeft" ||
		other.getName() == "TurnFloor" || other.getName() == "TranslessTurnFloor" ||
		other.getName() == "Door" || other.getName() == "MovelessFloorBreak" ||
		other.getName() == "Tubo") {
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

		opponent_ = HitOpponent::FLOOR_HIT;

		if (top >= 0 && left <= 0 && right <= 0) {
			velocity_.y = 0;
			position_.y = t_left.y - PLAYER_RADIUS;
			opponent_ = HitOpponent::FLOOR_TOP;
		}
		else if (bottom >= 0 && left <= 0 && right <= 0) {
			velocity_.y = 0;
			position_.y = b_right.y + PLAYER_RADIUS;
		}
		else if (right >= 0 && top <= 0 && bottom <= 0) {
			velocity_.x = 0;
			position_.x = t_right.x + PLAYER_RADIUS;
		}
		else if (left >= 0 && top <= 0 && bottom <= 0) {
			velocity_.x = 0;
			position_.x = b_left.x - PLAYER_RADIUS;
		}
	}

	Vector2 myCenter, segCenter, segPoint, targetPoint, targetVec;
	float posReset;
	if (other.name_ == "SegmentCollider") {
		opponent_ = HitOpponent::FLOOR_TOP;

		//相手の線分の中心
		segCenter = other.position_;
		//自分の前の位置-相手の中心
		myCenter = body_.GetCircle().previousPosition_ - segCenter;
		//相手の中心から端へのベクトル(内積の計算に使う)
		segPoint = (other.body_.GetSegment().component_.point[1]) - segCenter;
		//正規化、内積のaの部分にする
		segPoint = segPoint.Normalize();
		//segpointをa、自分をbとして、内積の計算を行う
		posReset = (segPoint.x * myCenter.x) + (segPoint.y * myCenter.y);
		//内積の計算で求めた、中心点から自分の位置への長さを相手の線分の向きに補正する
		targetPoint = segPoint * posReset;
		//前の位置-
		targetVec = body_.GetCircle().previousPosition_ - (targetPoint + other.position_);

		targetVec = targetVec.Normalize();

		Vector2 posCenter = position_ - segCenter;
		Vector2 positionPoint = (segPoint)* ((segPoint.x * posCenter.x) + (segPoint.y * posCenter.y));

		Vector2 vec = other.body_.GetSegment().component_.point[0] - other.body_.GetSegment().component_.point[1];
		vec.y = std::abs(vec.y);
		Vector2 moves = position_ - body_.GetCircle().previousPosition_;
		position_ = (segCenter + positionPoint) + (targetVec * body_.GetCircle().component_.radius);
		if (moves.y > 0)position_ += vec.Normalize() * 50;

		//if (moves.y > 0)slope_ = SLIP_SPEED * (positionPoint - targetPoint).Normalize();
		//if (moves.y > 0)position_ += 40 * (positionPoint - targetPoint).Normalize();
		//if (moves.y > 0)slope_ = SLIP_SPEED * segPoint;
	}
}

void PlayerBody::unionCollide(Actor & other){
	if (other.getName() == "StageClearPoint") {
		hit_enemy_ = HitOpponent::CLEAR;
	}
	if (other.getName() == "BaseEnemy" || other.getName() == "GameOverPoint") {
		hit_enemy_ = HitOpponent::ENEMY;
	}
	if (other.getName() == "MiniBoss") {
		bodyDump_ = std::max<float>(bodyDump_ - 0.25f, 0.2f);
		dumpTimer_ = 0;
		animation_.change(PlayerAnimID::DIV_MOVE);
	}
	if (other.getName() == "Boss" || other.getName() == "FlinchBoss" ||
		other.getName() == "PiyoriBoss" || other.getName() == "BokoBoss") {
		hit_enemy_ = HitOpponent::BOSS;
	}
}

void PlayerBody::change_state(PlayerState_Enum_Single state) {
	stateMgr_.change(*this, state);
}

PlayerStateMgr_Single & PlayerBody::stateMgr(){
	return stateMgr_;
}

void PlayerBody::collider(){	
	collider_->position() = position_;
}

Vector2& PlayerBody::velocity() {
	return velocity_;
}

float & PlayerBody::dump(){
	return bodyDump_;
}

bool PlayerBody::able_to_hold() {
	return	collider_->opponent() == HitOpponent::FLOOR_HIT;
}

bool PlayerBody::able_to_jump() {
	return opponent_ == HitOpponent::FLOOR_TOP;
}

bool PlayerBody::is_hit() {
	return opponent_ == HitOpponent::FLOOR_TOP || opponent_ == HitOpponent::FLOOR_HIT;
}

HitOpponent PlayerBody::hitOpponent() {
	return opponent_;
}

HitOpponent PlayerBody::hit_enemy() {
	return hit_enemy_;
}

void PlayerBody::reset_opponent() {
	opponent_ = HitOpponent::NONE;
}

void PlayerBody::reset_enemy() {
	hit_enemy_ = HitOpponent::NONE;
}

void PlayerBody::reset_slope() {
	slope_ = Vector2::Zero;
}

float PlayerBody::distance() {
	return Vector2::Distance(position_, partner_->getPosition());
}

void PlayerBody::set_partner(PlayerBodyPtr partner) {
	partner_ = partner;
}

void PlayerBody::set_hold_point() {
	position_ = collider_->other_position() + (position_ - collider_->other_position()).Normalize() + CHIPSIZE / 2;
	collider_->reset_pos();
}

void PlayerBody::single_action(float deltaTime) {
	stateMgr_.action(*this, deltaTime);
}

Vector2 PlayerBody::get_partner_vector() {
	return (partner_->getPosition() - position_).Normalize();
}

Vector2& PlayerBody::hit_vector(){
	return collider_->other_velocity();
}

PlayerAnimation2D & PlayerBody::animation() {
	return animation_;
}

void PlayerBody::ForcedMove(Vector2 velocity) {
	position_ += velocity*Time::GetInstance().deltaTime();
}


