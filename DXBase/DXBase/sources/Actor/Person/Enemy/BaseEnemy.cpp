#include "BaseEnemy.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"
#include "FloorSearchPoint.h"
#include "PlayerSearchObj.h"

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
	isMove_(false),
	isBlockCollideBegin_(false),
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
	psObj_(nullptr),
	fspScript(nullptr),
	wsScript(nullptr),
	pricleObj_(nullptr),
	enemyManager_(EnemyManager(position)),
	isTestGround_(false),
	testTop(0.0f),
	testBottom(0.0f),
	testRight(0.0f),
	testLeft(0.0f),
	test_t(0.0f)
{
	//Initialize();

	// rayオブジェクトの追加
	// auto player = world_->findActor("PlayerBody1");
	auto player = world_->findActor("PlayerBody1");
	auto ray = std::make_shared<PlayerSearchObj>(
		world_, position_, player->getPosition());
	world_->addActor(ActorGroup::EnemyBullet, ray);
	psObj_ = &*ray;
}

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::Initialize()
{
	// 床捜索オブジェクトの追加
	/*auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector2(0.0f, 0.0f + scale_ / 2.0f), position_);*/
	auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, 0.0f + scale_ / 2.0f),
		Vector2(scale_, 2.0f));
	// ワールドに追加
	world_->addActor(ActorGroup::Enemy, fsObj);
	fspScript = &*fsObj;
	fspScript->setPosition(position_);
	// 壁捜索オブジェクト
	/*auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector2(-scale_ / 2.0f, 0.0f), position_);*/
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, position_, 
		Vector2(-scale_ / 2.0f, 0.0f),
		Vector2(2.0f, scale_- 30.0f));
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
	
	isGround_ = false;
	// 衝突判定後のboolがtureなら、falseに変える
	if (!isBlockCollideExit_) return;
	isBlockCollideExit_ = false;

	// アニメーションの変更
	//animation_.change(motion_);
	// アニメーションの更新
	//animation_.update(deltaTime);
}

void BaseEnemy::onDraw() const
{
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// 敵の表示
	DrawGraph(
		vec3Pos.x - scale_ / 2.0f, vec3Pos.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);
	// 文字の表示
	DrawString(
		vec3Pos.x - scale_, vec3Pos.y - 20 - scale_,
		stateChar, GetColor(255, 255, 255));

	// デバッグ
	/*DrawFormatString(25, 25, GetColor(255, 255, 255), "body x:%d,y:%d", (int)body_.GetBox().component_.point[0].x, (int)body_.GetBox().component_.point[0].y);
	DrawFormatString(25, 50, GetColor(255, 255, 255), "pos  x:%d,y:%d", (int)position_.x, (int)position_.y);
	DrawFormatString(25, 75, GetColor(255, 255, 255), "プレイヤーとの距離:%d", (int)distance_);*/
	DrawFormatString(25, 150, GetColor(255, 255, 255),
		"ブロックとの位置=>上:%d 下:%d", 
		(int)testTop, (int)testBottom);
	DrawFormatString(25, 200, GetColor(255, 255, 255),
		"ブロックとの位置=>右:%d 左:%d",
		(int)testRight, (int)testLeft);
	DrawFormatString(25, 250, GetColor(255, 255, 255),
		"ブロックとのt:%d",
		(int)test_t);

	//char lengthChar = static_cast<char>(enemyManager_.getPlayerLength());
	//DrawString(position_.x + 50, position_.y - 20, &lengthChar, GetColor(255, 255, 255));
	body_.draw(inv_);
}

