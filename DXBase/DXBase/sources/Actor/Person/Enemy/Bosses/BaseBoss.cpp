#include "BaseBoss.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../../../Base/ActorGroup.h"
#include "../../../Body/CollisionBase.h"
#include "../../../../Define.h"
#include "BossManager.h"
#include "BossEntry.h"
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
	Actor(world, "BaseEnemy", position,
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	dp_(10),
	hp_(300),
	attackCount_(0),
	flinchCount_(0),
	piyoriCount_(5),
	angleCount_(0),
	starCreateCount_(0),
	bockCreateCount_(0),
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
	//animeNum_(BossAnimationNumber::WAIT_NUMBER),
	animeNum_(WAIT_NUMBER),
	animation_(EnemyAnimation2D()),
	wspObj_(nullptr),
	entryObj_(nullptr),
	//heartObj_(nullptr),
	bossGaugeUI_(nullptr),
	bossManager_(BossManager(world, position)),
	top_(0.0f), bottom_(0.0f), right_(0.0f), left_(0.0f),
	handle_(CreateFontToHandle(NULL, 50, 10, DX_FONTTYPE_NORMAL)),
	movePos_(Vector2::Zero),
	moveSpeed_(0.0f)
{
	asContainer_.clear();
	asAnimations_.clear();

	// 攻撃状態をコンテナに追加(攻撃順に追加する)
	asContainer_.push_back(AttackState::JumpAttack);
	asContainer_.push_back(AttackState::WallAttack);
	asContainer_.push_back(AttackState::SpeacialAttack);
	// 攻撃アニメーションコンテナ
	asAnimations_.push_back(JUMP_UP_NUMBER);
	asAnimations_.push_back(WALLATTACK_DASH_NUMBER);
	asAnimations_.push_back(BREATH_NUMBER);

	// ボスマネージャーに攻撃を追加
	bossManager_.addAttack(std::make_shared<ThreeJumpAttack>(world_, position));
	bossManager_.addAttack(std::make_shared<WallAttack>(world_, position));
	bossManager_.addAttack(std::make_shared<DysonAttack>(world_, position));

	//// 攻撃状態をコンテナに追加(攻撃順に追加する)
	//asContainer_.push_back(AttackState::WallAttack);
	//asContainer_.push_back(AttackState::SpeacialAttack);
	//asContainer_.push_back(AttackState::JumpAttack);
	//// 攻撃アニメーションコンテナ
	//asAnimations_.push_back(WALLATTACK_DASH_NUMBER);
	//asAnimations_.push_back(BREATH_NUMBER);
	//asAnimations_.push_back(JUMP_UP_NUMBER);

	//// ボスマネージャーに攻撃を追加
	//bossManager_.addAttack(std::make_shared<WallAttack>(world_, position));
	//bossManager_.addAttack(std::make_shared<DysonAttack>(world_, position));
	//bossManager_.addAttack(std::make_shared<ThreeJumpAttack>(world_, position));

	// 体力をロックするコンテナに追加
	lockHps_.clear();
	lockHps_.push_back(200);
	lockHps_.push_back(100);
	lockHps_.push_back(0);
	// スターコンテナの初期化
	stars_.clear();
	// アニメーションの追加
	addAnimation();
	animation_.changeAnimation(
		static_cast<int>(WAIT_NUMBER));
	/*animation_.changeAnimation(
		static_cast<int>(BossAnimationNumber::WAIT_NUMBER));*/

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
		Vector2(bodyScale / 2.0f, -bodyScale / 1.5f),
		bodyScale / 4.0f);
	world_->addActor(ActorGroup::Enemy, entryObj);
	entryObj_ = &*entryObj;
	// ボスの体力ゲージ
	auto bossUI = std::make_shared<BossGaugeUI>(world_, Vector2(64, -256));
	world_->addUIActor(bossUI);
	bossGaugeUI_ = bossUI.get();
	bossGaugeUI_->SetHp(hp_);

	body_.enabled(false);
}

BaseBoss::~BaseBoss()
{
	asContainer_.clear();
	asAnimations_.clear();
	lockHps_.clear();
	clampList_.clear();
	stars_.clear();
}

