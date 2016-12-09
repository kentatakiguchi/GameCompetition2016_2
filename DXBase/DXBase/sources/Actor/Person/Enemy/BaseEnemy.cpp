#include "BaseEnemy.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"
#include "FloorSearchPoint.h"
#include "PlayerSearchObj.h"
#include "DeadEnemy.h"

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
	speed_(1.0f),
	initSpeed_(speed_),
	scale_(bodyScale),
	direction_(direction),
	playerLength_(0.0f),
	isPlayer_(false),
	isMove_(false),
	isBlockCollideBegin_(false),
	isBlockCollideEnter_(false),
	isBlockCollidePrevEnter_(false),
	isBlockCollideExit_(false),
	isGround_(false),
	isUseGravity_(true),
	isInvincible_(false),
	discoveryLenght_(125),
	stateTimer_(0.0f),
	state_(State::Idel),
	stateString_(""),
	discoveryPosition_(Vector2::Zero),
	addTexPosition_(Vector2(0.0f, 40.0f)),
	player_(nullptr),
	psObj_(nullptr),
	fspScript(nullptr),
	wsScript(nullptr),
	pricleObj_(nullptr),
	enemyManager_(EnemyManager(position, direction)),
	animation_(EnemyAnimation2D()),
	handle_(0)
{
	//Initialize();

	// rayオブジェクトの追加
	// auto player = world_->findActor("PlayerBody1");
	auto player = world_->findActor("PlayerBody1");
	if (player != nullptr) {
		auto ray = std::make_shared<PlayerSearchObj>(
			world_, position_, player->getPosition());
		world_->addActor(ActorGroup::EnemyBullet, ray);
		psObj_ = &*ray;
		objContainer_.push_back(psObj_);
		isPlayer_ = true;
	}

	//// アニメーションの追加
	//addAnimation();
	//animation_.changeAnimation(ENEMY_WALK);

	// フォントハンドルの追加
	handle_ = CreateFontToHandle("ＭＳ 明朝", 40, 10, DX_FONTTYPE_NORMAL);
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
	/*auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector2(0.0f, 0.0f + scale_ / 2.0f), position_);*/
	auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, 0.0f + scale_ / 2.0f),
		Vector2(scale_, 2.0f));
	// ワールドに追加
	world_->addActor(ActorGroup::Enemy, fsObj);
	fspScript = &*fsObj;
	objContainer_.push_back(fspScript);
	fspScript->setPosition(position_);
	// 壁捜索オブジェクト
	/*auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector2(-scale_ / 2.0f, 0.0f), position_);*/
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, position_, 
		Vector2(scale_ / 2.0f, 0.0f),
		Vector2(2.0f, scale_- 30.0f));
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsScript = &*wsObj;
	objContainer_.push_back(wsScript);
	// アニメーションの追加
	addAnimation();
	animation_.changeAnimation(ENEMY_WALK);
}

void BaseEnemy::onUpdate(float deltaTime)
{
	/*enemyManager_.setEMPosition(position_, world_->findActor("PlayerBody01")->getPosition(), direction_);
	playerLength_ = enemyManager_.getPlayerLength();
	if (playerLength_ >=
		SCREEN_SIZE.x / 2.0f + body_.GetBox().getHeight())
		return;*/
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

	// アニメーションの変更
	//animation_.change(motion_);
	// アニメーションの更新
	//animation_.update(deltaTime);
}

void BaseEnemy::onDraw() const
{
	if (playerLength_ >=
		SCREEN_SIZE.x / 2.0f + body_.GetBox().getHeight())
		return;
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// 敵の表示
	/*DrawGraph(
		vec3Pos.x - scale_ / 2.0f, vec3Pos.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);*/
	// 文字の表示
	DrawString(
		vec3Pos.x - scale_, vec3Pos.y - 20 - scale_,
		stateChar, GetColor(255, 255, 255));
	// デバッグ
	body_.draw(inv_);
	// アニメーションの描画
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	animation_.draw(
		pos, Vector2::One * (body_.GetBox().getWidth() * 2) + addTexPosition_,
		0.5f, 0);
}

void BaseEnemy::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	// プレイヤー関連のオブジェクトに当たっているなら
	auto getFloorName = strstr(actorName.c_str(), "Floor");
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
		// 判定を一回のみにするので消す
		//body_.enabled(false);
		return;
	}

	// 死亡中は行わない
	if (state_ == State::Dead) return;
	// プレイヤーに当たらない？
	// PlayerのActorGroupが変わるので、 Player_AttackRangeに当たるようにする
	if ((actorName == "PlayerBody2" ||
		actorName == "PlayerBody1" || 
		actorName == "Player_AttackCollide") &&
		!isInvincible_) {
		// ダメージ
		// groundClamp(actor);
		circleClamp(actor);
		/*hp_ -= 10;
		if (hp_ <= 0) changeState(State::Dead, ENEMY_DEAD);
		else changeState(State::Damage, ENEMY_DAMAGE);*/
		changeState(State::Dead, ENEMY_DAMAGE);
		isUseGravity_ = true;
		return;
		/*body_.enabled(false);
		return;*/
	}
}

