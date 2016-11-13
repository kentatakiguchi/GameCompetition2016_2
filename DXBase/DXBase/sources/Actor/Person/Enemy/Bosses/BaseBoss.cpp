#include "BaseBoss.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../../../Base/ActorGroup.h"
#include "../../../Body/CollisionBase.h"
#include "../../../../Define.h"
#include "BossManager.h"
#include "BossEntry.h"
#include "BossHeart.h"
#include "../FloorSearchPoint.h"

// �{�X�N���X(�x�[�X�\��)
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
	stateString_("�ҋ@"),
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
	// �R���e�i�ɒǉ�(�U�����ɒǉ�����)
	asContainer_.push_back(AttackState::JumpAttack);
	asContainer_.push_back(AttackState::WallAttack);
	asContainer_.push_back(AttackState::SpeacialAttack);
	// �{�X�}�l�[�W���[
	/*auto manager = std::make_shared<BossManager>(position);
	bossManager_ = &*manager;*/
	// ���{���I�u�W�F�N�g
	auto fspObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, bodyScale + 1.0f), 0.1f
		);
	world_->addActor(ActorGroup::Enemy, fspObj);
	fspObj_ = &*fspObj;
	// �{�X�����I�u�W�F�N�g
	auto entryObj = std::make_shared<BossEntry>(
		world_, position_, 
		Vector2(bodyScale / 2.0f, bodyScale / 2.0f),
		bodyScale / 2.0f);
	world_->addActor(ActorGroup::Enemy, entryObj);
	entryObj_ = &*entryObj;
	// �{�X�S���I�u�W�F�N�g
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
	// ��ԃ^�C�}(�ő�l�P)�̍X�V
	setTimer(deltaTime);

	//
	hp_ = heartObj_->getBossHp();


	// ��Ԃ̍X�V
	updateState(deltaTime);
	// �ʒu���N�����v����
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
	// �ڒn(��)
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
	// �f�o�b�O
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �G�̕\��
	/*DrawGraph(
		position_.x - scale_ / 2.0f, position_.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);*/
	// ��Ԃ̕\��
	DrawString(
		vec3Pos.x, vec3Pos.y - 100,
		stateChar, GetColor(255, 255, 255));
	// �̗͂̕\��
	// �̗͂̕\��
	DrawFormatString(
		vec3Pos.x, vec3Pos.y - 150,
		GetColor(255, 255, 255), "�̗�:%d", hp_);
	DrawFormatString(
		vec3Pos.x, vec3Pos.y - 175,
		GetColor(255, 255, 255), "����:%d", (int)stateTimer_);
	body_.draw(inv_);
}

void BaseBoss::onCollide(Actor & actor)
{
	// �v���C���[�ɓ���������A�ϋv�l��������
	if (state_ == State::Flinch || state_ == State::Dead) return;
	auto actorName = actor.getName();
	if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
		auto damage = 10;
		dp_ -= damage;
		// �ϋv�l��0�ɂȂ�����A�Ђ��
		if (dp_ <= 0) {
			changeState(State::Flinch, BOSS_FLINCH);
			setBMStatus();
			body_.enabled(false);
			return;
		}
		// �������̂��߂�return
		return;
	}
}

void BaseBoss::onMessage(EventMessage event, void *)
{
}

void BaseBoss::updateState(float deltaTime)
{
	// ���݂͎g�p�s��
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
	// �ʒu�̍X�V
	//position_ = bossManager_->getMovePosition();
}

void BaseBoss::changeState(State state, unsigned int motion)
{
	// ������ԂȂ�Ԃ�
	if (state_ == state) return;
	state_ = state;
	stateTimer_ = 0.0f;
}

void BaseBoss::changeAttackState(AttackState aState, unsigned int motion)
{
	// �U����Ԃɋ����J�ڂ���
	changeState(State::Attack, BOSS_ATTACK);
	attackState_ = aState;
	bossManager_.prevPosition();
}

