#include "BaseEnemy.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include "Enemy_AttackRange.h"

BaseEnemy::BaseEnemy(IWorld * world, const Vector3& position) :
	Actor(world, "BaseEnemy", position, BoundingSphere(1.0f)),
	hp_(10),
	ap_(0),
	speed_(0.3f),
	color_(GetColor(255, 255, 255)),
	stateTimer_(0.0f),
	state_(State::Idel),
	animation_(),
	player_(nullptr)
{
}

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::onUpdate(float deltaTime)
{
	// 状態の更新
	updateState(deltaTime);
	// アニメーションの変更
	//animation_.change(motion_);
	// アニメーションの更新
	//animation_.update(deltaTime);
}

void BaseEnemy::onDraw() const
{
	//auto vec2Position = Vector2(position_.x, position_.y);
	//animation_.draw(vec2Position, NULL, 1.0f, 0.0f);
	//DrawRotaGraph2(position_.x, position_.y, 0.5f, 0.5f, 0.0f, 0.0f, 1, 1);
	DrawSphere3D(Vector3::Vector3ToVECTOR(position_), 1.0f, 16, color_, GetColor(0, 0, 0), 1);
}

void BaseEnemy::onCollide(Actor & actor)
{
	if (actor.getName() != "Player_AttackRange" || actor.getName() != "Player") return;
	// ダメージ
	// hp_ -= player->GetAP(); とか
	hp_ -= 10;
	if (hp_ <= 0) changeState(State::Dead, ENEMY_DEAD);
	else changeState(State::Damage, ENEMY_DAMAGE);
	body_.enabled = false;
}

void BaseEnemy::onMessage(EventMessage event, void *)
{
}

void BaseEnemy::idle()
{
	color_ = GetColor(255, 255, 255);
	//position_ += BaseEnemy::playerNormalizeDirection() * -speed_;
	if (playerLength() < 100) changeState(State::Search, ENEMY_WALK);
}
// 索敵移動します(デフォルト)
void BaseEnemy::searchMove()
{
	// プレイヤーの捜索
	findPlayer();
	color_ = GetColor(0, 255, 0);
	// 一定距離内なら追跡する
	if (playerLength() <= 10) changeState(State::Chase, ENEMY_WALK);
	else if(playerLength() >= 100) changeState(State::Idel, ENEMY_IDLE);
}
// プレイヤーを追跡します(デフォルト)
void BaseEnemy::chaseMove()
{
	// プレイヤーの捜索
	findPlayer();
	color_ = GetColor(255, 0, 0);
	if (playerLength() > 10) changeState(State::Search, ENEMY_WALK);
	// 前方に移動(仮)
	//auto distance = position_ - player_->getPosition();
	////auto direction = 1.0f;
	//if (distance.x < 0)
	//	direction_ = -1;
	//else if(distance.x > 0) direction_ = 1;
	//else direction_ = 0;

	//// 水平方向に移動
	//position_ += position_.Left * -speed_ * playerDirection().x;
	//// 移動
	//position_ += BaseEnemy::playerNormalizeDirection() * -speed_;
}

//void BaseEnemy::shortDistanceAttack()
//{
//}
//
//void BaseEnemy::centerDistanceAttack()
//{
//}
//
//void BaseEnemy::longDistanceAttack()
//{
//}

void BaseEnemy::Attack()
{
	/*world_->addActor(
		ActorGroup::Enemy_AttackRange, std::make_shared<Enemy_AttackRange>(world_, position_));*/
	if (stateTimer_ >= 3.0f)
		changeState(State::Search, ENEMY_IDLE);
}

void BaseEnemy::damageMove()
{
	color_ = GetColor(100, 100, 100);
	if (stateTimer_ >= 3.0f)
		changeState(State::Chase, ENEMY_WALK);
}

void BaseEnemy::deadMove()
{
	//if (stateTimer_ >= 3.0f) dead();
}

void BaseEnemy::changeState(State state, unsigned int motion)
{
	state_ = state;
	stateTimer_ = 0.0f;
	motion_ = motion;
}

void BaseEnemy::findPlayer()
{
	// プレイヤーがいなければ待機状態
	if (player_ == nullptr) {
		changeState(State::Idel, ENEMY_IDLE);
		return;
	}
}

// プレイヤーとの距離を返します
float BaseEnemy::playerLength()
{
	// プレイヤーの位置を取得
	Vector3 target = player_->getPosition();
	target_ = Vector2(target.x, target.y);
	Vector2 vec2Position_ = Vector2(position_.x, position_.y);
	Vector2 length = target_ - vec2Position_;
	return length.Length();
}

// プレイヤーとの方向を単位ベクトルで取得します
Vector2 BaseEnemy::playerDirection()
{
	// 方向の計算
	auto distance = position_ - player_->getPosition();
	auto direction = Vector2().Zero;
	//auto direction = 1.0f;
	// 方向の値を代入
	// X
	if (distance.x < 0)
		direction.x = -1;
	else if (distance.x > 0)
		direction.x = 1;
	else direction.x = 0;
	// Y
	if (distance.y < 0)
		direction.y = 1;
	else if (distance.x > 0)
		direction.y = -1;
	else direction.y = 0;
	return direction;
}

// プレイヤーとの方向を正規化されたベクトルで取得します
Vector3 BaseEnemy::playerNormalizeDirection()
{
	// 方向の計算
	auto distance = position_ - player_->getPosition();
	//// 変換
	//auto nomaDistance = Vector2(distance.x, distance.y);
	//// 正規化
	//nomaDistance = nomaDistance.Normalize(nomaDistance);
	//auto distance3 = Vector3(nomaDistance.x, nomaDistance.y, 0.0f);
	distance = distance.Normalize(distance);
	return distance;
}

// 敵が飲み込まれた時のスケールポイントを返します
float BaseEnemy::getSP()
{
	return 1.0f;
}

// 敵の大きさを返します
int BaseEnemy::getScale()
{
	return 1;
}

void BaseEnemy::updateState(float deltaTime)
{
	// プレイヤーの捜索
	player_ = world_->findActor("Player");

	switch (state_)
	{
	case State::Idel: idle(); break;
	case State::Search: searchMove(); break;
	case State::Chase: chaseMove(); break;
	case State::Attack: Attack(); break;
		// State::Return: ; break;
	case State::Damage: damageMove(); break;
	case State::Dead: deadMove(); break;
	}

	stateTimer_ += deltaTime;
}
