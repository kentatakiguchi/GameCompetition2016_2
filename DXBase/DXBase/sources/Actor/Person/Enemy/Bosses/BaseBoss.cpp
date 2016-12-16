#include "BaseBoss.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../../../Base/ActorGroup.h"
#include "../../../Body/CollisionBase.h"
#include "../../../../Define.h"
#include "BossManager.h"
#include "BossEntry.h"
#include "BossHeart.h"
#include "../FloorSearchPoint.h"
#include "bossAttack/importBossAttack.h"
#include "Effect/ImportEffects.h"
// ボスの体力表示
#include "../../../UIActor/BossGaugeUI/BossGaugeUI.h"

// ボスクラス(ベース予定)
BaseBoss::BaseBoss(
	IWorld * world,
	const Vector2 & position,
	const float bodyScale) :
	Actor(world, "BaseBoss", position,
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	dp_(10),
	initDp_(dp_),
	hp_(3),
	flinchCount_(0),
	angleCount_(0),
	starCreateCount_(0),
	// initHp_(hp_),
	stateTimer_(0.0f),
	timer_(0.0f),
	deltaTimer_(0.0f),
	damageTimer_(0.0f),
	angle_(0.0f),
	isGround_(false),
	isBottomHit_(false),
	isBodyHit_(true),
	isAttackHit_(true),
	isSceneEnd_(false),
	isBattle_(false),
	stateString_("待機"),
	// bossManager_(nullptr),
	playerPastPosition_(Vector2::Zero),
	direction_(Vector2::One),
	player_(nullptr),
	state_(State::BattleIdel),
	attackState_(AttackState::JumpAttack),
	animeNum_(BossAnimationNumber::WAIT_NUMBER),
	animation_(EnemyAnimation2D()),
	wspObj_(nullptr),
	entryObj_(nullptr),
	heartObj_(nullptr),
	bossGaugeUI_(nullptr),
	bossManager_(BossManager(world, position)),
	top_(0.0f), bottom_(0.0f), right_(0.0f), left_(0.0f),
	handle_(CreateFontToHandle(NULL, 50, 10, DX_FONTTYPE_NORMAL)),
	movePos_(Vector2::Zero),
	moveSpeed_(0.0f)
{
	// コンテナに追加(攻撃順に追加する)
	asContainer_.push_back(AttackState::JumpAttack);
	asContainer_.push_back(AttackState::WallAttack);
	asContainer_.push_back(AttackState::SpeacialAttack);
	// ボスマネージャー
	// 攻撃コンテナに追加
	bossManager_.addAttack(std::make_shared<ThreeJumpAttack>(world_, position));
	bossManager_.addAttack(std::make_shared<WallAttack>(world_, position));
	bossManager_.addAttack(std::make_shared<DysonAttack>(world_, position));
	/*auto manager = std::make_shared<BossManager>(position);
	bossManager_ = &*manager;*/

	stars_.clear();

	// アニメーションの追加
	addAnimation();
	animation_.changeAnimation(
		static_cast<int>(BossAnimationNumber::WAIT_NUMBER));

	// 床捜索オブジェクト
	auto wspObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(
			body_.GetCircle().getRadius(),
			body_.GetCircle().getRadius()), 10.0f);
	world_->addActor(ActorGroup::Enemy, wspObj);
	wspObj_ = &*wspObj;
	// ボス入口オブジェクト
	auto entryObj = std::make_shared<BossEntry>(
		world_, position_, 
		Vector2(bodyScale / 2.0f, -bodyScale / 2.0f),
		bodyScale / 2.0f);
	world_->addActor(ActorGroup::Enemy, entryObj);
	entryObj_ = &*entryObj;
	// ボス心臓オブジェクト
	auto heartHP = 100;
	auto heartObj = std::make_shared<BossHeart>(
		world_, Vector2(1080.0f, CHIPSIZE * 20), heartHP, hp_);
	world_->addActor(ActorGroup::Enemy, heartObj);
	heartObj_ = &*heartObj;
	// ボスの体力ゲージ
	auto bossUI = std::make_shared<BossGaugeUI>(world_, Vector2::Zero);
	world_->addUIActor(bossUI);
	bossGaugeUI_ = bossUI.get();
	bossGaugeUI_->SetHp(heartObj_->getHeartHp() * hp_);

	body_.enabled(false);
}

BaseBoss::~BaseBoss()
{
}

