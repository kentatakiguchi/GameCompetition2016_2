#include "PlayerBody.h"

#include"../../Body/CollisionBase.h"

#include "PlayerBodyCollider.h"
#include "PlayerConnector.h"

#include "Effect/PlayerEffectObj.h"

PlayerBody::PlayerBody() {}

PlayerBody::PlayerBody(IWorld * world, const std::string name, const Vector2 & position) :
	Actor(world, name, position, CollisionBase(Vector2(0, 0), PLAYER_RADIUS)),
	dead_limit_(0),
	stiffness_(3.0f),
	friction_(0.1f),
	mass_(0.8f),
	stateMgr_(name) {

	change_state(PlayerState_Enum_Single::STAND_BY);

	auto collider = std::make_shared<PlayerBodyCollider>(world_, name_);
	world_->addActor(ActorGroup::Player_Collider, collider);
	collider_ = collider;

	// グラフィックのロード
	animation_ = PlayerAnimation2D(name_);
	animation_.change(PlayerAnimID::IDLE, 2.0f);
}

PlayerBody::~PlayerBody() {}

void PlayerBody::onUpdate(float deltaTime) {
	position_ += (input_ * PLAYER_SPEED + launch_ + gravity_ + slope_ + collider_->other_velocity()) * deltaTime * static_cast<float>(GetRefreshRate());
	velocity_ = position_ - body_.GetCircle().previousPosition_;

	slope_.Length() > 0 ? slope_ -= slope_ / 20 : slope_ = Vector2::Zero;

	opponent_ = HitOpponent::NONE;

	animation_.update(deltaTime);

	if (InputMgr::GetInstance().IsKeyOn(KeyCode::Z))stiffness_ += 0.01f;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::X))stiffness_ -= 0.01f;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::C))friction_ += 0.01f;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::V))friction_ -= 0.01f;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::B))mass_ += 0.01f;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::N))mass_ -= 0.01f;

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::M)) {
		stiffness_ = 3.0f;
		friction_ = 0.1f;
		mass_ = 0.8f;
	}
}

void PlayerBody::onDraw() const {
	body_.draw(inv_);

	SetFontSize(32);
	DrawFormatString(static_cast<int>((position_ * inv_).x) + 30, static_cast<int>((position_ * inv_).y), GetColor(255, 255, 255), "%f", dead_limit_);

	DrawFormatString(100, 900, GetColor(0, 0, 0), "剛性 : %f", stiffness_);
	DrawFormatString(100, 950, GetColor(0, 0, 0), "摩擦 : %f", friction_);
	DrawFormatString(100, 1000, GetColor(0, 0, 0), "質量 : %f", mass_);

	Vector3 color = Vector3::Zero;
	if (name_ == "PlayerBody1")color = Vector3(255, 255, 255);
	if (name_ == "PlayerBody2")color = Vector3(255, 255, 255);
	animation_.draw(position_ * inv_, Vector2::One * 128, 0.5f, 0, color);
}

void PlayerBody::onLateUpdate(float deltaTime) {
	collider_->pos_update(position_);
	if (attack_collider_ != nullptr)attack_collider_->pos_update(position_);
	input_ = Vector2::Zero;
	gravity_ = Vector2::Zero;
	launch_ = Vector2::Zero;
}

void PlayerBody::onCollide(Actor & other) {
	if (other.getName() == "MovelessFloor" || other.getName() == "SticklessFloor" ||
		other.getName() == "MoveFloorUpDown" || other.getName() == "MoveFloorRightLeft" ||
		other.getName() == "TurnFloor" || other.getName() == "TranslessTurnFloor" ||
		other.getName() == "Door") {
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
			if (vec.Length() <= 0) position_ = center + Vector2::Down * (t_left - center).Length();
		}
	}
	if (other.getName() == "StageClearPoint") {
		hit_enemy_ = HitOpponent::CLEAR;
	}
	if (other.getName() == "BaseEnemy" || other.getName() == "GameOverPoint") {
		if (stateMgr_.get_state(PlayerState_Enum_Single::STAND_BY)) {
			hit_enemy_ = HitOpponent::ENEMY;
			dead_limit_ = 0;
		}
	}

	if ((getName() == "PlayerBody1" && other.getName() == "PlayerBody2Collider") ||
		(getName() == "PlayerBody2" && other.getName() == "PlayerBody1Collider")) {
		if (stateMgr_.get_state(PlayerState_Enum_Single::IDLE) || 
			stateMgr_.get_state(PlayerState_Enum_Single::MOVE) || 
			stateMgr_.get_state(PlayerState_Enum_Single::JUMP)) {
			hit_partner_ = HitOpponent::PARTNER;
		}
	}

	Vector2 myCenter, segCenter, segPoint, targetPoint, targetVec;
	float posReset;
	if (other.name_ == "SegmentCollider") {
		//線分はpositionを中心に取る
		//Vector2 myCenter = Vector2(previousPosition.x,previousPosition.y);
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
		Vector2 positionPoint = (segPoint)* ((segPoint.x*posCenter.x) + (segPoint.y*posCenter.y));

		position_ = (segCenter + positionPoint) + (targetVec*body_.GetCircle().component_.radius);

		Vector2 moves = position_ - body_.GetCircle().previousPosition_;

		if (moves.y > 0)slope_ = SLIP_SPEED * ((segCenter + positionPoint) - (segCenter + targetPoint));
	}
}