void BaseBoss::onUpdate(float deltaTime)
{
	clampList_.clear();

	// 補間タイマ(最大値１)の更新
	setTimer(deltaTime);
	// 体力の更新
	bossGaugeUI_->SetHp(hp_);
	//bossManager_.setHeartHP(heartObj_->getHeartHp());
	// アニメーションの更新
	animation_.update(deltaTime);

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

	// 演習が終わったらフラグを変更する。
	// world_->setEntry(false, true);
	// アニメーション(やられ状態)の追加
	
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
	//	vec3Pos.x, vec3Pos.y - 250,
	//	stateChar, GetColor(255, 255, 255));
	// アニメーションの描画
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	animation_.draw(
		pos - Vector2::Up * 10,
		Vector2::One * (body_.GetCircle().getRadius()) + Vector2::Up * 20,
		body_.GetCircle().getRadius() / (128 / 2), angle_);
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
	if (state_ == State::Flinch || state_ == State::Dead ||
		state_ == State::Boko || state_ == State::BattleIdel) return;
	if (damageTimer_ > 0 || attackCount_ == 2) return;
	// プレイヤーの攻撃範囲に当たった場合の処理
	if (actorName == "PlayerAttackCollider") {
		// プレイヤーの攻撃に当たらない場合は返す
		if (!isAttackHit_) return;
		// カウントを減らす
		piyoriCount_--;
		// ダメージ処理
		damage(30, actor.getPosition(), 2.0f);
		/*if (state_ == State::Idel)
			changeState(State::Damage, DAMAGE_NUMBER);
		setBMStatus();*/
		// ボスマネージャーに設定
		bossManager_.setCollideObj(actor);
		return;
	}
	//// プレイヤー本体に当たった場合の処理
	//if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
	//	// プレイヤーに当たらない場合は返す
	//	if (!isBodyHit_) return;
	//	// ダメージ処理
	//	damage(10, actor.getPosition(), 0.3f);
	//	//// ボスマネージャーに設定
	//	//bossManager_.setCollideObj(actor);
	//	// もしものためのreturn
	//	return;
	//}
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
void BaseBoss::movePosition(float deltaTime)
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
		position_ += Vector2::Normalize(distance)
		* moveSpeed_ * (deltaTime * 60.0f);
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

	if (hp_ <= 0) {
		name_ = "DeadBoss";
		changeState(State::Dead, DEATH_NUMBER);
		//changeState(State::Dead, BossAnimationNumber::DEATH_NUMBER);
	}

	switch (state_)
	{
	case State::BattleIdel: battleIdel(deltaTime); break;
	case State::Idel: idel(deltaTime); break;
	case State::Attack: attack(deltaTime); break;
	case State::Damage: damage(deltaTime); break;
	case State::Flinch: flinch(deltaTime); break;
	case State::Piyori: piyori(deltaTime); break;
	case State::Boko: boko(deltaTime); break;
	case State::Dead: deadMove(deltaTime); break;
	}

	stateTimer_ += deltaTime;
	// 位置の更新
	//position_ = bossManager_->getMovePosition();
}

//void BaseBoss::changeState(State state, BossAnimationNumber num)
void BaseBoss::changeState(State state, int num)
{
	// アニメーションの変更
	animation_.setIsLoop(true);
	//auto 
	//if (static_cast<int>(num) >= 15 && static_cast<int>(num) <= -1)
	//num = BossAnimationNumber::WAIT_NUMBER;
	animation_.changeAnimation(static_cast<int>(num));
	// 同じ状態なら返す
	if (state_ == state) return;
	state_ = state;
	stateTimer_ = 0.0f;
	angle_ = 0.0f;
}

//void BaseBoss::changeAttackState(AttackState aState, BossAnimationNumber num)
void BaseBoss::changeAttackState(AttackState aState, int num)
{
	// 攻撃状態に強制遷移する
	//if (attackState_ == aState) return;
	changeState(State::Attack, num);
	// 画像の方向を合わせる
	animation_.turnAnimation(num, direction_.x);
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
	movePosition(deltaTime);
	setBMStatus();

	// バトル開始でないなら
	if (!isBattle_) return;
	// 待機状態に遷移
	//changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
	/*changeAttackState(AttackState::JumpAttack,
		BossAnimationNumber::JUMP_UP_NUMBER);*/
	changeAttackState(AttackState::JumpAttack, JUMP_UP_NUMBER);
	body_.enabled(true);
}