void BaseBoss::onUpdate(float deltaTime)
{
	clampList_.clear();

	// 補間タイマ(最大値１)の更新
	setTimer(deltaTime);
	// 体力の更新
	hp_ = heartObj_->getBossHp();
	bossGaugeUI_->SetHp(heartObj_->getHeartHp());
	bossManager_.setHeartHP(heartObj_->getHeartHp());
	// アニメーションの更新
	animation_.update(deltaTime);
	//animation_.onUpdate(deltaTime);

	entryObj_->setBossPosition(position_);
	wspObj_->setPosition(position_);
	// wspObj_->setDirection(direction_);
	// 状態の更新
	updateState(deltaTime);
	// 接地(仮)
	bossManager_.setIsGround(isGround_);
	bossManager_.setIsBottom(isBottomHit_);

	if (damageTimer_ > 0) {
		damageTimer_ -= deltaTime;
	}
	
	// bool系
	isGround_ = false;
	isBottomHit_ = false;
}

void BaseBoss::onDraw() const
{
	// デバッグ
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	//// 状態の表示
	//DrawString(
	//	vec3Pos.x, vec3Pos.y - 100,
	//	stateChar, GetColor(255, 255, 255));
	//// 体力の表示
	//DrawFormatString(
	//	vec3Pos.x, vec3Pos.y - 150,
	//	GetColor(255, 255, 255), "体力:%d", hp_);
	//DrawFormatString(
	//	vec3Pos.x, vec3Pos.y - 175,
	//	GetColor(255, 255, 255), "時間:%d", (int)stateTimer_);
	// アニメーションの描画
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	animation_.draw(
		pos - Vector2::Up * 10,
		Vector2::One * (body_.GetCircle().getRadius()) + Vector2::Up * 20,
		body_.GetCircle().getRadius() / (128 / 2), angle_);
	//body_.draw(inv_);
}

void BaseBoss::onCollide(Actor & actor)
{
	auto actorName = actor.getName();

	// ブロックの下側にぶつかったら、落ちるようにする?
	// プログラムを書いて、コメントアウトする
	// マップのブロックに当たったら、処理を行う
	if (actorName == "MovelessFloor") {
		// 位置の補間
		groundClamp(actor);
		bossManager_.setFloorName(actorName.c_str());
		return;
	}
	// 空中に浮かぶ床に当たったら、ひるみカウントを加算する
	if (actorName == "BossAreaFloor") {
		// 位置の補間
		/*if (state_ == State::Attack)
			flinchCount_++;*/
		groundClamp(actor);
		bossManager_.setFloorName(actorName.c_str());
		return;
	}
	// 特定の状態ではプレイヤーに触れても何も起こらないようにする
	if (state_ == State::Flinch || state_ == State::Dead) return;
	if (damageTimer_ > 0) return;
	// プレイヤーの攻撃範囲に当たった場合の処理
	if (actorName == "Player_AttackCollider") {
		// プレイヤーの攻撃に当たらない場合は返す
		if (!isAttackHit_) return;
		// ダメージ処理
		damage(3);
		damageTimer_ = 1.0f;// *60.0f;
		return;
	}
	// プレイヤー本体に当たった場合の処理
	if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
		// プレイヤーに当たらない場合は返す
		if (!isBodyHit_) return;
		// ダメージ処理
		damage(1);
		damageTimer_ = 1.0f;// *60.0f;
		// もしものためのreturn
		return;
	}
}

void BaseBoss::onMessage(EventMessage event, void *)
{
}

// シーンを終了させるかを返します
bool BaseBoss::isSceneEnd()
{
	return isSceneEnd_;
}

// 目的地に移動します
void BaseBoss::movePosition()
{
	/*movePos_ = position;
	moveSpeed_ = speed;*/
	// 自分の位置が
	auto distance = movePos_ - position_;
	//auto thisSpeed = speed;
	// 目的地と速度の差が速度以下なら、位置を変える
	if (distance.Length() < moveSpeed_) {
		position_ = movePos_;
		//return true;
	}
	else
		position_ += Vector2::Normalize(distance) * moveSpeed_;
}

// 戦闘を開始するかを返します
void BaseBoss::setIsBattle(bool isBattle)
{
	isBattle_ = isBattle;
}

// 目的の位置を設定します
void BaseBoss::setMovePosition(const Vector2 & position, const float speed)
{
	movePos_ = position;
	moveSpeed_ = speed;
}

