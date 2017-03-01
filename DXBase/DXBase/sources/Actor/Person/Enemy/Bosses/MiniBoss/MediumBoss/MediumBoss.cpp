#include "MediumBoss.h"
#include "../ImportAnimationNumber.h"
#include "../../../../../UIActor/BossGaugeUI/BossGaugeUI.h"
#include "../../../../../../World/IWorld.h"

MediumBoss::MediumBoss(
	IWorld * world, 
	const Vector2 & position, 
	const float bodyScale) : 
	FighterMiniBoss(world, position, bodyScale, "MediumBoss"),
	hp_(100),
	damage_(20),
	direction_(Vector2::One),
	bossGaugeUI_(nullptr),
	mt_(std::mt19937())
{
	state_ = State::BattleIdel;
	// 乱数の取得
	std::random_device random;
	// メルセンヌツイスター法 後で調べる
	// 初期Seed値を渡す
	std::mt19937 mt(random());
	mt_ = mt;
}

void MediumBoss::onUpdate(float deltaTime)
{
	FighterMiniBoss::onUpdate(deltaTime);
}

void MediumBoss::battleIdel(float deltaTime)
{
	if (!world_->isMBossStage()) {
		stateTimer_ = 0.0f;
		return;
	}
	if (stateTimer_ < 2.0f) return;
	// ボスの体力ゲージ
	auto bossUI = std::make_shared<BossGaugeUI>(world_, Vector2(64, -256));
	world_->addUIActor(bossUI);
	bossGaugeUI_ = bossUI.get();
	bossGaugeUI_->SetHp(hp_);
	changeState(State::Idel, WAIT_NUMBER);
}

void MediumBoss::idel(float deltaTime)
{
}

void MediumBoss::move(float deltaTime)
{
}

void MediumBoss::attack(float deltaTime)
{
}

void MediumBoss::deadMove(float deltaTime)
{
	degree_ = 90.0f;
	if (!isGround_)
		position_.y += 9.8f * (deltaTime * 60.0f);
	if (stateTimer_ < 2.0f) return;
	name_ = "DeadMediumBoss";
	if (bossGaugeUI_ != nullptr) {
		bossGaugeUI_->dead();
		bossGaugeUI_ = nullptr;
	}
	//dead();
}

// 床に当たった時の処理
void MediumBoss::floorHit()
{
}

// プレイヤーの攻撃に当たった時の処理
void MediumBoss::playerAttackHit()
{
	hp_ -= damage_;
	damegeTimer_ = 2.0f;
	bossGaugeUI_->SetHp(hp_);
	if (hp_ < 0) {
		changeState(State::Dead, DEAD_NUMBER);
		animation_.setIsLoop(false);
		body_.enabled(false);
	}
}

// ランダムの値を取得します
int MediumBoss::getRandomInt(const int min, const int max)
{
	// 範囲の指定(int型)
	std::uniform_int_distribution<> value(min, max);
	return value(mt_);
}