void BaseBoss::idel(float deltaTime)
{
	stateString_ = "待機状態";
	//animation_.setIsLoop(true);
	// プレイヤーが取得できていれば、エネミーマネージャーに位置などを入れる
	setBMStatus();
	// 攻撃が当たるかの判定を入れる
	isAttackHit_ = true;
	isBodyHit_ = true;
	// 画像の方向を合わせる
	animation_.turnAnimation(WAIT_NUMBER, direction_.x);

	//bossManager_.changeAttackNumber(asContainer_.size() - hp_);
	bossManager_.changeAttackNumber(attackCount_);

	// 一定時間経過で攻撃状態に遷移
	if (stateTimer_ >= 5.0f) {
		// 攻撃行動のカウントで行動を決める
		changeAttackState(
			asContainer_[attackCount_],
			asAnimations_[attackCount_]);
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
	//animation_.setIsLoop(bossManager_.isAnimeLoop());
	//animation_.changeAnimation(static_cast<int>(bossManager_.getAnimaNum()));

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

// ダメージ状態
void BaseBoss::damage(float deltaTime)
{
	name_ = "DamageBoss";
	animation_.setIsLoop(false);
	if (stateTimer_ > 0.5f) {
		animation_.setIsLoop(true);
		changeState(State::Idel, WAIT_NUMBER);
		name_ = "BaseEnemy";
	}
}

// 怯み状態
void BaseBoss::flinch(float deltaTime)
{
	stateString_ = "ひるみ";
	name_ = "flinchBoss";
	entryObj_->setIsEntry(true);
	flinchCount_ = 0;
	animation_.setIsLoop(true);
	// 星の生成
	if (starCreateCount_ % 50 == 0 && stars_.size() < 6){
		auto addPos = Vector2::Right * 100;
		auto star = std::make_shared<PiyoriEffect>(
			world_, position_ + addPos);
		world_->addActor(ActorGroup::Effect, star);
		stars_.push_back(star);
	}
	starCreateCount_++;
	// ぴよりエフェクトの位置
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto addPos = Vector2::Right * 100;
		i->get()->position_ = position_ + addPos;
	}
	
	// 重力
	if (!isGround_ && bossManager_.isUseGravity()) {
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
	if (entryObj_->isEntered()) {
		// プレイヤーが出てきたら、待機状態にする
		//stateTimer_ = 5.0f;
		stateTimer_ = 5.0f;
		//heartObj_->setIsEntered(true);
		//heartObj_->addBossHp(-30);
		// カウントを減らす
		piyoriCount_--;
		// ダメージ処理
		damage(30, entryObj_->getPosition(), 0.8f);
		//changeState(State::Damage, DAMAGE_NUMBER);
		/*if (attackCount_ < asContainer_.size() - 1)
			attackCount_++;*/
		entryObj_->letOut();
		//name_ = "BaseEnemy";
		// スターの削除
		for (auto i = stars_.begin(); i != stars_.end(); i++) {
			auto star = *i;
			star->dead();
		}
		stars_.clear();
		starCreateCount_ = 0;
		return;
	}
	//// 体内に入ったら何かする
	//if (entryObj_->isEntered()) {
	//	// プレイヤーを追い出せていないなら返す
	//	//if (!heartObj_->isLetOut()) return;
	//	// プレイヤーが出てきた
	//	entryObj_->letOut();
	//}

	//// 体力が0になったら死亡
	//if (hp_ <= 0) {
	//	changeState(State::Dead, BossAnimationNumber::DEATH_NUMBER);
	//	return;
	//}
	// 一定時間経過で待機状態に遷移
	if (stateTimer_ < 5.0f) return;
	//changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
	changeState(State::Idel, WAIT_NUMBER);
	name_ = "BaseEnemy";
	entryObj_->setIsEntry(false);
	//dp_ = initDp_;
	// スターの削除
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto star = *i;
		star->dead();
	}
	stars_.clear();
	starCreateCount_ = 0;
}

// ぴより状態
void BaseBoss::piyori(float deltaTime)
{
	stateString_ = "ぴより";
	name_ = "piyoriBoss";
	entryObj_->setIsEntry(true);
	//flinchCount_ = 0;
	animation_.setIsLoop(true);
	// 星の生成
	if (starCreateCount_ % 50 == 0 && stars_.size() < 6) {
		auto addPos = Vector2::Right * 100;
		auto star = std::make_shared<PiyoriEffect>(
			world_, position_ + addPos);
		world_->addActor(ActorGroup::Effect, star);
		stars_.push_back(star);
	}
	starCreateCount_++;
	// ぴよりエフェクトの位置
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto addPos = Vector2::Right * 100;
		i->get()->position_ = position_ + addPos;
	}

	// 重力
	if (!isGround_ && bossManager_.isUseGravity()) {
		position_.y += 9.8f * (1.0f);// * 60.0f);
	}
	// 体内に入っていたら、ハートに入ったことを知らせる
	if (entryObj_->isEntered()) {
		// プレイヤーが出てきたら、待機状態にする
		stateTimer_ = 5.0f;
		if (attackCount_ < asContainer_.size() - 1)
			attackCount_++;
		// ぼこり状態に変更
		changeState(State::Boko, DAMAGE_BOKO_NUMBER);
		world_->setEntry(true, false);
		entryObj_->letOut();

		// スターの削除
		for (auto i = stars_.begin(); i != stars_.end(); i++) {
			auto star = *i;
			star->dead();
		}
		stars_.clear();
		starCreateCount_ = 0;

		return;
	}

	// 一定時間経過で待機状態に遷移
	if (stateTimer_ < 5.0f) return;
	//changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
	changeState(State::Idel, WAIT_NUMBER);
	name_ = "BaseEnemy";
	entryObj_->setIsEntry(false);
	// スターの削除
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto star = *i;
		star->dead();
	}
	stars_.clear();
	starCreateCount_ = 0;
}