bool BaseBoss::isMovePosition()
{
	if (movePos_.x == position_.x && 
		movePos_.y == position_.y)
		return true;
	return false;
}

void BaseBoss::updateState(float deltaTime)
{
	// 現在は使用不可
	// player_ = world_->findActor("Player");
	player_ = world_->findActor("PlayerBody1");

	if (hp_ <= 0)
		changeState(State::Dead, BossAnimationNumber::DEATH_NUMBER);

	switch (state_)
	{
	case State::BattleIdel: battleIdel(deltaTime); break;
	case State::Idel: idel(deltaTime); break;
	case State::Attack: attack(deltaTime); break;
	case State::Flinch: flinch(deltaTime); break;
	case State::Dead: deadMove(deltaTime); break;
	}

	stateTimer_ += deltaTime;
	// 位置の更新
	//position_ = bossManager_->getMovePosition();
}

void BaseBoss::changeState(State state, BossAnimationNumber num)
{
	// 同じ状態なら返す
	if (state_ == state) return;
	state_ = state;
	stateTimer_ = 0.0f;
	angle_ = 0.0f;
	// アニメーションの変更
	animation_.changeAnimation(static_cast<int>(num));
}

void BaseBoss::changeAttackState(AttackState aState, BossAnimationNumber num)
{
	// 攻撃状態に強制遷移する
	//if (attackState_ == aState) return;
	changeState(State::Attack, num);
	attackState_ = aState;
	bossManager_.prevPosition();
}

// 戦闘待機状態
void BaseBoss::battleIdel(float deltaTime)
{
	// 目的地が設定されていないなら返す
	if (movePos_.x == Vector2::Zero.x && 
		movePos_.y == Vector2::Zero.y) return;

	// 目的地に移動
	movePosition();

	// バトル開始でないなら
	if (!isBattle_) return;
	// 待機状態に遷移
	//changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
	changeAttackState(AttackState::JumpAttack,
		BossAnimationNumber::JUMP_UP_NUMBER);
	body_.enabled(true);
}

void BaseBoss::idel(float deltaTime)
{
	stateString_ = "待機状態";
	// プレイヤーが取得できていれば、エネミーマネージャーに位置などを入れる
	setBMStatus();
	// 攻撃が当たるかの判定を入れる
	isAttackHit_ = true;
	isBodyHit_ = true;
	// 画像の方向を合わせる
	animation_.turnAnimation(motion_, direction_.x);

	bossManager_.changeAttackNumber(asContainer_.size() - hp_);
	// 一定時間経過で攻撃状態に遷移
	if (stateTimer_ >= 5.0f) {
		// 残り体力で攻撃状態を変える
		// initHp - hp
		changeAttackState(
			asContainer_[asContainer_.size() - hp_],
			BossAnimationNumber::JUMP_UP_NUMBER);

		//bossManager_.changeAttackNumber(asContainer_.size() - hp_);
		return;
	}
	// 重力
	if (!isGround_ && bossManager_.isUseGravity()) {
		position_.y += 9.8f * (1.0f);// * 60.0f);
	}
}

void BaseBoss::attack(float deltaTime)
{
	// 攻撃状態の選択
	switch (attackState_) {
	case AttackState::JumpAttack: jumpAttack(deltaTime); break;
	case AttackState::WallAttack: wallAttack(deltaTime); break;
	case AttackState::SpeacialAttack: specialAttack(deltaTime); break;
	}
	// 
	animation_.setIsLoop(bossManager_.isAnimeLoop());

	/*if(!bossManager_.isAttackEnd())
		animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));*/
	// 攻撃が当たるかの判定を入れる
	isAttackHit_ = bossManager_.IsAttackHit();
	isBodyHit_ = bossManager_.IsBodyHit();

	// 攻撃が終了したら、待機状態に遷移
	//if (bossManager_->isAttackEnd()) {
	//	changeState(State::Idel, BOSS_IDLE);
	//	// ボスマネージャーの内部値をリフレッシュ
	//	bossManager_->attackRefresh();
	//}
}

