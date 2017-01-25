#include "BaseEnemy.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"
#include "FloorSearchPoint.h"
#include "PlayerSearchObj.h"
#include "Bosses/Effect/EnemyDeadEffect.h"
#include "Bosses/Effect/EnemyCollideEffect.h"
//#include "DeadEnemy.h"

BaseEnemy::BaseEnemy(
	IWorld * world,
	const Vector2& position,
	const float bodyScale,
	const Vector2& direction) :
	Actor(world, "BaseEnemy", position,
		CollisionBase(
			Vector2(position.x + bodyScale / 2.0f, position.y + bodyScale / 2.0f),
			Vector2(position.x - bodyScale / 2.0f, position.y + bodyScale / 2.0f),
			Vector2(position.x + bodyScale / 2.0f, position.y - bodyScale / 2.0f),
			Vector2(position.x - bodyScale / 2.0f, position.y - bodyScale / 2.0f)
			)),
	hp_(10),
	ap_(0),
	texSize_(256),
	turnMotion_(ENEMY_WALK),
	speed_(1.0f),
	initSpeed_(speed_),
	scale_(bodyScale),
	direction_(direction),
	prevDirection_(direction),
	playerLength_(0.0f),
	TexDegress_(0),
	hitTimer_(0.0f),
	isPlayer_(false),
	isMove_(false),
	isScreen_(false),
	isBlockCollideBegin_(false),
	isBlockCollideEnter_(false),
	isBlockCollidePrevEnter_(false),
	isBlockCollideExit_(false),
	isGround_(false),
	isUseGravity_(true),
	isInvincible_(false),
	isMoveFloor_(false),
	discoveryLenght_(500),
	stateTimer_(0.0f),
	state_(State::Idel),
	discoveryPosition_(Vector2::Zero),
	addTexPosition_(Vector2(0.0f, 40.0f)),
	player_(nullptr),
	psObj_(nullptr),
	fspScript_(nullptr),
	wsScript_(nullptr),
	pricleObj_(nullptr),
	enemyManager_(EnemyManager(position, direction)),
	animation_(EnemyAnimation2D()),
	seHandle_(0)
{
	// rayオブジェクトの追加
	auto player = world_->findActor("PlayerBody1");
	if (player != nullptr) {
		auto ray = std::make_shared<PlayerSearchObj>(
			world_, position_, player->getPosition());
		world_->addActor(ActorGroup::EnemyBullet, ray);
		psObj_ = &*ray;
		objContainer_.push_back(psObj_);
		isPlayer_ = true;
	}
	// SEの追加
	seHandle_ = LoadSoundMem("./resources/sounds/enemy/enemy_hakkenn.mp3");
}

BaseEnemy::~BaseEnemy()
{
	fspPositionContainer_.clear();
	fspScaleContainer_.clear();
	objContainer_.clear();
}

void BaseEnemy::Initialize()
{
	// 床捜索オブジェクトの追加
	auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, 0.0f + scale_ / 2.0f),
		Vector2(scale_, 2.0f));
	// ワールドに追加
	world_->addActor(ActorGroup::Enemy, fsObj);
	fspScript_ = &*fsObj;
	objContainer_.push_back(fspScript_);
	fspScript_->setPosition(position_);
	// 壁捜索オブジェクト
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(scale_ / 2.0f, 0.0f),
		Vector2(2.0f, scale_ - 30.0f));
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsScript_ = &*wsObj;
	objContainer_.push_back(wsScript_);
	// アニメーションの追加
	addAnimation();
	animation_.changeAnimation(ENEMY_WALK);
	animation_.changeDirType(direction_.x);
	//animation_.turnAnimation(turnMotion_, direction_.x);
}

void BaseEnemy::onUpdate(float deltaTime)
{
	// 子供用のupdate(親のupdate前に行います)
	beginUpdate(deltaTime);
	// デルタタイムの値を設定する
	setDeltaTime(deltaTime);
	// エネミーマネージャーの更新
	enemyManager_.update(deltaTime);
	// アニメーションの更新
	animation_.update(deltaTime);
	// 状態の更新
	updateState(deltaTime);
	// 捜索オブジェクトの更新
	updateSearchObjct();
	// 子のupdateの前の処理
	// ここで子のupdateを呼ばないと変になることがある
	update(deltaTime);
	// 子のupdateが終わった後の処理
	// 衝突関連の更新
	updateCollide();
	// 画像の方向を合わせる
	//animation_.turnAnimation(turnMotion_, direction_.x);
	animation_.changeDirType(direction_.x);
}