void BaseEnemy::onMessage(EventMessage event, void *)
{
}

// 子供用のupdate(親のupdate前に行います)
void BaseEnemy::beginUpdate(float deltaTime){}

// 子供用のupdate
void BaseEnemy::update(float deltaTime){}

// 待機状態です
void BaseEnemy::idle()
{
	stateString_ = "待機";
	// プレイヤーとの距離を計算して、
	// スクリーンの幅の半分 + 敵の大きさよりちいさいなら動く
	if (enemyManager_.getPlayerLength() < 
		SCREEN_SIZE.x / 2.0f + body_.GetBox().getHeight())
		changeState(State::Search, ENEMY_WALK);
}
// 索敵移動です(デフォルト)
void BaseEnemy::search()
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
		changeState(State::Discovery, ENEMY_DISCOVERY);
		discoveryPosition_ = position_;
	}
	//else if(enemyManager_.getPlayerLength() >= 100) changeState(State::Idel, ENEMY_IDLE);
}

// プレイヤーを発見した時の行動です
void BaseEnemy::discovery()
{
	isUseGravity_ = false;
	stateString_ = "発見";
	// ジャンプモーション
	position_.y += (-0.5f + stateTimer_) * GRAVITY_ * deltaTimer_;
	// ジャンプ後に床に接地したら追跡状態に遷移
	if (isGround_ && stateTimer_ >= 0.2f) {
		changeState(State::Chase, ENEMY_ATTACK);
		//animation_.turnAnimation(ENEMY_ATTACK);
		isUseGravity_ = true;
	}
}

// プレイヤーの追跡行動です(デフォルト)
void BaseEnemy::chase()
{
	// プレイヤーの捜索
	findPlayer();
	stateString_ = "追跡";
	// 移動速度を倍速にする
	speed_ = initSpeed_ * 1.5f;
	// 追跡行動
	chaseMove();
	// プレイヤーが追跡距離外か、プレイヤーの間にブロックがあるなら、
	// 捜索状態に遷移
	if (enemyManager_.getPlayerLength() > discoveryLenght_ + 30.0f &&
		!psObj_->isPlayerLook())
		changeState(State::Search, ENEMY_WALK);
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
		changeState(State::Search, ENEMY_WALK);
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
	// 所持しているオブジェクトの削除
	for (auto i = objContainer_.begin(); i != objContainer_.end(); i++) {
		auto a = *i;
		a->dead();
	}
	// 死亡アニメーションオブジェクトの追加
	/*world_->addActor(ActorGroup::Effect, std::make_shared<DeadEnemy>(
		world_, position_, body_.GetBox().getSize()));*/
	dead();
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
	// アニメーションの変更
	animation_.changeAnimation(motion);
}

// 所持しているオブジェクトの位置を設定します
void BaseEnemy::setObjPosition()
{
	if (fspScript == nullptr) return;
	fspScript->setPosition(position_);
	wsScript->setPosition(position_);
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

	// スクリーンの幅の半分 + 敵の大きさより大きいなら待機状態にする
	if (enemyManager_.getPlayerLength() >=
		SCREEN_SIZE.x / 2.0f + body_.GetBox().getHeight())
		changeState(State::Idel, ENEMY_WALK);

	stateTimer_ += deltaTime;
}

// 捜索オブジェクトの更新
void BaseEnemy::updateSearchObjct()
{
	// 接地していないなら重力加算
	//if (!fspScript->isGround() && isUseGravity_)
	if (!isGround_ && isUseGravity_)
		position_.y += GRAVITY_ * deltaTimer_;
	if (fspScript != nullptr) {
		// 壁に当たったら方向転換(X)
		if (wsScript->isGround())
			direction_.x *= -1.0f;
		// 捜索オブジェクトにプレイヤーの方向を入れる
		wsScript->setDirection(direction_);
		// 各捜索オブジェクトに位置を入れる
		fspScript->setPosition(position_);
		wsScript->setPosition(position_);
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
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_EGGENEMY_WALK_TEX),
		texSize_, 8, 4, 1);
	animation_.addAnimation(
		ENEMY_DISCOVERY,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_EGGENEMY_DISCORVER_TEX),
		texSize_, 8, 2);
	animation_.addAnimation(
		ENEMY_ATTACK,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_EGGENEMY_ATTACK_TEX),
		texSize_, 8, 2);
	animation_.addAnimation(
		ENEMY_DAMAGE,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_EGGENEMY_DAMAGE_TEX),
		texSize_, 8, 2);
}
