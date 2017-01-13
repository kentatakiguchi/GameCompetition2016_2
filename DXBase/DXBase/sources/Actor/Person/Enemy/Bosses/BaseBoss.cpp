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
	bokoCreateCount_(0),
	stateTimer_(0.0f),
	timer_(0.0f),
	deltaTimer_(0.0f),
	damageTimer_(0.0f),
	angle_(0.0f),
	effectCreateTimer_(0.0f),
	isGround_(false),
	isBottomHit_(false),
	isAttackHit_(false),
	isSceneEnd_(false),
	isBattle_(false),
	isEffectCreate_(true),
	playerPastPosition_(Vector2::Zero),
	direction_(Vector2::One),
	player_(nullptr),
	state_(State::BattleIdel),
	attackState_(AttackState::JumpAttack),
	animeNum_(WAIT_NUMBER),
	animation_(EnemyAnimation2D()),
	wspObj_(nullptr),
	entryObj_(nullptr),
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
	//asContainer_.push_back(AttackState::SpeacialAttack);
	//asContainer_.push_back(AttackState::WallAttack);
	//asContainer_.push_back(AttackState::JumpAttack);
	//// 攻撃アニメーションコンテナ
	//asAnimations_.push_back(BREATH_NUMBER);
	//asAnimations_.push_back(WALLATTACK_DASH_NUMBER);
	//asAnimations_.push_back(JUMP_UP_NUMBER);

	//// ボスマネージャーに攻撃を追加
	//bossManager_.addAttack(std::make_shared<DysonAttack>(world_, position));
	//bossManager_.addAttack(std::make_shared<WallAttack>(world_, position));
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
		world_, position_ + Vector2::Left * 50,
		Vector2(bodyScale / 1.75f, -bodyScale / 1.25f),
		bodyScale / 4.0f);
	world_->addActor(ActorGroup::Enemy, entryObj);
	entryObj_ = &*entryObj;
	// ボスの体力ゲージ
	auto bossUI = std::make_shared<BossGaugeUI>(world_, Vector2(64, -256));
	world_->addUIActor(bossUI);
	bossGaugeUI_ = bossUI.get();
	bossGaugeUI_->SetHp(hp_);
	// 衝突判定を一回無くす
	body_.enabled(false);
}

BaseBoss::~BaseBoss()
{
	asContainer_.clear();
	asAnimations_.clear();
	lockHps_.clear();
	stars_.clear();
}

void BaseBoss::onUpdate(float deltaTime)
{
	deltaTimer_ = deltaTime * 60.0f;
	// 補間タイマ(最大値１)の更新
	setTimer(deltaTime);
	// 体力の更新
	bossGaugeUI_->SetHp(hp_);
	// アニメーションの更新
	animation_.update(deltaTime);
	// 所持しているオブジェクトの位置更新
	entryObj_->setBossPosition(position_ + Vector2::Left * 50);
	wspObj_->setPosition(position_);
	// 状態の更新
	updateState(deltaTime);
	// 接地(仮)
	bossManager_.setIsGround(isGround_);
	bossManager_.setIsBottom(isBottomHit_);
	// 被弾したら、ダメージタイマを減算する
	if (damageTimer_ > 0)
		damageTimer_ -= deltaTime;
	// bool系
	isGround_ = false;
	isBottomHit_ = false;
}

void BaseBoss::onEnd()
{
	bossManager_.attackRefresh();
	// SEが再生中なら、止める
	if (CheckSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_POKO)) == 1)
		StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_POKO));
}

void BaseBoss::onDraw() const
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
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
		groundClamp(actor);
		bossManager_.setFloorName(actorName.c_str());
		return;
	}
	// プレイヤーの攻撃に当たらない場合は返す
	if (!isAttackHit_ || damageTimer_ > 0 || attackCount_ == 2) return;
	if (state_ == State::Flinch) return;
	//if (damageTimer_ > 0 || attackCount_ == 2) return;
	// プレイヤーの攻撃範囲に当たった場合の処理
	if (actorName == "PlayerAttackCollider") {
		// カウントを減らす
		piyoriCount_--;
		// ダメージ処理
		damage(30, actor.getPosition(), 2.0f);
		// ボスマネージャーに設定
		bossManager_.setCollideObj(actor);
		return;
	}
}

void BaseBoss::onMessage(EventMessage event, void *){}

// シーンを終了させるかを返します
bool BaseBoss::isSceneEnd()
{
	return isSceneEnd_;
}

