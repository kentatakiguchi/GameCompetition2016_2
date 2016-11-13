#include "BaseBoss.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../../../Base/ActorGroup.h"
#include "../../../Body/CollisionBase.h"
#include "../../../../Define.h"
#include "BossManager.h"
#include "BossEntry.h"
#include "BossHeart.h"
#include "../FloorSearchPoint.h"

// ボスクラス(ベース予定)
BaseBoss::BaseBoss(IWorld * world, const Vector2 & position, const float bodyScale) :
	Actor(world, "BaseBoss", position,
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	dp_(20),
	initDp_(dp_),
	hp_(3),
	// initHp_(hp_),
	stateTimer_(0.0f),
	timer_(0.0f),
	deltaTimer_(0.0f),
	stateString_("待機"),
	// bossManager_(nullptr),
	playerPastPosition_(Vector2::Zero),
	player_(nullptr),
	state_(State::Idel),
	attackState_(AttackState::JumpAttack),
	fspObj_(nullptr),
	entryObj_(nullptr),
	heartObj_(nullptr),
	bossManager_(BossManager(position))
{
	// コンテナに追加(攻撃順に追加する)
	asContainer_.push_back(AttackState::JumpAttack);
	asContainer_.push_back(AttackState::WallAttack);
	asContainer_.push_back(AttackState::SpeacialAttack);
	// ボスマネージャー
	/*auto manager = std::make_shared<BossManager>(position);
	bossManager_ = &*manager;*/
	// 床捜索オブジェクト
	auto fspObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, bodyScale + 1.0f), 0.1f
		);
	world_->addActor(ActorGroup::Enemy, fspObj);
	fspObj_ = &*fspObj;
	// ボス入口オブジェクト
	auto entryObj = std::make_shared<BossEntry>(
		world_, position_, 
		Vector2(bodyScale / 2.0f, bodyScale / 2.0f),
		bodyScale / 2.0f);
	world_->addActor(ActorGroup::Enemy, entryObj);
	entryObj_ = &*entryObj;
	// ボス心臓オブジェクト
	auto heartObj = std::make_shared<BossHeart>(
		world_, Vector2(position_.x + 128.0f, position_.y -32.0f), 10, hp_);
	world_->addActor(ActorGroup::Enemy, heartObj);
	heartObj_ = &*heartObj;
}

BaseBoss::~BaseBoss()
{
}

void BaseBoss::onUpdate(float deltaTime)
{
	// 補間タイマ(最大値１)の更新
	setTimer(deltaTime);

	//
	hp_ = heartObj_->getBossHp();


	// 状態の更新
	updateState(deltaTime);
	// 位置をクランプする
	/*if (fspObj_->isGround()) {
		position_.y = MathHelper::Clamp(position_.y,
			fspObj_->getFloorPosition().y - 100.0f,
			fspObj_->getFloorPosition().y - CHIPSIZE);
		bossManager_.setIsGround(fspObj_->isGround());
	}*/
	position_.x = MathHelper::Clamp(position_.x,
		CHIPSIZE + body_.GetCircle().getRadius(),
		FIELD_SIZE.x);
	position_.y = MathHelper::Clamp(position_.y,
		CHIPSIZE + body_.GetCircle().getRadius(),
		FIELD_SIZE.y);
	// 接地(仮)
	if (position_.y < FIELD_SIZE.y) {
		bossManager_.setIsGround(false);
		// position_.y += 9.8f * (deltaTimer_ * 60.0f);
	}
	else if (position_.y == FIELD_SIZE.y)
		bossManager_.setIsGround(true);

	// bossManager_.setIsGround(fspObj_->isGround());
	fspObj_->setPosition(position_);
	entryObj_->setBossPosition(position_);
	// entryObj_->setDirection(direction_);
	//position_.y = MathHelper::Clamp(position_.y, -1000, 500.0f);
}

void BaseBoss::onDraw() const
{
	// デバッグ
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// 敵の表示
	/*DrawGraph(
		position_.x - scale_ / 2.0f, position_.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);*/
	// 状態の表示
	DrawString(
		vec3Pos.x, vec3Pos.y - 100,
		stateChar, GetColor(255, 255, 255));
	// 体力の表示
	// 体力の表示
	DrawFormatString(
		vec3Pos.x, vec3Pos.y - 150,
		GetColor(255, 255, 255), "体力:%d", hp_);
	DrawFormatString(
		vec3Pos.x, vec3Pos.y - 175,
		GetColor(255, 255, 255), "時間:%d", (int)stateTimer_);
	body_.draw(inv_);
}