void BaseEnemy::onDraw() const
{
	if (!isScreen_) return;
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// アニメーションの描画
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	animation_.draw(
		pos, Vector2::One * (body_.GetBox().getWidth() * 2) + addTexPosition_,
		0.5f, TexDegress_);
}

void BaseEnemy::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	// プレイヤー関連のオブジェクトに当たっているなら
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	// 動く床関連に当たっているか
	auto getMoveFloorName = strstr(actorName.c_str(), "MoveFloor");
	// マップのブロックに当たったら、処理を行う
	if (getFloorName != NULL) {
		// 位置の補間
		groundClamp(actor);
		// 所持しているオブジェクトの位置も再設定する
		setObjPosition();
		// 衝突中にtrueを入れる
		isBlockCollideEnter_ = true;
		// 過去の衝突中がfalseで、、過去と現在の衝突中が違うなら場合
		// 衝突直後になる
		if (!isBlockCollidePrevEnter_ &&
			isBlockCollidePrevEnter_ != isBlockCollideEnter_)
			isBlockCollideBegin_ = true;
		// 動く床に触れたら止まる(一部の敵)
		if (getMoveFloorName != NULL)
			isMoveFloor_ = true;
		return;
	}

	// 死亡中は行わない
	if (state_ == State::Dead) return;
	// プレイヤーに当たらない？
	// PlayerのActorGroupが変わるので、 Player_AttackRangeに当たるようにする
	if ((actorName == "PlayerAttackCollider" || actorName == "BodyPoint") &&
		!isInvincible_) {
		// ダメージ
		//circleClamp(actor);
		//// 距離が長かったら返す
		if (Vector2(actor.getPosition() - position_).Length() >= 
			actor.getBody().GetCircle().getRadius() + scale_) return;
		changeState(State::Dead, ENEMY_DAMAGE);
		// エフェクトの追加(プレイヤーのチャージエフェクト)
		world_->addActor(ActorGroup::Effect,
			std::make_shared<EnemyCollideEffect>(world_, position_));
		world_->setIsStopTime(true);
		TexDegress_ = 0.0f;
		isUseGravity_ = true;
		return;
	}
}

void BaseEnemy::onMessage(EventMessage event, void *) {}

// 子供用のupdate(親のupdate前に行います)
void BaseEnemy::beginUpdate(float deltaTime) {}

// 子供用のupdate
void BaseEnemy::update(float deltaTime) {}

// 待機状態です
void BaseEnemy::idle()
{
	// プレイヤーとの距離を計算して、
	// スクリーンの幅の半分 + 敵の大きさよりちいさいなら動く
	auto a = enemyManager_.getPlayerLength();
	if (isScreen())
		changeState(State::Search, ENEMY_WALK);
}
// 索敵移動です(デフォルト)
void BaseEnemy::search()
{
	// プレイヤーの捜索
	findPlayer();
	turnMotion_ = ENEMY_WALKTURN;
	// 初期速度に戻す
	speed_ = initSpeed_;
	// 捜索行動
	searchMove();
	// プレイヤーが存在しなければ、捜索と待機状態以外は行わない
	if (!isPlayer_) return;
	// 一定距離内で、プレイヤーとの間にブロックがなかったら
	// 角度
	auto a = enemyManager_.getPlayerNormalizeDirection();
	auto b = Vector2::Left * direction_.x;
	auto radius = std::atan2(b.y - a.y, b.x - a.x);
	auto deg = radius * 180.0f / MathHelper::Pi;
	// 追跡する
	if (enemyManager_.getPlayerLength() <= discoveryLenght_ &&
		std::abs(deg) <= 30.0f &&
		psObj_->isPlayerLook()) {
		changeState(State::Discovery, ENEMY_DISCOVERY);
		// 発見SEの再生
		PlaySoundMem(seHandle_, DX_PLAYTYPE_BACK);
		discoveryPosition_ = position_;
	}
}

// プレイヤーを発見した時の行動です
void BaseEnemy::discovery()
{
	isUseGravity_ = false;
	// ジャンプモーション
	position_.y += (-0.5f + stateTimer_) * GRAVITY_ * deltaTimer_;
	// ジャンプ後に床に接地したら追跡状態に遷移
	if (isGround_ && stateTimer_ >= 0.2f) {
		changeState(State::Chase, ENEMY_ATTACK);
		turnMotion_ = ENEMY_ATTACKTURN;
		//animation_.turnAnimation(ENEMY_ATTACK);
		isUseGravity_ = true;
	}
}