void PlayerBody::change_state(PlayerState_Enum_Single state) {
	stateMgr_.change(*this, state);
}

void PlayerBody::move(Vector2 vector) {
	input_ = vector;
}

void PlayerBody::chase() {
	if (partner_ == nullptr || Vector2::Distance(Vector2::Zero, input_) > 0)return;
	auto cntr = std::dynamic_pointer_cast<PlayerConnector>(world_->findActor("PlayerConnector"));
	if (cntr == nullptr)return;
	//if (cntr->length_sum() <= PLAYER_MAX_NORMAL_LENGTH)return;
	if (name_ == "PlayerBody1"/* && (position_ - cntr->get_point(0)).Length() > PLAYER_MIN_DIV_LENGTH*/) {
		Vector2::Spring(position_, cntr->get_point(0), v_, stiffness_, friction_, mass_);
	}
	if (name_ == "PlayerBody2"/* && (position_ - cntr->get_point(PLAYER_CNTR_DIV_NUM - 1)).Length() > PLAYER_MIN_DIV_LENGTH*/) {
		Vector2::Spring(position_, cntr->get_point(PLAYER_CNTR_DIV_NUM - 1), v_, stiffness_, friction_, mass_);
	}
}

void PlayerBody::gravity() {
	if (opponent_ == HitOpponent::FLOOR_TOP)gravity_ = Vector2(0, 0);
	else gravity_ = Vector2(0, 9.8f);
}

void PlayerBody::acc_gravity() {

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

void PlayerBody::hold_gravity() {
	if (Vector2::Distance(Vector2::Zero, input_) <= 0)gravity();
}

void PlayerBody::clamp() {
	auto cntr = std::dynamic_pointer_cast<PlayerConnector>(world_->findActor("PlayerConnector"));
	if (cntr == nullptr)return;
	if (name_ == "PlayerBody1") position_ = Vector2::ClampTarget(position_, cntr->get_point(0), PLAYER_MAX_DIV_LENGTH);
	if (name_ == "PlayerBody2") position_ = Vector2::ClampTarget(position_, cntr->get_point(PLAYER_CNTR_DIV_NUM - 1), PLAYER_MAX_DIV_LENGTH);
}

void PlayerBody::launch(Vector2 dir) {
	launch_ = dir;
}

HitOpponent PlayerBody::hitOpponent() {
	return opponent_;
}

HitOpponent PlayerBody::hit_partner() {
	return hit_partner_;
}

HitOpponent PlayerBody::hit_enemy() {
	return hit_enemy_;
}

void PlayerBody::reset_opponent() {
	opponent_ = HitOpponent::NONE;
}

void PlayerBody::reset_partner() {
	hit_partner_ = HitOpponent::NONE;
}

void PlayerBody::reset_enemy() {
	hit_enemy_ = HitOpponent::NONE;
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

bool PlayerBody::dead_limit() {
	return dead_limit_ >= PLAYER_DEAD_LIMIT;
}

bool PlayerBody::isInv() {
	return dead_limit_ <= PLAYER_INV_TIME;
}

void PlayerBody::single_action(float deltaTime) {
	stateMgr_.action(*this, deltaTime);
}

Vector2 PlayerBody::get_partner_vector() {
	return (partner_->getPosition() - position_).Horizontal().Normalize();
}

void PlayerBody::create_attack_collider_() {
	auto collider = std::make_shared<PlayerBodyCollider>(world_, std::string("PlayerAttack"));
	world_->addActor(ActorGroup::Player_Collider, collider);
	attack_collider_ = collider;
}

void PlayerBody::delete_attack_collider_() {
	attack_collider_->dead();
}

void PlayerBody::reset_dead_limit() {
	dead_limit_ = 0;
}

void PlayerBody::count_dead_limit(float deltaTime) {
	if (stateMgr_.get_state(PlayerState_Enum_Single::STAND_BY) || stateMgr_.get_state(PlayerState_Enum_Single::LEAN_BACK))return;
	dead_limit_ += deltaTime;
}

PlayerAnimation2D & PlayerBody::animation() {
	return animation_;
}