void BaseBoss::onCollide(Actor & actor)
{
	// プレイヤーに当たったら、耐久値を下げる
	if (state_ == State::Flinch || state_ == State::Dead) return;
	auto actorName = actor.getName();
	if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
		auto damage = 10;
		dp_ -= damage;
		// 耐久値が0になったら、ひるむ
		if (dp_ <= 0) {
			changeState(State::Flinch, BOSS_FLINCH);
			setBMStatus();
			body_.enabled(false);
			return;
		}
		// もしものためのreturn
		return;
	}
}

void BaseBoss::onMessage(EventMessage event, void *)
{
}

void BaseBoss::updateState(float deltaTime)
{
	// 現在は使用不可
	// player_ = world_->findActor("Player");
	player_ = world_->findActor("PlayerBody1");

	switch (state_)
	{
	case State::Idel: idel(deltaTime); break;
	case State::Attack: attack(deltaTime); break;
	case State::Flinch: flinch(deltaTime); break;
	case State::Dead: deadMove(deltaTime); break;
	}

	stateTimer_ += deltaTime;
	// 位置の更新
	//position_ = bossManager_->getMovePosition();
}

void BaseBoss::changeState(State state, unsigned int motion)
{
	// 同じ状態なら返す
	if (state_ == state) return;
	state_ = state;
	stateTimer_ = 0.0f;
}

void BaseBoss::changeAttackState(AttackState aState, unsigned int motion)
{
	// 攻撃状態に強制遷移する
	changeState(State::Attack, BOSS_ATTACK);
	attackState_ = aState;
	bossManager_.prevPosition();
}

void BaseBoss::idel(float deltaTime)
{
	stateString_ = "待機状態";
	// プレイヤーが取得できていれば、エネミーマネージャーに位置などを入れる
	setBMStatus();
	// 一定時間経過で攻撃状態に遷移
	if (stateTimer_ >= 5.0f) {
		// 残り体力で攻撃状態を変える
		// initHp - hp
		changeAttackState(
			asContainer_[asContainer_.size() - hp_], BOSS_ATTACK);
		return;
	}
	// 重力
	if (position_.y < SCREEN_SIZE.y - CHIPSIZE - body_.GetCircle().getRadius()) {
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
	// 重力
	if (position_.y < FIELD_SIZE.y) {
		position_.y += 9.8f * (1.0f);// * 60.0f);
	}

	// 体内に入っていたら、ハートに入ったことを知らせる
	if (entryObj_->isEntered() && !heartObj_->isLetOut()) {
		// プレイヤーが出てきたら、待機状態にする
		stateTimer_ = 5.0f;
		heartObj_->setIsEntered(true);
	}
	// 体内に入ったら何かする
	if (entryObj_->isEntered()) {
		// プレイヤーを追い出せていないなら返す
		if (!heartObj_->isLetOut()) return;
		// プレイヤーが出てきた
		entryObj_->letOut();
	}
	// 体力が0になったら死亡
	if (hp_ <= 0) 
		changeState(State::Dead, BOSS_DEAD);
	// 一定時間経過で待機状態に遷移
	if (stateTimer_ < 5.0f) return;
	changeState(State::Idel, BOSS_IDLE);
	entryObj_->setIsEntry(false);
	dp_ = initDp_;
}

void BaseBoss::deadMove(float deltaTime)
{
	stateString_ = "死亡";
	//dead();
}

void BaseBoss::jumpAttack(float deltaTime)
{
	stateString_ = "ジャンプ攻撃";
	// ジャンプ攻撃
	bossManager_.attackMove(ATTACK_JUMPATTACK_NUMBER, deltaTime);
	position_ = bossManager_.getMovePosition();
	// ジャンプ攻撃が終わったら、待機状態にする
	if (bossManager_.isAttackEnd()) {
		changeState(State::Idel, BOSS_IDLE);
		bossManager_.attackRefresh();
	}
}

void BaseBoss::wallAttack(float deltaTime)
{
	stateString_ = "壁攻撃";
	// bossManager_.wallAttack(deltaTime);
}

void BaseBoss::specialAttack(float deltaTime)
{
	stateString_ = "スペシャルな攻撃";
	// bossManager_.specialAttack(deltaTime);
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
		// 戻す y = -1.0fに
		// direction.y = -1.0f;
		direction.y = 1.0f;
		entryObj_->setDirection(direction);
	}
}