// プレイヤーの追跡行動です(デフォルト)
void BaseEnemy::chase()
{
	// プレイヤーの捜索
	findPlayer();
	// 移動速度を倍速にする
	speed_ = initSpeed_ * 1.5f;
	// 追跡行動
	chaseMove();
	// 画像の方向を合わせる
	/*if (direction_.x != prevDirection_.x)
	animation_.turnAnimation(turnMotion_, direction_.x);*/
	// プレイヤーが追跡距離外か、プレイヤーの間にブロックがあるなら、
	// 捜索状態に遷移
	if (enemyManager_.getPlayerLength() > discoveryLenght_ + 100.0f &&
		!psObj_->isPlayerLook()) {
		changeState(State::Search, ENEMY_WALK);
		turnMotion_ = ENEMY_WALKTURN;
	}
}

// 攻撃行動です
void BaseEnemy::attack()
{
	if (stateTimer_ >= 3.0f)
		changeState(State::Search, ENEMY_WALK);
}

// 被弾行動です
void BaseEnemy::damageMove()
{
	if (stateTimer_ >= 3.0f) {
		changeState(State::Chase, ENEMY_WALK);
		turnMotion_ = ENEMY_ATTACKTURN;
	}
}

// 死亡行動です
void BaseEnemy::deadMove()
{
	animation_.setIsLoop(false);
	name_ = "";
	if (hitTimer_ > 0.1f)
		world_->setIsStopTime(false);
	else {
		world_->setIsStopTime(true);
		// ポーズ中に止める処理
		if (deltaTimer_ == 0.0f && world_->isStopTime())
			hitTimer_ += world_->getDeltaTime();
		//// ポーズ中に止める処理
		//if (deltaTimer_ == 0.0f && !world_->isStopTime())
		//	return;
		//hitTimer_ += world_->getDeltaTime();
		//world_->setIsStopTime(true);
		return;
	}
	//world_->setIsStopTime(false);
	// 所持しているオブジェクトの削除
	for (auto i = objContainer_.begin(); i != objContainer_.end(); i++) {
		auto a = *i;
		a->dead();
	}
	if (!animation_.isEndAnimation()) return;
	// 死亡エフェクトの追加
	world_->addActor(ActorGroup::Effect,
		std::make_shared<EnemyDeadEffect>(
			world_, position_ - Vector2::Up * 325.0f, EFFECT_DEAD));
	dead();
}

// プレイヤーを見失ったときの行動です
void BaseEnemy::lostMove(){}

// 状態の変更を行います
void BaseEnemy::changeState(State state, unsigned int motion)
{
	state_ = state;
	stateTimer_ = 0.0f;
	motion_ = motion;
	// アニメーションの変更
	animation_.changeAnimation(motion);
}

// 所持しているオブジェクトの位置を設定します
void BaseEnemy::setObjPosition()
{
	if (fspScript_ == nullptr) return;
	fspScript_->setPosition(position_);
	wsScript_->setPosition(position_);
}

// プレイヤーを捜索します
void BaseEnemy::findPlayer()
{
	// プレイヤーがいなければ待機状態
	if (player_ == nullptr) {
		changeState(State::Idel, ENEMY_WALK);
		isPlayer_ = false;
		return;
	}
}

void BaseEnemy::searchMove(){}

void BaseEnemy::chaseMove(){}

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
		// エネミーマネージャーに追加
		enemyManager_.addFSP(fspScript);
		objContainer_.push_back(fspScript);
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
	case State::Damage: damageMove(); break;
	case State::Dead: deadMove(); break;
	}

	// スクリーンの幅の半分 + 敵の大きさより大きいなら待機状態にする
	if (!isScreen())
		changeState(State::Idel, ENEMY_WALK);
	prevDirection_ = direction_;
	stateTimer_ += deltaTime;
}

// 捜索オブジェクトの更新
void BaseEnemy::updateSearchObjct()
{
	// 接地していないなら重力加算
	if (!isGround_ && isUseGravity_)
		position_.y += GRAVITY_ * deltaTimer_;
	if (fspScript_ != nullptr) {
		// 壁に当たったら方向転換(X)
		if (wsScript_->isGround())
			direction_.x *= -1.0f;
		// 捜索オブジェクトにプレイヤーの方向を入れる
		wsScript_->setDirection(direction_);
		// 各捜索オブジェクトに位置を入れる
		fspScript_->setPosition(position_);
		wsScript_->setPosition(position_);
	}
}