// 目的地に移動します
void BaseBoss::movePosition(float deltaTime)
{
	// 目的地と自分の方向を出す
	auto distance = movePos_ - position_;
	// 目的地と速度の差が速度以下なら、位置を変える
	if (distance.Length() < moveSpeed_) {
		position_ = movePos_;
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
	player_ = world_->findActor("PlayerBody1");
	// 体力が0以下になったら死亡
	if (hp_ <= 0) {
		name_ = "DeadBoss";
		isAttackHit_ = false;
		changeState(State::Dead, DEATH_NUMBER);
	}
	// 状態の更新
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
}

void BaseBoss::changeState(State state, int num)
{
	// アニメーションの変更
	animation_.setIsLoop(true);
	animation_.changeAnimation(static_cast<int>(num));
	// 同じ状態なら返す
	if (state_ == state) return;
	state_ = state;
	stateTimer_ = 0.0f;
	angle_ = 0.0f;
}

void BaseBoss::changeAttackState(AttackState aState, int num)
{
	// 攻撃状態に強制遷移する
	changeState(State::Attack, num);
	// 画像の方向を合わせる
	animation_.changeDirType(direction_.x);
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
	// バトル開始でないなら返す
	if (!isBattle_) return;
	// ジャンプ攻撃状態に遷移
	changeAttackState(AttackState::JumpAttack, JUMP_UP_NUMBER);
	isAttackHit_ = true;
	body_.enabled(true);
}

void BaseBoss::idel(float deltaTime)
{
	// プレイヤーが取得できていれば、エネミーマネージャーに位置などを入れる
	setBMStatus();
	// 画像の方向を合わせる
	animation_.changeDirType(direction_.x);
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
	// 攻撃が当たるかの判定を入れる
	isAttackHit_ = bossManager_.IsAttackHit();
}

// ダメージ状態
void BaseBoss::damage(float deltaTime)
{
	name_ = "DamageBoss";
	animation_.setIsLoop(false);
	if (stateTimer_ > 0.5f) {
		animation_.setIsLoop(true);
		changeState(State::Idel, WAIT_NUMBER);
		isAttackHit_ = false;
		name_ = "BaseEnemy";
	}
}

// 怯み状態
void BaseBoss::flinch(float deltaTime)
{
	name_ = "flinchBoss";
	flinchCount_ = 0;
	// 行動
	piyoriMove(deltaTime);
}

// ぴより状態
void BaseBoss::piyori(float deltaTime)
{
	name_ = "piyoriBoss";
	piyoriCount_ = 5;
	piyoriMove(deltaTime);
}

void BaseBoss::boko(float deltaTime)
{
	name_ = "BokoBoss";
	// 煙の生成
	if (isEffectCreate_ && (int)effectCreateTimer_ % 50 <= 24 && bokoCreateCount_ < 2) {
		// エフェクトの追加
		auto addPos = Vector2::One * -40.0f;
		world_->addActor(ActorGroup::Effect,
			std::make_shared<BokoEffect>(world_, position_ + addPos));
		bokoCreateCount_++;
		isEffectCreate_ = false;
	}
	else if ((int)effectCreateTimer_ % 50 > 24) {
		isEffectCreate_ = true;
	}
	effectCreateTimer_ += deltaTimer_;
	// デルタタイムが0以下なら、SEを一時停止する
	auto se = ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_POKO);
	if (CheckSoundMem(se) == 1 &&
		deltaTime <= 0) {
		StopSoundMem(se);
	}
	else if (CheckSoundMem(se) == 0 && deltaTime > 0) {
		// SEの再生(停止した箇所から再生)
		PlaySoundMem(se, DX_PLAYTYPE_LOOP, false);
	}
	if (stateTimer_ < 2.0f) return;
	direction_.x = -1.0f;
	animation_.changeDirType(direction_.x);
	world_->setEntry(false, true);
	entryObj_->setIsEntry(false);
	// SEが再生中なら、止める
	if (CheckSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_POKO)) == 1)
		StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_POKO));
	if (stateTimer_ >= 3.0f) {
		name_ = "BaseEnemy";
		bokoCreateCount_ = 0;
		effectCreateTimer_ = 0.0f;
		isEffectCreate_ = true;
		isAttackHit_ = true;
		changeState(State::Idel, WAIT_NUMBER);
	}
}

void BaseBoss::deadMove(float deltaTime)
{
	animation_.setIsLoop(false);
	// 死亡から一定時間経過なら、シーンを終了させる
	if (stateTimer_ >= 3.0f)
		isSceneEnd_ = true;
}