void BaseEnemy::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	// プレイヤー関連のオブジェクトに当たっているなら
	// actorName != "Player_AttackRange"
	// if (actorName != "Player") return;

	// 名無しなら,boolを衝突後のものにする
	if (actorName == "") {
		isBlockCollideExit_ = true;
		isBlockCollideEnter_ = false;
		body_.enabled(false);
		return;
	}
	// マップのブロックに当たったら、処理を行う
	if (actorName == "MovelessFloor") {
		// Enterがfalseなら、beginをtrueにする
		// 逆ならば、beginをfalseに変える
		if(!isBlockCollideEnter_)
			isBlockCollideBegin_ = true;
		else isBlockCollideBegin_ = false;
		isBlockCollideEnter_ = true;
		body_.enabled(false);
		return;

		//// 相手側の当たり判定が四角形以外なら行わない(てきとう判定)
		//if (actor.body_.GetBox().getWidth() == 0) return;
		// 正方形同士の計算
		// 自分自身の1f前の位置を取得
		auto pos = body_.GetBox().previousPosition_;
		// 相手側の四角形の4点を取得
		auto topLeft = actor.getBody().GetBox().component_.point[0];
		auto topRight = actor.getBody().GetBox().component_.point[1];
		auto bottomLeft = actor.getBody().GetBox().component_.point[2];
		auto bottomRight = actor.getBody().GetBox().component_.point[3];
		// 各辺に対する位置の外積を計算する
		// 縦方向のベクトル(H)を求める
		auto top = Vector2::Cross(
			(topLeft - topRight).Normalize(), (pos - topRight));
		auto bottom = Vector2::Cross(
			(bottomRight - bottomLeft).Normalize(), (pos - bottomLeft));
		auto right = Vector2::Cross(
			(topRight - bottomRight).Normalize(), (pos - bottomRight));
		auto left = Vector2::Cross(
			(bottomLeft - topLeft).Normalize(), (pos - topLeft));

		testTop = top * 100;
		testBottom = bottom * 100;
		testRight = right * 100;
		testLeft = left * 100;
		// Y軸上で衝突した場合
		//if (left <= 0 && right <= 0) {
		//	// top > 0 なら上に補間 bottom > 0 なら下に補間する
		//	if (top > 0)
		//		position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
		//	if (bottom > 0)
		//		position_.y = bottomRight.y + body_.GetBox().getHeight() / 2.0f;
		//}	// X軸上で衝突した場合
		//if (top <= 0 && bottom <= 0) {
		//	// left > 0 なら右に補間 right > 0 なら左に補間する
		//	if (left > 0)
		//		position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;
		//	if (right > 0)
		//		position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;
		//}

		// 中心から線分に下した点とp1までの距離比
		/*Vector2 other_v = actor.body_.GetBox().component_.point[3] - 
			actor.body_.GetBox().component_.point[2];
		Vector2 left_v1 = body_.GetBox().component_.point[2] -
			actor.body_.GetBox().component_.point[2];
		float left_t = Vector2::Dot(other_v, left_v1) /
			Vector2::Dot(other_v, other_v);*/

		// 
		//Vector2 right_v1 = body_.GetBox().component_.point[3] -
		//	actor.body_.GetBox().component_.point[2];
		//// 中心から線分に下した点とp1までの距離比
		//float right_t = Vector2::Dot(other_v, right_v1) /
		//	Vector2::Dot(other_v, other_v);

		//if (left <= 0 && right <= 0) {
		//	// top > 0 なら上に補間 bottom > 0 なら下に補間する
		//	
		//}

		/*if (top > 0)
			position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
		else
			position_.y = bottomRight.y + body_.GetBox().getHeight() / 2.0f;*/
		// 当たったブロックの大きさ
		// top < actor.body_.GetBox().getWidth

		// 上に補間
		//if (top > 0 && 
		//	(-body_.GetBox().getWidth() < right && 
		//	-body_.GetBox().getWidth() < left))
		//	position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
		//// 右に補間
		//if (right >= actor.body_.GetBox().getWidth() &&
		//	top < actor.body_.GetBox().getHeight())
		//	position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;
		//// 左に補間
		//if (left >= actor.body_.GetBox().getWidth() &&
		//	top < actor.body_.GetBox().getHeight())
		//	position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;

		// 上
		//if (top >= 32 && left > -64) {
		//	/*if(left >= -body_.GetBox().getWidth() && 
		//		right >= -body_.GetBox().getWidth())
		//		position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;*/
		//	position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
		//}
		//if (right >= 0) {
		//	if (top < 32) {
		//		if(bottom < 0)
		//		position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;
		//	}
		//	else {
		//		if (bottom > -64 && bottom < -63)
		//		position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;
		//	}
		//		
		//}
		//if (left >= 0) {
		//	if(top < 32)
		//		position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;
		//}

		//else {
		//	// 左に補間
		//	/*if (left >= -64)
		//		position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;*/
		//	// 右に補間
		//	// top == 32 で衝突しない
		//	/*if (right >= 0)
		//		position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;*/
		//}

		// 右に補間する
		/*if (left_t > 0 && right >= 0)
			position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;*/

		// 上に補間
		//if (top > 0)
		//	position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
		//// 左に補間
		//if (left_t >= 0 && left >= 0)
		//	position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;

		//test_t = right_t * 100;

		/*Vector2 otherCenter = actor.body_.GetBox().position_;
		Vector2 thisCenter = body_.GetBox().position_;*/

		//Vector2 otherCenter = actor.body_.GetBox().component_.point[3] / 2.0f;
		//Vector2 thisCenter = body_.GetBox().component_.point[3] / 2.0f;
		//// 方向
		//Vector2 dir = thisCenter - otherCenter;

		//if (std::abs(dir.x) >std::abs(dir.y))
		//{
		//	if (dir.x > 0)
		//	{
		//		position_.x = actor.position_.x + body_.GetBox().getWidth();
		//		//position.X = gameObj.getRectangle().Right;
		//	}
		//	else
		//	{
		//		position_.x = actor.position_.x - body_.GetBox().getWidth() / 2.0f;
		//		//position.X = gameObj.getRectangle().Left - this.width;
		//	}
		//}
		//else
		//{
		//	if (dir.y > 0)
		//	{
		//		position_.y = actor.position_.y + body_.GetBox().getHeight();
		//		//position.Y = gameObj.getRectangle().Bottom;
		//	}
		//	else
		//	{
		//		position_.y = actor.position_.y - body_.GetBox().getHeight() / 2.0f;
		//		//position.Y = gameObj.getRectangle().Top - this.hight;
		//	}
		//}
		

		isTestGround_ = true;

		body_.enabled(false);
		return;
	}

	// プレイヤーに当たらない？
	if ((actorName == "PlayerBody2" || actorName == "PlayerBody1") &&
		!isInvincible_) {
		// ダメージ
		/*hp_ -= 10;
		if (hp_ <= 0) changeState(State::Dead, ENEMY_DEAD);
		else changeState(State::Damage, ENEMY_DAMAGE);*/
		changeState(State::Dead, ENEMY_DEAD);
		isUseGravity_ = true;
		body_.enabled(false);
		return;
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
	speed_ = initSpeed_;
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
	speed_ = initSpeed_ * 1.5f;
	// 追跡行動
	chaseMove();
	if (enemyManager_.getPlayerLength() > discoveryLenght_ + 30.0f)
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
void BaseEnemy::attack()
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

// プレイヤーを見失ったときの行動です
void BaseEnemy::lostMove()
{
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
		auto fsObj = 
			std::make_shared<FloorSearchPoint>(
				world_, position_, 
				fspPositionContainer_[i],
				fspScaleContainer_[i]
				);
		world_->addActor(ActorGroup::Enemy, fsObj);
		// 床オブジェクトのスクリプト取得
		auto fspScript = &*fsObj;
		//fspScript->setEnemyScale(Vector2(scale_, scale_));
		// 追加
		/*wspContainer_.push_back(fspScript);
		wspContainer_[i]->setEnemyScale(Vector2(scale_, scale_));
		wspContainer_[i]->setPosition(position_ + fspPositionContainer_[i]);*/
		// エネミーマネージャーに追加
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
	// player_ = world_->findActor("Player");
	player_ = world_->findActor("PlayerBody1");
	// プレイヤーが取得できれば、エネミーマネージャーに位置を入れる
	if (player_ != nullptr) {
		enemyManager_.setEMPosition(position_, player_->getPosition(), direction_);
		psObj_->setPosition(position_, player_->getPosition());
	}
	switch (state_)
	{
	case State::Idel: idle(); break;
	case State::Search: search(); break;
	case State::Discovery: discovery(); break;
	case State::Chase: chase(); break;
	case State::Lost: lostMove(); break;
	case State::attack: attack(); break;
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
	// if (!isTestGround_)
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