void BaseBoss::boko(float deltaTime)
{
	name_ = "BokoBoss";
	// 煙の生成
	if (starCreateCount_ % 50 == 0 && bockCreateCount_ < 2) {
		// エフェクトの追加
		auto addPos = Vector2::One * 220.0f;
		world_->addActor(ActorGroup::Effect,
			std::make_shared<BokoEffect>(world_, position_ + addPos));
		bockCreateCount_++;
		//stars_.push_back(star);
	}
	starCreateCount_++;
	if (stateTimer_ < 2.0f) return;
	direction_.x = -1.0f;
	animation_.turnAnimation(DAMAGE_BOKO_NUMBER, direction_.x);
	world_->setEntry(false, true);
	entryObj_->setIsEntry(false);
	if (stateTimer_ >= 3.0f) {
		name_ = "BaseEnemy";
		bockCreateCount_ = 0;
		starCreateCount_ = 0;
		changeState(State::Idel, WAIT_NUMBER);
	}
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
	/*auto anime = BossAnimationNumber::PIYO_NUMBER;
	changeState(State::Piyori, BossAnimationNumber::PIYO_NUMBER);
	animation_.setIsLoop(true);
	bossManager_.attackRefresh();

	animation_.changeAnimation(static_cast<int>(bossManager_.getAnimaNum()));
	return;*/

	stateString_ = "ジャンプ攻撃";
	// プレイヤー本体に当たらない
	//isBodyHit_ = false;
	// ジャンプ攻撃
	bossManager_.attackMove(deltaTime);
	bossManager_.setPlayerPosition(player_->getPosition());
	position_ = bossManager_.getMovePosition();
	// アニメーションの変更
	animation_.setIsLoop(bossManager_.isAnimeLoop());
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	/*animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));*/
	animation_.turnAnimation(JUMP_UP_NUMBER, bossManager_.getAttackDirection().x);
	/*if (bossManager_.isPiyori()) {
		changeState(State::Piyori, BossAnimationNumber::PIYO_NUMBER);
		animation_.setIsLoop(true);
		bossManager_.attackRefresh();
	}*/
	// ジャンプ攻撃が終わったら、待機状態にする
	if (bossManager_.isAttackEnd()) {
		//changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
		animation_.setIsLoop(true);
		changeState(State::Idel, WAIT_NUMBER);
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
	animation_.setIsLoop(bossManager_.isAnimeLoop());
	/*animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));*/
	animation_.turnAnimation(WALLATTACK_DASH_NUMBER, Vector2::Left.x);
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
			//changeState(State::Flinch, BossAnimationNumber::PIYO_NUMBER);
			changeState(State::Flinch, PIYO_NUMBER);
			bossManager_.attackRefresh();
			flinchCount_ = 0;
			return;
		}
		else {
			//changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
			changeState(State::Idel, WAIT_NUMBER);
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
		//changeState(State::Flinch, BossAnimationNumber::PIYO_NUMBER);
		changeState(State::Flinch, PIYO_NUMBER);
		bossManager_.attackRefresh();
		//angleCount_ = 0;
		//angle_ = 0.0f;
		return;
	}

	stateString_ = "スペシャルな攻撃";
	name_ = "suikomiBoss";
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
	animation_.setIsLoop(bossManager_.isAnimeLoop());
	/*animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));*/
	animation_.turnAnimation(
		static_cast<int>(bossManager_.getAnimaNum()),
		bossManager_.getAttackDirection().x);
	// bossManager_.specialAttack(deltaTime);
	/*if (entryObj_->isBlock()) {

	}*/

	if (bossManager_.isAttackEnd()) {
		name_ = "BaseEnemy";
		//changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
		changeState(State::Idel, WAIT_NUMBER);
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
void BaseBoss::damage(const int damage, const Vector2& position, const float scale)
{
	// if (attackCount_ == 2) return;
	hp_ -= damage;
	//dp_--;
	// 体力がロックよりも小さくなったら補間する
	if (hp_ < lockHps_[attackCount_]) {
		hp_ = lockHps_[attackCount_];
	}
	damageTimer_ = 1.0f;
	// エフェクトの生成
	world_->addActor(ActorGroup::Effect,
		std::make_shared<AttackEffect>(world_, position, scale));
	// 耐久値が0になったら、ぴよる
	if (piyoriCount_ <= 0) {
		//changeState(State::Piyori, BossAnimationNumber::PIYO_NUMBER);
		changeState(State::Piyori, PIYO_NUMBER);
		// 衝突するかどうかの bool を全てtrueにする
		piyoriCount_ = 5;
		isBodyHit_ = true;
		isAttackHit_ = true;
		setBMStatus();
		// 画像の方向を合わせる
		animation_.setIsLoop(true);
		animation_.turnAnimation(DAMAGE_NUMBER, direction_.x);
		bossManager_.attackRefresh();
		return;
	}
	else {
		if (state_ == State::Idel || state_ == State::Flinch) {
			isBodyHit_ = true;
			isAttackHit_ = true;
			setBMStatus();
			// 画像の方向を合わせる
			//animation_.setIsLoop(true);
			animation_.turnAnimation(DAMAGE_NUMBER, direction_.x);
			changeState(State::Damage, DAMAGE_NUMBER);
		}
	}

	//if (dp_ <= 0) {
	//	changeState(State::Flinch, BossAnimationNumber::PIYO_NUMBER);
	//	// 衝突するかどうかの bool を全てtrueにする
	//	isBodyHit_ = true;
	//	isAttackHit_ = true;
	//	setBMStatus();
	//	// 画像の方向を合わせる
	//	animation_.turnAnimation(motion_, direction_.x);
	//}
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
	// 待機
	animation_.addAnimation(
		static_cast<int>(WAIT_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WAIT_TEX));
	animation_.addAnimation(
		static_cast<int>(WAIT_TURN_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WAIT_TURN_TEX));
	// ジャンプ攻撃
	animation_.addAnimation(
		static_cast<int>(JUMP_UP_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_JUMP_UP_TEX));
	animation_.addAnimation(
		static_cast<int>(JUMP_DOWN_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_JUMP_DOWN_TEX));
	// 壁移動攻撃
	animation_.addAnimation(
		static_cast<int>(WALLATTACK_DASH_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WALLATTACK_DASH_TEX));
	animation_.addAnimation(
		static_cast<int>(WALLATTACK_DASHJUMP_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WALLATTACK_DASHJUMP_TEX));
	animation_.addAnimation(
		static_cast<int>(WALLATTACK_DASHJUMP_STOP_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WALLATTACK_DASHJUMP_STOP_TEX));
	// 吸い込み攻撃
	animation_.addAnimation(
		static_cast<int>(BREATH_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_BREATH_TEX));
	animation_.addAnimation(
		static_cast<int>(BREATH_TURN_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_BREATH_TURN_TEX));
	animation_.addAnimation(
		static_cast<int>(BREATH_DYSFUNCTION_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_BREATH_DYSFUNCTION_TEX));
	animation_.addAnimation(
		static_cast<int>(BREATH_LESS_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_BREATH_LESS_TEX));
	// 怯み
	animation_.addAnimation(
		static_cast<int>(PIYO_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_PIYO_TEX));
	// ダメージ
	animation_.addAnimation(
		static_cast<int>(DAMAGE_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_DAMAGE_TEX));
	animation_.addAnimation(
		static_cast<int>(DAMAGE_BOKO_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_DAMAGE_BOKO_TEX));
	// 死亡
	animation_.addAnimation(
		static_cast<int>(DEATH_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_DEATH_TEX));
}