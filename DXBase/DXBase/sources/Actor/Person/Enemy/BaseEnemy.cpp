#include "BaseEnemy.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"
#include "FloorSearchPoint.h"


BaseEnemy::BaseEnemy(IWorld * world, const Vector2& position, const float bodyScale) :
	Actor(world, "BaseEnemy", position,
		CollisionBase(
			Vector2(position.x + bodyScale / 2.0f, position.y + bodyScale / 2.0f),
			Vector2(position.x - bodyScale / 2.0f, position.y + bodyScale / 2.0f),
			Vector2(position.x + bodyScale / 2.0f, position.y - bodyScale / 2.0f),
			Vector2(position.x - bodyScale / 2.0f, position.y - bodyScale / 2.0f)
			)),
	hp_(10),
	ap_(0),
	speed_(1.0f),
	initSpeed_(speed_),
	scale_(bodyScale),
	direction_(Vector2(1.0f, 1.0f)),
	isGround_(false),
	isUseGravity_(true),
	isInvincible_(false),
	discoveryLenght_(125),
	stateTimer_(0.0f),
	state_(State::Idel),
	stateString_(""),
	discoveryPosition_(Vector2::Zero),
	animation_(),
	player_(nullptr),
	fspScript(nullptr),
	wsScript(nullptr),
	pricleObj_(nullptr),
	enemyManager_(EnemyManager(position))
{
	Initialize();
}

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::Initialize()
{
	// 床捜索オブジェクトの追加
	auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector3(0.0f, 0.0f + scale_ / 2.0f, 0.0f), position_);
	// ワールドに追加
	world_->addActor(ActorGroup::Enemy, fsObj);
	fspScript = &*fsObj;
	fspScript->setPosition(position_);
	// 壁捜索オブジェクト
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector3(-scale_ / 2.0f, 0.0f, 0.0f), position_);
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsScript = &*wsObj;
}

void BaseEnemy::onUpdate(float deltaTime)
{
	// デルタタイムの値を設定する
	setDeltaTime(deltaTime);
	// エネミーマネージャーの更新
	enemyManager_.update(deltaTime);
	// 状態の更新
	updateState(deltaTime);
	// 捜索オブジェクトの更新
	updateSearchObjct();
	
	// デバッグ
	distance_ = enemyManager_.getPlayerLength();
	isGround_ = false;

	// アニメーションの変更
	//animation_.change(motion_);
	// アニメーションの更新
	//animation_.update(deltaTime);
}

void BaseEnemy::onDraw() const
{
	auto stateChar = stateString_.c_str();
	// 敵の表示
	DrawGraph(
		position_.x - scale_ / 2.0f, position_.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);
	// 文字の表示
	DrawString(
		position_.x - scale_, position_.y - 20 - scale_,
		stateChar, GetColor(255, 255, 255));

	// デバッグ
	/*DrawFormatString(25, 25, GetColor(255, 255, 255), "body x:%d,y:%d", (int)body_.GetBox().component_.point[0].x, (int)body_.GetBox().component_.point[0].y);
	DrawFormatString(25, 50, GetColor(255, 255, 255), "pos  x:%d,y:%d", (int)position_.x, (int)position_.y);
	DrawFormatString(25, 75, GetColor(255, 255, 255), "プレイヤーとの距離:%d", (int)distance_);*/

	//char lengthChar = static_cast<char>(enemyManager_.getPlayerLength());
	//DrawString(position_.x + 50, position_.y - 20, &lengthChar, GetColor(255, 255, 255));
	body_.draw();
}

void BaseEnemy::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	// プレイヤー関連のオブジェクトに当たっているなら
	// actorName != "Player_AttackRange"
	// if (actorName != "Player") return;

	// プレイヤーに当たらない？
	if (actorName == "PlayerBody2" && !isInvincible_) {
		// ダメージ
		/*hp_ -= 10;
		if (hp_ <= 0) changeState(State::Dead, ENEMY_DEAD);
		else changeState(State::Damage, ENEMY_DAMAGE);*/
		changeState(State::Dead, ENEMY_DEAD);
		isUseGravity_ = true;
		body_.enabled(false);
	}
	//// ダメージ
	//// hp_ -= player->GetAP(); とか
	//hp_ -= 10;
	//if (hp_ <= 0) changeState(State::Dead, ENEMY_DEAD);
	//else changeState(State::Damage, ENEMY_DAMAGE);
	//body_.enabled(false);
}

void BaseEnemy::onMessage(EventMessage event, void *)
{
}

// 待機状態です
void BaseEnemy::idle()
{
	stateString_ = "待機";
	// if (enemyManager_.getPlayerLength() < 100) changeState(State::Search, ENEMY_WALK);
	changeState(State::Search, ENEMY_WALK);
}
// 索敵移動です(デフォルト)
void BaseEnemy::search()
{
	// プレイヤーの捜索
	findPlayer();
	stateString_ = "捜索";
	// 捜索行動
	searchMove();
	// 一定距離内なら追跡する
	if (enemyManager_.getPlayerLength() <= discoveryLenght_) {
		changeState(State::Discovery, ENEMY_DISCOVERY);
		discoveryPosition_ = position_;
	}
	//else if(enemyManager_.getPlayerLength() >= 100) changeState(State::Idel, ENEMY_IDLE);
}