// ぴより行動
void BaseBoss::piyoriMove(float deltaTime)
{
	entryObj_->setIsEntry(true);
	auto dir = direction_;
	dir.y = 1.0f;
	entryObj_->setDirection(dir);
	animation_.setIsLoop(true);
	// 星の生成
	if (isEffectCreate_ && (int)effectCreateTimer_ % 50 <= 24 && stars_.size() < 6) {
		auto star = std::make_shared<PiyoriEffect>(
			world_, position_);
		world_->addActor(ActorGroup::Effect, star);
		stars_.push_back(star);
		isEffectCreate_ = false;
	}
	else if ((int)effectCreateTimer_ % 50 > 24) {
		isEffectCreate_ = true;
	}
	effectCreateTimer_ += deltaTimer_;
	// ぴよりエフェクトの位置
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto addPos = Vector2::Up * -150;
		i->get()->position_ = position_ + addPos;
	}
	// 重力
	if (!isGround_ && bossManager_.isUseGravity()) {
		position_.y += 9.8f * deltaTimer_;// * 60.0f);
	}
	// 口の印の更新
	auto posEffect = world_->findActor("EntrySignEffect");
	auto addPos = Vector2::Up * -225;
	if (posEffect != nullptr) {
		posEffect->position_ = entryObj_->getPosition() + addPos;
	}
	// 体内に入っていたら、ハートに入ったことを知らせる
	if (entryObj_->isEntered()) {
		// プレイヤーが出てきたら、待機状態にする
		stateTimer_ = 5.0f;
		// スターの削除
		for (auto i = stars_.begin(); i != stars_.end(); i++) {
			auto star = *i;
			star->dead();
		}
		// エフェクトの削除
		auto effect = world_->findActor("EntrySignEffect");
		if (effect != nullptr)
			effect->dead();
		stars_.clear();
		effectCreateTimer_ = 0.0f;
		entryObj_->letOut();
		isEffectCreate_ = true;
		// 状態によって行動を変える
		if (state_ == State::Flinch) {
			// カウントを減らす
			piyoriCount_--;
			// ダメージ処理
			damage(30, entryObj_->getPosition(), 0.8f);
			return;
		}
		else if (state_ == State::Piyori) {
			if (attackCount_ < asContainer_.size() - 1)
				attackCount_++;
			// ぼこり状態に変更
			changeState(State::Boko, DAMAGE_BOKO_NUMBER);
			isAttackHit_ = false;
			world_->setEntry(true, false);
			// SEの再生
			PlaySoundMem(
				ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_POKO),
				DX_PLAYTYPE_LOOP);
			return;
		}
	}
	// 一定時間経過で待機状態に遷移
	if (stateTimer_ < 5.0f) return;
	changeState(State::Idel, WAIT_NUMBER);
	name_ = "BaseEnemy";
	isAttackHit_ = true;
	entryObj_->setIsEntry(false);
	isEffectCreate_ = true;
	// エフェクトの削除
	auto effect = world_->findActor("EntrySignEffect");
	if (effect != nullptr)
		effect->dead();
	// スターの削除
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto star = *i;
		star->dead();
	}
	stars_.clear();
	effectCreateTimer_ = 0.0f;
}

void BaseBoss::jumpAttack(float deltaTime)
{
	// ジャンプ攻撃
	bossManager_.attackMove(deltaTime);
	bossManager_.setPlayerPosition(player_->getPosition());
	position_ = bossManager_.getMovePosition();
	// アニメーションの変更
	animation_.setIsLoop(bossManager_.isAnimeLoop());
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	animation_.changeDirType(bossManager_.getAttackDirection().x);
	// ジャンプ攻撃が終わったら、待機状態にする
	if (bossManager_.isAttackEnd()) {
		animation_.setIsLoop(true);
		changeState(State::Idel, WAIT_NUMBER);
		// 攻撃が当たるかの判定を入れる
		isAttackHit_ = true;
		bossManager_.attackRefresh();
	}
}

