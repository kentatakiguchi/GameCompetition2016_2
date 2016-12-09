#include "FlyingEnemy.h"
#include "../../../Base/ActorGroup.h"
#include "../FloorSearchPoint.h"
#include "Prickle.h"
#include "../PlayerSearchObj.h"

FlyingEnemy::FlyingEnemy(
	IWorld * world,
	const Vector2 & position, 
	float Down) :
	BaseEnemy(world, position, 64.0f),
	direTimer_(0.0f),
	lostTimer_(0.0f),
	pastPosition(Vector2::Zero),
	wsObj_(nullptr)
{
	direction_ = Vector2(1.0f, Down);
	BaseEnemy::Initialize();

	isUseGravity_ = false;
	// 壁捜索オブジェクトの生成
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, -(scale_ / 2.0f + 1.0f)), 
		Vector2(scale_, 2.0f));
	// ワールドに追加
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsObj_ = &*wsObj;
	objContainer_.push_back(wsObj_);
	// トゲオブジェクトの生成
	auto pricleObj = std::make_shared<Prickle>(
		world_,
		Vector2::Zero,
		Vector2::Up * -(scale_ + 1.0f),
		Vector2(64.0f, 64.0f));
	world_->addActor(ActorGroup::Enemy_AttackRange, pricleObj);
	pricleObj_ = &*pricleObj;
	objContainer_.push_back(pricleObj_);
	pricleObj_->setDirection(direction_);
	// アニメーションの追加
	addTexPosition_ = Vector2::Zero;
	addAnimation();
	animation_.changeAnimation(ENEMY_WALK);
}

void FlyingEnemy::beginUpdate(float deltaTime)
{
	// トゲの更新
	//pricleObj_->setDirection(direction_);
	pricleObj_->setEnemyPosition(position_);
}

void FlyingEnemy::update(float deltaTime)
{
	wsObj_->setDirection(direction_);
	wsObj_->setPosition(position_);
}

//void FlyingEnemy::onDraw() const
//{
//	auto stateChar = stateString_.c_str();
//	// 敵の表示
//	DrawGraph(
//		position_.x - scale_ / 2.0f, position_.y - scale_ / 2.0f,
//		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);
//	// 文字の表示
//	DrawString(
//		position_.x - scale_, position_.y - 20 - scale_,
//		stateChar, GetColor(255, 255, 255));
//
//	// デバッグ
//	DrawFormatString(
//		25, 75, GetColor(255, 255, 255), 
//		"プレイヤーとのX方向:%d", (int)(position_ - pastPosition).x);
//}

void FlyingEnemy::onCollide(Actor & actor)
{
	BaseEnemy::onCollide(actor);
}

void FlyingEnemy::onMessage(EventMessage event, void *)
{
}

// 索敵移動です
void FlyingEnemy::search()
{
	// プレイヤーの捜索
	findPlayer();
	stateString_ = "捜索";
	// 初期速度に戻す
	speed_ = initSpeed_;
	// 捜索行動
	searchMove();
	// プレイヤーが存在しなければ、捜索と待機状態以外は行わない
	if (!isPlayer_) return;
	// 一定距離内で、プレイヤーとの間にブロックがなかったら
	// 追跡する
	if (enemyManager_.getPlayerLength() <= discoveryLenght_ &&
		psObj_->isPlayerLook()) {
		changeState(State::Chase, ENEMY_ATTACK);
		discoveryPosition_ = position_;
		// 過去の位置を入れる
		auto player = world_->findActor("PlayerBody1");
		pastPosition = player->getPosition();
		pricleObj_->setDirection(enemyManager_.getDirection(pastPosition));
		// 回転
		if (enemyManager_.getDirection(pastPosition).x < 0)
			TexDegress_ = 90;
		else TexDegress_ = 270;
	}
}

void FlyingEnemy::discovery()
{
	/*auto player = world_->findActor("PlayerBody1");
	pastPosition = player->getPosition();
	pricleObj_->setDirection(enemyManager_.getDirection(pastPosition));
	changeState(State::Chase, ENEMY_WALK);*/
}

void FlyingEnemy::attack()
{
}

void FlyingEnemy::searchMove()
{
	// 速度 / チップサイズの大きさ
	// => direTimer_ = 1 => マップチップ一個分動いたことにする	
	direTimer_ += (speed_ / CHIPSIZE) * deltaTimer_;
	// 床に当たるか、一定のマップチップ分動いたら、方向転換
	// (wsObj_->isGround() || direTimer_ >= 14.0f)
	if (wsObj_->isGround() || direTimer_ >= 3.0f) {
		direction_.y *= -1;
		direTimer_ = 0;
	}
	position_ += Vector2::Down * speed_ * direction_.y * deltaTimer_;
	pricleObj_->setDirection(Vector2::Up);
	pricleObj_->setAddPosition(Vector2::Up * -(scale_ + 1.0f));
	//pDirection_ = enemyManager_.getPlayerNormalizeDirection();
}

// プレイヤーの追跡行動です
void FlyingEnemy::chase()
{
	// プレイヤーの捜索
	findPlayer();
	stateString_ = "追跡";
	// 移動速度を倍速にする
	speed_ = initSpeed_ * 1.5f;
	// 追跡行動
	chaseMove();
}

void FlyingEnemy::chaseMove()
{
	// プレイヤーのいた方向に進む
	// プレイヤーが居た位置との距離が０ならば、見失う
	// pastPosition -= world_->MoveActor();
	auto direction = enemyManager_.getDirection(pastPosition);
	auto p_Direction = position_ - pastPosition;
 	auto length = p_Direction.Length();
	/*pricleObj_->setDirection(-direction);
	pricleObj_->setAddPosition(Vector2::Left * (scale_ + 1.0f));*/
	// プレイヤーが床にいる場合、一定の距離内に居ることが難しいので、切り上げる
	if (length <= 15) {
		//changeState(State::Lost, ENEMY_LOST);
		changeState(State::Lost, ENEMY_WALK);
		return;
	}
	// 接地していたら、yベクトルを 0 にする
	if (wsObj_->isGround() || isGround_)
		p_Direction.y = 0;
	auto speed = speed_;
	if (length < speed_)
		speed = length;
	// プレイヤーの居た位置からの方向を設定
	direction_ = enemyManager_.getDirection(pastPosition);
	// プレイヤーの居た位置に進む
	direction.y *= -1;
	position_ += -direction.Normalize() * speed * deltaTimer_;
	// トゲの設定
	//pricleObj_->setDirection(direction);
	pricleObj_->setAddPosition(Vector2::Left * (scale_ + 1.0f));
}

// 敵を見失った時の行動です
void FlyingEnemy::lostMove()
{
	// 見失う
	stateString_ = "見失う";
	lostTimer_ += deltaTimer_ / 60.0f;
	if (lostTimer_ <= 8.0f) return;
	lostTimer_ = 0.0f;
	changeState(State::Search, ENEMY_WALK);
}

// アニメーションの追加を行います
void FlyingEnemy::addAnimation()
{
	animation_.addAnimation(
		ENEMY_WALK,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_FLYINGENEMY_WALK_TEX),
		texSize_, 8, 3, 3);
	animation_.addAnimation(
		ENEMY_ATTACK,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_FLYINGENEMY_ATTACK_TEX),
		texSize_, 8, 2, 5);
	animation_.addAnimation(
		ENEMY_DAMAGE,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_FLYINGENEMY_DAMAGE_TEX),
		texSize_, 8, 3, 3);
}