// プレイヤーを発見した時の行動です
void BaseEnemy::discovery()
{
	isUseGravity_ = false;
	// プレイヤーの捜索
	//findPlayer();
	stateString_ = "発見";
	// ジャンプモーション
	position_.y += (-0.5f + stateTimer_) * GRAVITY_ * deltaTimer_;
	// 位置を補正
	groundClamp();
	// 補正されたら、追跡に移行
	if (position_.y >= fspScript->getFloorPosition().y) {
		changeState(State::Chase, ENEMY_WALK);
		isUseGravity_ = true;
	}
}

// プレイヤーの追跡行動です(デフォルト)
void BaseEnemy::chase()
{
	// プレイヤーの捜索
	findPlayer();
	stateString_ = "追跡";
	// 追跡行動
	chaseMove();
	if (enemyManager_.getPlayerLength() > discoveryLenght_)
		changeState(State::Search, ENEMY_WALK);
	// 前方に移動(仮)
	//auto distance = position_ - player_->getPosition();
	////auto direction = 1.0f;
	//if (distance.x < 0)
	//	directionX_ = -1;
	//else if(distance.x > 0) directionX_ = 1;
	//else directionX_ = 0;

	//// 水平方向に移動
	//position_ += position_.Left * -speed_ * getPlayerDirection().x;
	//// 移動
	//position_ += BaseEnemy::getPlayerNormalizeDirection() * -speed_;
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

// 攻撃行動です
void BaseEnemy::Attack()
{
	/*world_->addActor(
		ActorGroup::Enemy_AttackRange, std::make_shared<Enemy_AttackRange>(world_, position_));*/
	stateString_ = "攻撃";
	if (stateTimer_ >= 3.0f)
		changeState(State::Search, ENEMY_IDLE);
}

// 被弾行動です
void BaseEnemy::damageMove()
{
	stateString_ = "ダメージ";
	if (stateTimer_ >= 3.0f)
		changeState(State::Chase, ENEMY_WALK);
}

// 死亡行動です
void BaseEnemy::deadMove()
{
	//if (stateTimer_ >= 3.0f) dead();
	stateString_ = "死亡";
	//dead();
}

// 状態の変更を行います
void BaseEnemy::changeState(State state, unsigned int motion)
{
	state_ = state;
	stateTimer_ = 0.0f;
	motion_ = motion;
}

// プレイヤーを捜索します
void BaseEnemy::findPlayer()
{
	// プレイヤーがいなければ待機状態
	if (player_ == nullptr) {
		changeState(State::Idel, ENEMY_IDLE);
		return;
	}
}

void BaseEnemy::searchMove()
{
}

void BaseEnemy::chaseMove()
{
}

// 床捜索オブジェクトの生成
void BaseEnemy::createFSP()
{
	// 追加された位置分だけ生成する
	for (int i = 0; i != fspPositionContainer_.size(); ++i) {
		// 捜索オブジェクトの追加
		auto fsObj = std::make_shared<FloorSearchPoint>(world_, Vector3::Zero, position_);
		//fsPoint_ = std::make_shared<FloorSearchPoint>(world_, position_);
		world_->addActor(ActorGroup::Effect, fsObj);
		// 床オブジェクトのスクリプト取得
		auto fspScript = &*fsObj;
		//fspScript->setEnemyScale(Vector2(scale_, scale_));
		// 追加
		fspContainer_.push_back(fspScript);
		fspContainer_[i]->setEnemyScale(Vector2(scale_, scale_));
		fspContainer_[i]->setPosition(position_ + fspPositionContainer_[i]);
		// エネミーマネージャー
		enemyManager_.addFSP(fspScript);
	}
}

void BaseEnemy::setDeltaTime(float deltatime)
{
	deltaTimer_ = deltatime * 60.0f;
}

// 敵が飲み込まれた時のスケールポイントを返します
float BaseEnemy::getSP()
{
	return 1.0f;
}

// 敵の大きさを返します
int BaseEnemy::getScale()
{
	return (int)scale_;
}

void BaseEnemy::updateState(float deltaTime)
{
	// プレイヤーの捜索
	player_ = world_->findActor("Player");
	// プレイヤーが取得できれば、エネミーマネージャーに位置を入れる
	if (player_ != nullptr)
		enemyManager_.setEMPosition(position_, player_->getPosition());
	switch (state_)
	{
	case State::Idel: idle(); break;
	case State::Search: search(); break;
	case State::Discovery: discovery(); break;
	case State::Chase: chase(); break;
	case State::Attack: Attack(); break;
		// State::Return: ; break;
	case State::Damage: damageMove(); break;
	case State::Dead: deadMove(); break;
	}

	stateTimer_ += deltaTime;
}

// 捜索オブジェクトの更新
void BaseEnemy::updateSearchObjct()
{
	// 接地していないなら重力加算
	if (!fspScript->isGround() && isUseGravity_)
		position_.y += GRAVITY_ * deltaTimer_;
	// 床の位置に補正する
	if (fspScript->isGround())
		groundClamp();
	// 壁に当たったら方向転換(X)
	if (wsScript->isGround())
		direction_.x *= -1.0f;
	// 捜索オブジェクトにプレイヤーの方向を入れる
	wsScript->setDirection(direction_);
	// 各捜索オブジェクトに位置を入れる
	fspScript->setPosition(position_);
	wsScript->setPosition(position_);
}

//地面の位置に補正します
void BaseEnemy::groundClamp()
{
	position_.y = MathHelper::Clamp(position_.y,
		fspScript->getFloorPosition().y - 100.0f,
		fspScript->getFloorPosition().y);
}