void BaseBoss::flinch(float deltaTime)
{
	stateString_ = "ひるみ";
	entryObj_->setIsEntry(true);
	flinchCount_ = 0;
	animation_.setIsLoop(true);

	if (starCreateCount_ % 50 == 0 && stars_.size() < 6){
		auto addPos = Vector2(-80, 100);
		auto star = std::make_shared<PiyoriEffect>(world_, position_ - addPos);
		world_->addActor(ActorGroup::Effect, star);
		stars_.push_back(star);
	}
	starCreateCount_++;

	// 重力
	if (position_.y < FIELD_SIZE.y) {
		position_.y += 9.8f * (1.0f);// * 60.0f);
	}

	//// 体内に入った場合、体力を減らす
	//if (entryObj_->isEntered()) {
	//	entryObj_->letOut();
	//	entryObj_->setIsEntry(false);
	//	heartObj_->addBossHp(-50);
	//	changeState(State::Idel, BOSS_IDLE);
	//}

	// 体内に入っていたら、ハートに入ったことを知らせる
	if (entryObj_->isEntered() && !heartObj_->isLetOut()) {
		// プレイヤーが出てきたら、待機状態にする
		//stateTimer_ = 5.0f;
		stateTimer_ = 5.0f;
		heartObj_->setIsEntered(true);
		heartObj_->addBossHp(-50);
		entryObj_->letOut();
	}
	// 体内に入ったら何かする
	if (entryObj_->isEntered()) {
		// プレイヤーを追い出せていないなら返す
		if (!heartObj_->isLetOut()) return;
		// プレイヤーが出てきた
		entryObj_->letOut();
	}
	// 体力が0になったら死亡
	if (hp_ <= 0) {
		changeState(State::Dead, BossAnimationNumber::DEATH_NUMBER);
		return;
	}
	// 一定時間経過で待機状態に遷移
	if (stateTimer_ < 5.0f) return;
	changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
	entryObj_->setIsEntry(false);
	dp_ = initDp_;
	// スターの削除
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto star = *i;
		star->dead();
	}
	stars_.clear();
	starCreateCount_ = 0;
	//flinchCount_ = 3;
}

void BaseBoss::deadMove(float deltaTime)
{
	stateString_ = "死亡";
	animation_.setIsLoop(false);
	if (animation_.isEndAnimation()) {
		// アニメーションを停止させる
		//dead();
	}
	// 死亡から一定時間経過なら、シーンを終了させる
	if (stateTimer_ >= 3.0f)
		isSceneEnd_ = true;
	//dead();
}

void BaseBoss::jumpAttack(float deltaTime)
{
	stateString_ = "ジャンプ攻撃";
	// プレイヤー本体に当たらない
	//isBodyHit_ = false;
	// ジャンプ攻撃
	bossManager_.attackMove(deltaTime);
	bossManager_.setPlayerPosition(player_->getPosition());
	position_ = bossManager_.getMovePosition();
	// アニメーションの変更
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	animation_.turnAnimation(motion_, bossManager_.getAttackDirection().x);
	// ジャンプ攻撃が終わったら、待機状態にする
	if (bossManager_.isAttackEnd()) {
		changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
		//isBodyHit_ = true;
		bossManager_.attackRefresh();
	}
}

void BaseBoss::wallAttack(float deltaTime)
{
	stateString_ = "壁攻撃";
	bossManager_.attackMove(deltaTime);
	position_ = bossManager_.getMovePosition();
	// アニメーションの変更
	angle_ = bossManager_.getAnimeAngle();
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	animation_.turnAnimation(motion_, Vector2::Left.x);
	// 攻撃動作中なら、壁捜索オブジェクトなどの判定をONにする
	if (bossManager_.isAttackStart()) {
		setBMStatus();
		bossManager_.getPlayerNormalizeDirection();
	}
	// ジャンプ攻撃が終わったら、待機状態にする
	if (bossManager_.isAttackEnd()) {
		//flinchCount_ = 0;
		flinchCount_++;
		//if (flinchCount_ == 0)
		// 攻撃側のひるみ回数と以上なら、ひるみ状態に遷移
		if (bossManager_.getFlinchCount() <= flinchCount_) {
			changeState(State::Flinch, BossAnimationNumber::PIYO_NUMBER);
			bossManager_.attackRefresh();
			flinchCount_ = 0;
			return;
		}
		else {
			changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
			bossManager_.attackRefresh();
			return;
		}
	}
}

