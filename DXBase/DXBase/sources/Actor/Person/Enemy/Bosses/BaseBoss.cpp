#include "BaseBoss.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../../../Base/ActorGroup.h"
#include "../../../Body/CollisionBase.h"
#include "BossManager.h"

BaseBoss::BaseBoss(IWorld * world, const Vector2 & position, const float bodyScale) : 
	Actor(world, "BaseEnemy", position,
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	dp_(20),
	initDp_(dp_),
	hp_(3),
	stateTimer_(0.0f),
	timer_(0.0f),
	deltaTimer_(0.0f),
	stateString_("待機"),
	// bossManager_(nullptr),
	playerPastPosition_(Vector2::Zero),
	player_(nullptr),
	state_(State::Idel),
	attackState_(AttackState::JumpAttack),
	bossManager_(BossManager(position))
{
	// ボスマネージャー
	/*auto manager = std::make_shared<BossManager>(position);
	bossManager_ = &*manager;*/
}

BaseBoss::~BaseBoss()
{
}

void BaseBoss::onUpdate(float deltaTime)
{
	// 補間タイマ(最大値１)の更新
	setTimer(deltaTime);
	// 状態の更新
	updateState(deltaTime);
	// 位置をクランプする
	position_.y = MathHelper::Clamp(position_.y, -1000, 500.0f);
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
	// 文字の表示
	DrawString(
		vec3Pos.x, vec3Pos.y,
		stateChar, GetColor(255, 255, 255));
	body_.draw(inv_);
}

void BaseBoss::onCollide(Actor & actor)
{
	// プレイヤーに当たったら、耐久値を下げる

	//auto actorName = actor.getName();
	//if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
	//	auto damage = 10;
	//	hp_ -= damage;
	//	dp_ -= damage;
	//	// 体力が0になったら死亡
	//	if (hp_ <= 0) {
	//		changeState(State::Dead, BOSS_DEAD);
	//		body_.enabled(false);
	//		return;
	//	}
	//	// 耐久値が0になったら、ひるむ
	//	if (dp_ <= 0) {
	//		changeState(State::Flinch, BOSS_FLINCH);
	//		body_.enabled(false);
	//		return;
	//	}
	//	// もしものためのreturn
	//	return;
	//}
}

void BaseBoss::onMessage(EventMessage event, void *)
{
}

void BaseBoss::updateState(float deltaTime)
{
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
	state_ = state;
	stateTimer_ = 0.0f;
}

void BaseBoss::changeAttackState(AttackState aState, unsigned int motion)
{
	attackState_ = aState;
}

void BaseBoss::idel(float deltaTime)
{
	stateString_ = "待機状態";
	// 一回状態を変える
	if (stateTimer_ >= 5.0f) {
		changeAttackState(AttackState::JumpAttack, BOSS_ATTACK);
		changeState(State::Attack, BOSS_ATTACK);
	}

	// bossManager_->attackMove(ATTACK_JUMPATTACK_NUMBER);
	// position_ = bossManager_->getMovePosition();

	// jumpAttack_.update(deltaTime);
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
	//	bossManager_->moveRefresh();
	//}
}

void BaseBoss::flinch(float deltaTime)
{
	stateString_ = "ひるみ";
	// 一定時間経過で待機状態に遷移
	if (stateTimer_ < 5.0f) return;
	changeState(State::Idel, BOSS_IDLE);
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
	if (bossManager_.isAttackEnd())
		changeState(State::Idel, BOSS_IDLE);
	// bossManager_.jumpAttack(deltaTime);
	// bossManager_->attackMove(ATTACK_JUMPATTACK_NUMBER);
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
