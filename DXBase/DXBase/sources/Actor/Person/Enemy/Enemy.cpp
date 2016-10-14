#include "Enemy.h"

#include "../../../ResourceLoader/ResourceLoader.h"
#include"../../Body/CollisionBase.h"
#include "../../Base/ActorGroup.h"
#include "Enemy_AttackRange.h"
#include <algorithm>

Enemy::Enemy(IWorld * world, const Vector3 & position) :
	Actor(world, "Enemy", position, CollisionBase()){
	// モデルの読み込み
	modelHandle_ = MV1DuplicateModel(ResourceLoader::GetInstance().getModelID(ModelID::ENEMY));

	animation_ = Animation(modelHandle_);

	//初期状態を正面に設定
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), 0);
	rotation_.NormalizeRotationMatrix();

	setPos();
	alpha_ = 255;
	changeState(State::INIT, ENEMY_IDLE);
}

Enemy::~Enemy(){
}

void Enemy::onUpdate(float deltaTime){
	updateState(deltaTime);

	animation_.changeAnim(motion_);
	animation_.update(deltaTime);


	MV1SetMatrix(modelHandle_, Matrix::MatrixToMATRIX(getPose()));
}

void Enemy::onDraw() const{
	SetDrawAlphaTest(DX_CMP_GREATER, 0);
	MV1SetOpacityRate(modelHandle_, alpha_ / 255.0f);
	// プレイヤーモデルの描画
	MV1DrawModel(modelHandle_);
}

void Enemy::onCollide(Actor & actor){
	if (actor.getName() == "Player_AttackRange") {
		changeState(State::DAMAGE, ENEMY_DAMAGE);
		body_.enabled(false);
	}
}

void Enemy::onMessage(EventMessage event, void *){
}

void Enemy::updateState(float deltaTime){
	switch (state_) {
	case State::INIT:init(); break;
	case State::IDLE:idle(deltaTime); break;
	case State::MOVE:move(deltaTime); break;
	case State::CHASE:chase(deltaTime); break;
	case State::ATTACK:attack(deltaTime); break;
	case State::DAMAGE:damage(deltaTime); break;
	};
	stateTimer_ += deltaTime;
	timer_ += deltaTime;

	position_ = Vector3::Clamp(position_, Vector3::Zero, Vector3::One * 1000 * 5);
}

void Enemy::changeState(State state, unsigned int motion){
	motion_ = motion;
	state_ = state;
	stateTimer_ = 0.0f;
}

void Enemy::init() {
	alpha_ = std::min<float>(alpha_ + stateTimer_ * 2, 255.0f);

	if (animation_.isAnimEnd()) {
		changeState(State::MOVE, ENEMY_IDLE);
	}
}

void Enemy::idle(float deltaTime){
	if (animation_.isAnimEnd())
	{
		body_.enabled(true);
		changeState(State::MOVE, ENEMY_WALK);
	}
}

void Enemy::move(float deltaTime){
	auto player = world_->findActor("Player");
	if (player == nullptr) return;

	target_ = player->getPosition();

	Vector3 to_target = target_ - position_;
	
	if (to_target.Length() <= 100)changeState(State::CHASE, ENEMY_WALK);
}

void Enemy::chase(float deltaTime){
	auto player = world_->findActor("Player");
	if (player == nullptr) return;

	target_ = player->getPosition();

	rotation_.NormalizeRotationMatrix();

	Vector3 to_target = target_ - position_;
	Vector3 forward_cross_target = Vector3::Cross(rotation_.Forward(), to_target);
	float forward_dot_target = Vector3::Dot(rotation_.Forward(), to_target);
	float up_dot_cross = Vector3::Dot(rotation_.Up(), forward_cross_target);
	float angle = Vector3::Angle(rotation_.Forward(), to_target);

	float yaw = std::min<float>(2.0f, angle);
	yaw = (up_dot_cross >= 0.0f) ? yaw : -yaw;
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), yaw);
	position_ += rotation_.Forward() * 0.5f;

	if (to_target.Length() <= 20)changeState(State::ATTACK, ENEMY_ATTACK);

	if (to_target.Length() > 100)changeState(State::MOVE, ENEMY_IDLE);
}

void Enemy::attack(float deltaTime){
	if (animation_.isAnimEnd()) {
		world_->addActor(ActorGroup::Enemy_AttackRange, std::make_shared<Enemy_AttackRange>(world_, position_));

		changeState(State::IDLE, ENEMY_IDLE);
	}
}

void Enemy::damage(float deltaTime){	
	alpha_ = std::max<float>(alpha_ - stateTimer_, 0);
	if (animation_.isAnimEnd()) {
		setPos();
		changeState(State::INIT, ENEMY_IDLE);		
	}
}

void Enemy::setPos(){
	int width = GetRand(25);
	int depth = GetRand(25);

	position_ = Vector3(-100.0f * width, 0.0f, -100.0f * depth);
}

