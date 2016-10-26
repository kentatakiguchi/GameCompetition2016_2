#include "BaseEnemy.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"
#include "Enemy_AttackRange.h"
#include "FloorSearchPoint.h"


BaseEnemy::BaseEnemy(IWorld * world, const Vector3& position, const float bodyScale) :
	Actor(world, "BaseEnemy", position, CollisionBase(Vector2(-bodyScale, -bodyScale), Vector2(bodyScale, -bodyScale), Vector2(-bodyScale, bodyScale), Vector2(bodyScale, bodyScale))),
	hp_(10),
	ap_(0),
	speed_(1.0f),
	initSpeed_(speed_),
	scale_(bodyScale),
	discoveryLenght_(50),
	color_(GetColor(255, 255, 255)),
	stateTimer_(0.0f),
	state_(State::Idel),
	stateString_(""),
	discoveryPosition_(Vector3(0.0f, 0.0f, 0.0f)),
	animation_(),
	player_(nullptr),
	fsPointScript(nullptr),
	enemyManager_(EnemyManager(position))
{
	//world_->addActor(ActorGroup::Enemy, std::make_shared<WeakEnemy>(world_.get(), Vector3(15, 5, 0)));
	
	//fsPointScript = &*fsPoint_;

	//objD->s
	//fsPointScript = typeid(fsPoint_).name();
}

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::onUpdate(float deltaTime)
{
	// エネミーマネージャーの更新
	enemyManager_.update(deltaTime);
	// 状態の更新
	updateState(deltaTime);
	// アニメーションの変更
	//animation_.change(motion_);
	// アニメーションの更新
	//animation_.update(deltaTime);
}

void BaseEnemy::onDraw() const
{
	auto stateChar = stateString_.c_str();
	DrawGraph(
		position_.x - scale_, position_.y - scale_, 
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);
	DrawString(position_.x - scale_, position_.y - 20 - scale_, stateChar, GetColor(255, 255, 255));

	//char lengthChar = static_cast<char>(enemyManager_.getPlayerLength());
	//DrawString(position_.x + 50, position_.y - 20, &lengthChar, GetColor(255, 255, 255));
	
	body_.draw();
}

void BaseEnemy::onCollide(Actor & actor)
{
	if (actor.getName() != "Player_AttackRange" || actor.getName() != "Player") return;
	// ダメージ
	// hp_ -= player->GetAP(); とか
	hp_ -= 10;
	if (hp_ <= 0) changeState(State::Dead, ENEMY_DEAD);
	else changeState(State::Damage, ENEMY_DAMAGE);
	body_.enabled(false);
}

void BaseEnemy::onMessage(EventMessage event, void *)
{
}

// 待機状態です
void BaseEnemy::idle()
{
	color_ = GetColor(255, 255, 255);
	stateString_ = "待機";
	//position_ += BaseEnemy::getPlayerNormalizeDirection() * -speed_;
	if (enemyManager_.getPlayerLength() < 100) changeState(State::Search, ENEMY_WALK);
}
// 索敵移動です(デフォルト)
void BaseEnemy::search()
{
	// プレイヤーの捜索
	findPlayer();
	color_ = GetColor(0, 255, 0);
	stateString_ = "捜索";
	// 捜索行動
	searchMove();
	// 一定距離内なら追跡する
	if (enemyManager_.getPlayerLength() <= discoveryLenght_) {
		changeState(State::Discovery, ENEMY_DISCOVERY);
		discoveryPosition_ = position_;
	}
	//else if(getPlayerLength() >= 100) changeState(State::Idel, ENEMY_IDLE);
}

// プレイヤーを発見した時の行動です
void BaseEnemy::discovery()
{
	// プレイヤーの捜索
	//findPlayer();
	stateString_ = "発見";
	position_.y += -4.0f + stateTimer_ * 9.8f;
	position_.y = MathHelper::Clamp(
		position_.y, discoveryPosition_.y - 100.0f, discoveryPosition_.y);
	if(position_.y == discoveryPosition_.y)
		changeState(State::Chase, ENEMY_WALK);
}

// プレイヤーの追跡行動です(デフォルト)
void BaseEnemy::chase()
{
	// プレイヤーの捜索
	findPlayer();
	color_ = GetColor(255, 0, 0);
	stateString_ = "追跡";
	// 追跡行動
	chaseMove();
	if (enemyManager_.getPlayerLength() > discoveryLenght_)
		changeState(State::Search, ENEMY_WALK);
	// 前方に移動(仮)
	//auto distance = position_ - player_->getPosition();
	////auto direction = 1.0f;
	//if (distance.x < 0)
	//	direction_ = -1;
	//else if(distance.x > 0) direction_ = 1;
	//else direction_ = 0;

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
	color_ = GetColor(255, 255, 0);
	stateString_ = "ダメージ";
	if (stateTimer_ >= 3.0f)
		changeState(State::Chase, ENEMY_WALK);
}

// 死亡行動です
void BaseEnemy::deadMove()
{
	//if (stateTimer_ >= 3.0f) dead();
	stateString_ = "死亡";
	color_ = GetColor(10, 10, 10);
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
		// 床捜索オブジェクトの追加
		auto fsObj = std::make_shared<FloorSearchPoint>(world_, position_);
		//fsPoint_ = std::make_shared<FloorSearchPoint>(world_, position_);
		world_->addActor(ActorGroup::Effect, fsObj);
		// 床オブジェクトのスクリプト取得
		auto fspScript = &*fsObj;
		//fsPointScript->setEnemyScale(Vector2(scale_, scale_));
		// 追加
		fspContainer_.push_back(fspScript);
		fspContainer_[i]->setEnemyScale(Vector2(scale_, scale_));
		fspContainer_[i]->setPosition(position_ + fspPositionContainer_[i]);
		// エネミーマネージャー
		enemyManager_.addFSP(fspScript);
	}
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