void BaseBoss::wallAttack(float deltaTime)
{
	bossManager_.attackMove(deltaTime);
	position_ = bossManager_.getMovePosition();
	// アニメーションの変更
	angle_ = static_cast<float>(bossManager_.getAnimeAngle());
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	animation_.setIsLoop(bossManager_.isAnimeLoop());
	//animation_.turnAnimation(WALLATTACK_DASH_NUMBER, Vector2::Left.x);
	animation_.changeDirType(Vector2::Left.x);
	// 攻撃動作中なら、壁捜索オブジェクトなどの判定をONにする
	if (bossManager_.isAttackStart()) {
		setBMStatus();
		bossManager_.getPlayerNormalizeDirection();
	}
	// ジャンプ攻撃が終わったら、待機状態にする
	if (bossManager_.isAttackEnd()) {
		flinchCount_++;
		// ボスマネージャ側のひるみ回数以上なら、ひるみ状態に遷移	
		if (bossManager_.getFlinchCount() > flinchCount_) {
			changeState(State::Idel, WAIT_NUMBER);
			// 攻撃が当たるかの判定を入れる
			isAttackHit_ = true;
			bossManager_.attackRefresh();
			return;
		}
		else if (bossManager_.getFlinchCount() <= flinchCount_) {
			changeState(State::Flinch, PIYO_NUMBER);
			flinchCount_ = 0;
			isAttackHit_ = false;
			// 怯み状態の設定
			setPiyori();
			// 方向の変更
			auto dir = Vector2::Left;
			if(bossManager_.getAttackDirection().x >= 0)
			dir.x = 1.0f;
			direction_.x = dir.x;
			animation_.changeDirType(dir.x);
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
		changeState(State::Flinch, PIYO_NUMBER);
		bossManager_.attackRefresh();
		isAttackHit_ = false;
		// 怯み状態の設定
		setPiyori();
		return;
	}

	name_ = "suikomiBoss";
	// isBlock() == true => 塞がれている
	bossManager_.setIsAttackMove(!entryObj_->isBlock());
	bossManager_.attackMove(deltaTime);
	position_ = bossManager_.getMovePosition();
	// 壁に当たっている場合
	bossManager_.setIsWallHit(wspObj_->isGround());
	wspObj_->setDirection(bossManager_.getWallMoveDirection());
	// アニメーションの変更
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	animation_.setIsLoop(bossManager_.isAnimeLoop());
	animation_.changeDirType(bossManager_.getAttackDirection().x);

	if (bossManager_.isAttackEnd()) {
		name_ = "BaseEnemy";
		changeState(State::Idel, WAIT_NUMBER);
		// 攻撃が当たるかの判定を入れる
		isAttackHit_ = true;
		bossManager_.attackRefresh();
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
		// 壁に当たっている場合
		bossManager_.setIsWallHit(wspObj_->isGround());
		if (wspObj_->isGround()) {
			wspObj_->setDirection(bossManager_.getWallMoveDirection());
		}
		wspObj_->setDirection(bossManager_.getWallMoveDirection());
		// 戻す y = -1.0fに
		// direction.y = -1.0f;
		direction.y = 1.0f;
		entryObj_->setDirection(direction);
	}
}

// 指定した値のダメージ量を加算します
void BaseBoss::damage(const int damage, const Vector2& position, const float scale)
{
	hp_ -= damage;
	// 体力がロックよりも小さくなったら補間する
	if (hp_ < lockHps_[attackCount_]) {
		hp_ = lockHps_[attackCount_];
	}
	damageTimer_ = 1.0f;
	// 待機中に攻撃を受けたら次の行動までに攻撃を受けないようにする
	if (state_ == State::Idel)
		isAttackHit_ = false;
	// エフェクトの生成
	world_->addActor(ActorGroup::Effect,
		std::make_shared<AttackEffect>(world_, position, scale));
	// 耐久値が0になったら、ぴよる
	if (piyoriCount_ <= 0) {
		changeState(State::Piyori, PIYO_NUMBER);
		// 衝突するかどうかの bool を全てtrueにする
		piyoriCount_ = 5;
		setBMStatus();
		// 画像の方向を合わせる
		animation_.setIsLoop(true);
		//animation_.turnAnimation(DAMAGE_NUMBER, direction_.x);
		animation_.changeDirType(direction_.x);
		bossManager_.attackRefresh();
		// 怯み状態の設定
		setPiyori();
		return;
	}
	else {
		if (state_ == State::Idel || state_ == State::Flinch) {
			setBMStatus();
			// 画像の方向を合わせる
			//animation_.turnAnimation(DAMAGE_NUMBER, direction_.x);
			animation_.changeDirType(direction_.x);
			changeState(State::Damage, DAMAGE_NUMBER);
			isAttackHit_ = false;
		}
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

// ぴより状態の設定を行います
void BaseBoss::setPiyori()
{
	// 攻撃が当たるかの判定を入れる
	isAttackHit_ = false;
	// エフェクトの生成
	auto effect = std::make_shared<EntrySignEffect>(
		world_, entryObj_->getPosition() - Vector2::Up * 150.0f);
	world_->addActor(ActorGroup::Effect, effect);
}
