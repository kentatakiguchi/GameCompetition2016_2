#include "FlyingEnemy.h"
#include "../../../Base/ActorGroup.h"
#include "../FloorSearchPoint.h"
#include "Prickle.h"

FlyingEnemy::FlyingEnemy(IWorld * world, const Vector2 & position) : 
	BaseEnemy(world, position, 64.0f),
	direTimer_(0.0f),
	lostTimer_(0.0f),
	pastPosition(Vector2::Zero),
	wsObj_(nullptr)
{
	isUseGravity_ = false;
	// 壁捜索オブジェクトの生成
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, -(scale_ / 2.0f + 1.0f)), 
		Vector2(scale_, 2.0f));
	// ワールドに追加
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsObj_ = &*wsObj;
	// トゲオブジェクトの生成
	auto pricleObj = std::make_shared<Prickle>(
		world_,
		Vector2::Zero,
		Vector2::Up * -(scale_ + 1.0f),
		Vector2(64.0f, 64.0f));
	world_->addActor(ActorGroup::Enemy_AttackRange, pricleObj);
	pricleObj_ = &*pricleObj;
	pricleObj_->setDirection(direction_);
}

void FlyingEnemy::onUpdate(float deltaTime)
{
	// トゲの更新
	//pricleObj_->setDirection(direction_);
	pricleObj_->setEnemyPosition(position_);

	BaseEnemy::onUpdate(deltaTime);
	direTimer_ += deltaTime;

	/*if (state_ == State::Search) {
		if (wsObj_->isGround() || direTimer_ >= 4.0f) {
			direction_.y *= -1;
			direTimer_ = 0;
		}
	}*/

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

void FlyingEnemy::discovery()
{
	//auto player = world_->findActor("PlayerBody1");
	auto player = world_->findActor("Player");
	pastPosition = player->getPosition();
	pricleObj_->setDirection(enemyManager_.getDirection(pastPosition));
	changeState(State::Chase, ENEMY_WALK);
}

void FlyingEnemy::attack()
{
}

void FlyingEnemy::searchMove()
{
	// 床に当たるか、一定時間経過したら、方向転換
	if (wsObj_->isGround() || direTimer_ >= 4.0f) {
		direction_.y *= -1;
		direTimer_ = 0;
	}
	position_ += Vector2::Down * speed_ * direction_.y * deltaTimer_;
	pricleObj_->setDirection(Vector2::Up);
	pricleObj_->setAddPosition(Vector2::Up * -(scale_ + 1.0f));
	//pDirection_ = enemyManager_.getPlayerNormalizeDirection();
}

void FlyingEnemy::chaseMove()
{
	// プレイヤーのいた方向に進む
	// プレイヤーが居た位置との距離が０ならば、見失う
	pastPosition -= world_->MoveActor();
	auto dire = position_ - pastPosition;
	if ((int)dire.x < 0)
		dire.x = 1;
	else if ((int)dire.x > 0)
		dire.x = 1;
	auto direction = enemyManager_.getDirection(pastPosition);

	direction.y = 0.0f;

	auto p_Direction = position_ - pastPosition;
 	auto length = p_Direction.Length();

	/*pricleObj_->setDirection(-direction);
	pricleObj_->setAddPosition(Vector2::Left * (scale_ + 1.0f));*/
	// プレイヤーが床にいる場合、一定の距離内に居ることが難しいので、切り上げる
	if (length <= 15) {
		changeState(State::Lost, ENEMY_LOST);
		return;
	}
	// 接地していたら、yベクトルを 0 にする
	if (wsObj_->isGround())
		p_Direction.y = 0;
	auto speed = speed_;
	if (length < speed_)
		speed = length;
	// プレイヤーの居た位置からの方向を設定
	direction_ = enemyManager_.getDirection(pastPosition);
	// プレイヤーの居た位置に進む
	position_ -= p_Direction.Normalize() * speed * deltaTimer_;
	// トゲの設定
	//pricleObj_->setDirection(direction);
	pricleObj_->setAddPosition(Vector2::Left * (scale_ + 1.0f));
}

void FlyingEnemy::lostMove()
{
	lostTimer_ += deltaTimer_ / 60.0f;
	if (lostTimer_ <= 8.0f) return;
	lostTimer_ = 0.0f;
	changeState(State::Search, ENEMY_WALK);
}