void BaseBoss::idel(float deltaTime)
{
	stateString_ = "�ҋ@���";
	// �v���C���[���擾�ł��Ă���΁A�G�l�~�[�}�l�[�W���[�Ɉʒu�Ȃǂ�����
	setBMStatus();
	// ��莞�Ԍo�߂ōU����ԂɑJ��
	if (stateTimer_ >= 5.0f) {
		// �c��̗͂ōU����Ԃ�ς���
		// initHp - hp
		changeAttackState(
			asContainer_[asContainer_.size() - hp_], BOSS_ATTACK);
		return;
	}
	// �d��
	if (position_.y < SCREEN_SIZE.y - CHIPSIZE - body_.GetCircle().getRadius()) {
		position_.y += 9.8f * (1.0f);// * 60.0f);
	}
}

void BaseBoss::attack(float deltaTime)
{
	// �U����Ԃ̑I��
	switch (attackState_) {
	case AttackState::JumpAttack: jumpAttack(deltaTime); break;
	case AttackState::WallAttack: wallAttack(deltaTime); break;
	case AttackState::SpeacialAttack: specialAttack(deltaTime); break;
	}

	// �U�����I��������A�ҋ@��ԂɑJ��
	//if (bossManager_->isAttackEnd()) {
	//	changeState(State::Idel, BOSS_IDLE);
	//	// �{�X�}�l�[�W���[�̓����l�����t���b�V��
	//	bossManager_->attackRefresh();
	//}
}

void BaseBoss::flinch(float deltaTime)
{
	stateString_ = "�Ђ��";
	entryObj_->setIsEntry(true);
	// �d��
	if (position_.y < FIELD_SIZE.y) {
		position_.y += 9.8f * (1.0f);// * 60.0f);
	}

	// �̓��ɓ����Ă�����A�n�[�g�ɓ��������Ƃ�m�点��
	if (entryObj_->isEntered() && !heartObj_->isLetOut()) {
		// �v���C���[���o�Ă�����A�ҋ@��Ԃɂ���
		stateTimer_ = 5.0f;
		heartObj_->setIsEntered(true);
	}
	// �̓��ɓ������牽������
	if (entryObj_->isEntered()) {
		// �v���C���[��ǂ��o���Ă��Ȃ��Ȃ�Ԃ�
		if (!heartObj_->isLetOut()) return;
		// �v���C���[���o�Ă���
		entryObj_->letOut();
	}
	// �̗͂�0�ɂȂ����玀�S
	if (hp_ <= 0) 
		changeState(State::Dead, BOSS_DEAD);
	// ��莞�Ԍo�߂őҋ@��ԂɑJ��
	if (stateTimer_ < 5.0f) return;
	changeState(State::Idel, BOSS_IDLE);
	entryObj_->setIsEntry(false);
	dp_ = initDp_;
}

void BaseBoss::deadMove(float deltaTime)
{
	stateString_ = "���S";
	//dead();
}

void BaseBoss::jumpAttack(float deltaTime)
{
	stateString_ = "�W�����v�U��";
	// �W�����v�U��
	bossManager_.attackMove(ATTACK_JUMPATTACK_NUMBER, deltaTime);
	position_ = bossManager_.getMovePosition();
	// �W�����v�U�����I�������A�ҋ@��Ԃɂ���
	if (bossManager_.isAttackEnd()) {
		changeState(State::Idel, BOSS_IDLE);
		bossManager_.attackRefresh();
	}
}

void BaseBoss::wallAttack(float deltaTime)
{
	stateString_ = "�ǍU��";
	// bossManager_.wallAttack(deltaTime);
}

void BaseBoss::specialAttack(float deltaTime)
{
	stateString_ = "�X�y�V�����ȍU��";
	// bossManager_.specialAttack(deltaTime);
}

void BaseBoss::setTimer(float deltaTime)
{
	timer_ = deltaTime * 60.0f;
}

// �{�X�}�l�[�W���[�̃X�e�[�^�X�̐ݒ�
void BaseBoss::setBMStatus()
{
	if (player_ != nullptr) {
		bossManager_.setPlayerPosition(player_->getPosition());
		bossManager_.setPosition(position_);
		// ����������
		auto direction = bossManager_.getPlayerDirection();
		// �߂� y = -1.0f��
		// direction.y = -1.0f;
		direction.y = 1.0f;
		entryObj_->setDirection(direction);
	}
}
