#include "MediumBoss.h"
#include "../ImportAnimationNumber.h"
#include "../../Effect/AttackEffect.h"
//#include "../../../DeadEnemy.h"
#include "../../../../../UIActor/BossGaugeUI/BossGaugeUI.h"
#include "../../../../../Base/ActorGroup.h"
#include "../../../../../../World/IWorld.h"

MediumBoss::MediumBoss(
	IWorld * world, 
	const Vector2 & position, 
	const float bodyScale) : 
	FighterMiniBoss(world, position, bodyScale, "Boss"),
	hp_(100),
	damage_(20),
	direction_(Vector2::One),
	bossGaugeUI_(nullptr),
	mt_(std::mt19937())
{
	state_ = State::BattleIdel;
	// �����̎擾
	std::random_device random;
	// �����Z���k�c�C�X�^�[�@ ��Œ��ׂ�
	// ����Seed�l��n��
	std::mt19937 mt(random());
	mt_ = mt;
}

void MediumBoss::onUpdate(float deltaTime)
{
	FighterMiniBoss::onUpdate(deltaTime);
}

void MediumBoss::onDraw() const
{
	// ���u�����h�̐ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha_);
	SetDrawBright((int)color_.x, (int)color_.y, (int)color_.z);
	FighterMiniBoss::onDraw();
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void MediumBoss::battleIdel(float deltaTime)
{
	if (!world_->isMBossStage()) {
		stateTimer_ = 0.0f;
		return;
	}
	if (stateTimer_ < 2.0f) return;
	// �v���C���[�𓮂����Ԃɂ���
	world_->PlayerNotMove(false);
	// �{�X�̗̑̓Q�[�W
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
	// ���S���Ă��钆�{�X�̒ǉ�
	/*auto deadBoss = std::make_shared<DeadEnemy>(
		world_, position_, body_.GetBox().getWidth(),
		direction_, AnimationID::BOSS_DEATH_TEX);
	world_->addActor(ActorGroup::Enemy, deadBoss);
	deadBoss->setColor(color_);*/
	//dead();
}

// ���ɓ����������̏���
void MediumBoss::floorHit()
{
}

// �v���C���[�̍U���ɓ����������̏���
void MediumBoss::playerAttackHit(Actor & actor)
{
	hp_ -= damage_;
	damegeTimer_ = 2.0f;
	isAttackHit_ = true;
	bossGaugeUI_->SetHp(hp_);
	// �G�t�F�N�g�̐���
	world_->addActor(ActorGroup::Effect,
		std::make_shared<AttackEffect>(world_, actor.getPosition(), 1.0f));
	if (hp_ < 0) {
		changeState(State::Dead, DEAD_NUMBER);
		PlaySoundMem(
			ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_DEAD),
			DX_PLAYTYPE_BACK);
		animation_.setIsLoop(false);
		body_.enabled(false);
	}
}

// �����_���̒l���擾���܂�
int MediumBoss::getRandomInt(const int min, const int max)
{
	// �͈͂̎w��(int�^)
	std::uniform_int_distribution<> value(min, max);
	return value(mt_);
}