// 衝突関連の更新
void BaseEnemy::updateCollide()
{
	// bool系列
	// 接地をfalseにする
	isGround_ = false;
	// 最初に衝突直後と衝突後の判定をfalseにする
	isBlockCollideBegin_ = false;
	isBlockCollideExit_ = false;
	// 過去の衝突中がtureで、過去と現在の衝突中が違うなら場合
	// 衝突後になる
	if (isBlockCollidePrevEnter_ &&
		isBlockCollidePrevEnter_ != isBlockCollideEnter_) {
		// 衝突後の判定
		isBlockCollideBegin_ = false;
		isBlockCollideExit_ = true;
	}
	// 過去の衝突中に、現在の衝突中を入れる
	isBlockCollidePrevEnter_ = isBlockCollideEnter_;
	// ブロックに当たっていればtrueになるので、falseを入れる
	isBlockCollideEnter_ = false;
	isMoveFloor_ = false;
}

//地面の位置に補正します
void BaseEnemy::groundClamp(Actor& actor)
{
	if (actor.body_.GetBox().getWidth() == 0) return;
	// 正方形同士の計算
	// 自分自身の1f前の中心位置を取得
	auto pos = body_.GetBox().previousPosition_;
	// 相手側の四角形の4点を取得
	auto topLeft = actor.getBody().GetBox().component_.point[0];
	auto topRight = actor.getBody().GetBox().component_.point[1];
	auto bottomLeft = actor.getBody().GetBox().component_.point[2];
	auto bottomRight = actor.getBody().GetBox().component_.point[3];
	// 外積を使って、縦の長さを計算する
	auto top = Vector2::Cross(
		(topLeft - topRight).Normalize(), (pos - topRight));
	auto bottom = Vector2::Cross(
		(bottomRight - bottomLeft).Normalize(), (pos - bottomLeft));
	auto right = Vector2::Cross(
		(topRight - bottomRight).Normalize(), (pos - bottomRight));
	auto left = Vector2::Cross(
		(bottomLeft - topLeft).Normalize(), (pos - topLeft));
	// Y方向に位置を補間する
	if (left < body_.GetBox().getWidth() / 2.0f &&
		right < body_.GetBox().getWidth() / 2.0f) {
		// 上に補間
		if (top > 0) {
			position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
			// 接地
			isGround_ = true;
		}
		// 下に補間
		if (bottom > 0)
			position_.y = bottomRight.y + body_.GetBox().getHeight() / 2.0f;
	}
	// X方向に位置を補間する
	if (top < body_.GetBox().getHeight() / 2.0f &&
		bottom < body_.GetBox().getHeight() / 2.0f) {
		// 左に補間
		if (left > 0)
			position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;
		// 右に補間
		if (right > 0)
			position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;
	}
}

// 円と衝突したときに位置に補正します
void BaseEnemy::circleClamp(Actor & actor)
{
	// 当たった円とのベクトルを計算して、位置を補間します
	// 当たったオブジェクトが円でない場合(てきとう)
	if (actor.getBody().GetCapsule().getRadius() == 0) return;
	// 過去の位置を取得
	auto pos = body_.GetBox().previousPosition_;
	auto direction = actor.getPosition() - pos;
	// 矩形の補間
	auto lerpVelo = Vector2(
		(actor.getBody().GetCircle().getRadius() +
			body_.GetBox().getWidth() / 2.0f) * direction.Normalize().x,
		(actor.getBody().GetCircle().getRadius() +
			body_.GetBox().getHeight() / 2.0f) * direction.Normalize().y
		);
	position_ += lerpVelo;
}

// テクスチャの追加を行います
void BaseEnemy::addAnimation()
{
	// 敵の画像に合わせて調整
	animation_.addAnimation(
		ENEMY_WALK,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_EGGENEMY_WALK_TEX));
	animation_.addAnimation(
		ENEMY_WALKTURN,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_EGGENEMY_WALKTURN_TEX));
	animation_.addAnimation(
		ENEMY_DISCOVERY,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_EGGENEMY_DISCORVER_TEX));
	animation_.addAnimation(
		ENEMY_ATTACK,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_EGGENEMY_ATTACK_TEX));
	animation_.addAnimation(
		ENEMY_ATTACKTURN,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_EGGENEMY_ATTACKTURN_TEX));
	animation_.addAnimation(
		ENEMY_DAMAGE,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_EGGENEMY_DAMAGE_TEX));
}

// プレイヤーとのX方向とY方向を計算し、画面外にいるかを返します
bool BaseEnemy::isScreen()
{
	if (std::abs(enemyManager_.getPlayerVector().x) <= 
		(SCREEN_SIZE.x - SCREEN_SIZE.x / 12) + body_.GetBox().getWidth() &&
		std::abs(enemyManager_.getPlayerVector().y) <= 
		(SCREEN_SIZE.y - SCREEN_SIZE.x / 12) + body_.GetBox().getHeight()) {
		isScreen_ = true;
		return true;
	}
	isScreen_ = false;
	// 画面外
	return false;
}