void BaseBoss::specialAttack(float deltaTime)
{
	// 口にプレイヤー同士をつなぐ線が当たり、
	// ひるむ時間に達するまでに
	// 口から離れたら、もう一度攻撃を行う

	if (bossManager_.isFlinch()) {
		changeState(State::Flinch, BossAnimationNumber::PIYO_NUMBER);
		bossManager_.attackRefresh();
		//angleCount_ = 0;
		//angle_ = 0.0f;
		return;
	}

	stateString_ = "スペシャルな攻撃";
	// isBlock() == true => 塞がれている
	bossManager_.setIsAttackMove(!entryObj_->isBlock());
	bossManager_.attackMove(deltaTime);
	position_ = bossManager_.getMovePosition();
	// 角度の変更
	//angle_ = bossManager_.getAngle();

	// 壁に当たっている場合
	bossManager_.setIsWallHit(wspObj_->isGround());
	wspObj_->setDirection(bossManager_.getWallMoveDirection());
	// アニメーションの変更
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	animation_.turnAnimation(motion_, bossManager_.getAttackDirection().x);
	// bossManager_.specialAttack(deltaTime);
	/*if (entryObj_->isBlock()) {

	}*/

	if (bossManager_.isAttackEnd()) {
		changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
		bossManager_.attackRefresh();
		//angleCount_ = 0;
		//angle_ = 0.0f;
	}
}

void BaseBoss::setTimer(float deltaTime)
{
	timer_ = deltaTime * 60.0f;
}

// ボスマネージャーのステータスの設定
void BaseBoss::setBMStatus()
{
	if (player_ != nullptr) {
		bossManager_.setPlayerPosition(player_->getPosition());
		bossManager_.setPosition(position_);
		// 方向を入れる
		auto direction = bossManager_.getPlayerDirection();
		direction_ = direction;
		//wspObj_->setDirection(direction);
		// 壁に当たっている場合
		bossManager_.setIsWallHit(wspObj_->isGround());
		if (wspObj_->isGround()) {
			wspObj_->setDirection(bossManager_.getWallMoveDirection());
		}
		wspObj_->setDirection(bossManager_.getWallMoveDirection());
		/*if (wspObj_->isGround()) {
			
		}*/

		// 戻す y = -1.0fに
		// direction.y = -1.0f;
		direction.y = 1.0f;
		entryObj_->setDirection(direction);
	}
}

// 指定した値のダメージ量を加算します
void BaseBoss::damage(const int damage)
{
	dp_ -= damage;
	// 耐久値が0になったら、ひるむ
	if (dp_ <= 0) {
		changeState(State::Flinch, BossAnimationNumber::PIYO_NUMBER);
		// 衝突するかどうかの bool を全てtrueにする
		isBodyHit_ = true;
		isAttackHit_ = true;
		setBMStatus();
		// 画像の方向を合わせる
		animation_.turnAnimation(motion_, direction_.x);

		//body_.enabled(false);
	}
}

//地面の位置に補正します
void BaseBoss::groundClamp(Actor& actor)
{
	if (actor.body_.GetBox().getWidth() == 0) return;
	// 新円と正方形の衝突判定
	// 自分自身の1f前の中心位置を取得
	auto isHit = false;
	auto pos = body_.GetCircle().previousPosition_;
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

	top_ = top;
	bottom_ = bottom;
	right_ = right;
	left_ = left;
	// 過去の位置
	// Y方向に位置を補間する
	if (left < 0 &&
		right < 0) {
		// 上に補間
		if (top > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = topLeft.y - body_.GetCircle().getRadius();
			// 接地
			isGround_ = true;
			isHit = true;
		}
		// 下に補間
		if (bottom > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
			// ブロックの下側に当たった
			isBottomHit_ = true;
			isHit = true;
		}
	}
	// X方向に位置を補間する
	else if (top < 0 &&
		bottom < 0) {
		// 左に補間
		if (left > 0) {
			position_.x = bottomLeft.x - body_.GetCircle().getRadius();
			isHit = true;
		}
		// 右に補間
		if (right > 0) {
			position_.x = topRight.x + body_.GetCircle().getRadius();
			isHit = true;
		}
	}
	bossManager_.setPosition(position_);
	bossManager_.prevPosition();
	if (isHit) return;

	// 現在の判定
	pos = position_;
	// 外積を使って、縦の長さを計算する
	top = Vector2::Cross(
		(topLeft - topRight).Normalize(), (pos - topRight));
	bottom = Vector2::Cross(
		(bottomRight - bottomLeft).Normalize(), (pos - bottomLeft));
	right = Vector2::Cross(
		(topRight - bottomRight).Normalize(), (pos - bottomRight));
	left = Vector2::Cross(
		(bottomLeft - topLeft).Normalize(), (pos - topLeft));
	// Y方向に位置を補間する
	if (left < 0 &&
		right < 0) {
		// 上に補間
		if (top > -actor.getBody().GetBox().getHeight() / 2.0f) {
			position_.y = topLeft.y - body_.GetCircle().getRadius();
			// 接地
			isGround_ = true;
		}
		// 下に補間
		if (bottom > -actor.getBody().GetBox().getHeight() / 2.0f) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
			// ブロックの下側に当たった
			isBottomHit_ = true;
		}
	}
	// X方向に位置を補間する
	if (top < 0 &&
		bottom < 0) {
		// 左に補間
		if (left > -actor.getBody().GetBox().getWidth() / 2.0f)
			position_.x = bottomLeft.x - body_.GetCircle().getRadius();
		// 右に補間
		if (right > -actor.getBody().GetBox().getWidth() / 2.0f)
			position_.x = topRight.x + body_.GetCircle().getRadius();
	}
	bossManager_.setPosition(position_);
	bossManager_.prevPosition();

	// 60
	// 160
	//// 左に補間
	//if (left > -14)
	//	position_.x = bottomLeft.x - body_.GetCircle().getRadius();
	//// 右に補間
	//if (right > -body_.GetCircle().getRadius())
	//	position_.x = topRight.x + body_.GetCircle().getRadius();

	/*if (top >= 0 && left <= 0 && right <= 0) {
		position_.y = t_left.y - PLAYER_RADIUS;
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
		position_ = center + (pos - center).Normalize() * (t_left - center).Length();
	}*/

	//float r2 = body_.GetCircle().getRadius() * body_.GetCircle().getRadius();
	//Vector2 topV = topRight - topLeft;
	//Vector2 v1 = position_ - topLeft;
	//float t = Vector2::Dot(topV, v1) / Vector2::Dot(topV, topV);
	//Vector2 vn =t * topV;
	//// Vector2 vn = v1 - t * v;
	////if (0 < t && t < 1 && vn.LengthSquared() <= r2) {
	////	// pc = p1 + v * t + r * Vector2.Normalize(vn); // 中心を移動
	////	position_ = topLeft + topV * t + body_.GetCircle().getRadius() *
	////		Vector2::Normalize(vn);
	////}
	//top_ = vn.Length();
}

// テクスチャの追加を行います
void BaseBoss::addAnimation()
{
	auto texSize = 256;
	// 敵の画像に合わせて調整
	// 待機
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::WAIT_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_WAIT_TEX),
		texSize, 8, 4, 1);
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::WAIT_TURN_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_WAIT_TURN_TEX),
		texSize, 8, 2);
	// ジャンプ攻撃
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::JUMP_UP_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_JUMP_UP_TEX),
		texSize, 8, 3, 3);
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::JUMP_DOWN_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_JUMP_DOWN_TEX),
		texSize, 8, 4);
	// 壁移動攻撃
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::WALLATTACK_DASH_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_WALLATTACK_DASH_TEX),
		texSize, 8, 2, 5);
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::WALLATTACK_DASHJUMP_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_WALLATTACK_DASHJUMP_TEX),
		texSize, 8, 2, 4);
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::WALLATTACK_DASHJUMP_STOP_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_WALLATTACK_DASHJUMP_STOP_TEX),
		texSize, 8, 3, 3);
	// 吸い込み攻撃
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::BREATH_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_BREATH_TEX),
		texSize, 8, 4);
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::BREATH_TURN_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_BREATH_TURN_TEX),
		texSize, 8, 2);
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::BREATH_DYSFUNCTION_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_BREATH_DYSFUNCTION_TEX),
		texSize, 8, 4);
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::BREATH_LESS_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_BREATH_LESS_TEX),
		texSize, 8, 4);
	// 怯み
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::PIYO_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_PIYO_TEX),
		texSize, 8, 4);
	// ダメージ
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::DAMAGE_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_DAMAGE_TEX),
		texSize, 7, 2, 2);
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::DAMAGE_BOKO_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_DAMAGE_BOKO_TEX),
		texSize, 8, 4);
	// 死亡
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::DEATH_NUMBER),
		ResourceLoader::GetInstance().getTextureID(
			TextureID::BOSS_DEATH_TEX),
		texSize, 8, 4);
}