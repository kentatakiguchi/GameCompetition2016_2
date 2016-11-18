#include "BaseBoss.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../../../Base/ActorGroup.h"
#include "../../../Body/CollisionBase.h"
#include "../../../../Define.h"
#include "BossManager.h"
#include "BossEntry.h"
#include "BossHeart.h"
#include "../FloorSearchPoint.h"
// �{�X�̗͕̑\��
#include "../../../UIActor/BossGaugeUI/BossGaugeUI.h"

// �{�X�N���X(�x�[�X�\��)
BaseBoss::BaseBoss(IWorld * world, const Vector2 & position, const float bodyScale) :
	Actor(world, "BaseBoss", position,
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	dp_(100),
	initDp_(dp_),
	hp_(3),
	flinchCount_(0),
	// initHp_(hp_),
	stateTimer_(0.0f),
	timer_(0.0f),
	deltaTimer_(0.0f),
	isGround_(false),
	isSceneEnd_(false),
	stateString_("�ҋ@"),
	// bossManager_(nullptr),
	playerPastPosition_(Vector2::Zero),
	player_(nullptr),
	state_(State::Idel),
	attackState_(AttackState::JumpAttack),
	fspObj_(nullptr),
	entryObj_(nullptr),
	heartObj_(nullptr),
	bossGaugeUI_(nullptr),
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
	auto heartHP = 100;
	auto heartObj = std::make_shared<BossHeart>(
		world_, Vector2(position_.x + 128.0f, position_.y -32.0f), heartHP, hp_);
	world_->addActor(ActorGroup::Enemy, heartObj);
	heartObj_ = &*heartObj;
	// �{�X�̗̑̓Q�[�W
	auto bossUI = std::make_shared<BossGaugeUI>(world_, Vector2::Zero);
	world_->addUIActor(bossUI);
	bossGaugeUI_ = bossUI.get();
	bossGaugeUI_->SetHp(heartObj_->getHeartHp() * hp_);
}

BaseBoss::~BaseBoss()
{
}

void BaseBoss::onUpdate(float deltaTime)
{
	// ��ԃ^�C�}(�ő�l�P)�̍X�V
	setTimer(deltaTime);

	// �̗͂̍X�V
	hp_ = heartObj_->getBossHp();
	bossGaugeUI_->SetHp(heartObj_->getHeartHp());

	entryObj_->setBossPosition(position_);
	// ��Ԃ̍X�V
	updateState(deltaTime);
	// �ʒu���N�����v����
	/*if (fspObj_->isGround()) {
		position_.y = MathHelper::Clamp(position_.y,
			fspObj_->getFloorPosition().y - 100.0f,
			fspObj_->getFloorPosition().y - CHIPSIZE);
		bossManager_.setIsGround(fspObj_->isGround());
	}*/
	/*position_.x = MathHelper::Clamp(position_.x,
		CHIPSIZE + body_.GetCircle().getRadius(),
		FIELD_SIZE.x);
	position_.y = MathHelper::Clamp(position_.y,
		CHIPSIZE + body_.GetCircle().getRadius(),
		FIELD_SIZE.y);*/
	// �ڒn(��)
	bossManager_.setIsGround(isGround_);
	//if (position_.y < FIELD_SIZE.y) {
	//	bossManager_.setIsGround(false);
	//	// position_.y += 9.8f * (deltaTimer_ * 60.0f);
	//}
	//else if (position_.y == FIELD_SIZE.y)
	//	bossManager_.setIsGround(true);

	// bossManager_.setIsGround(fspObj_->isGround());
	fspObj_->setPosition(position_);
	/*entryObj_->setBossPosition(position_);*/
	// entryObj_->setDirection(direction_);
	//position_.y = MathHelper::Clamp(position_.y, -1000, 500.0f);

	isGround_ = false;
}

void BaseBoss::onDraw() const
{
	// �f�o�b�O
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �{�X�̕\��
	DrawGraph(
		vec3Pos.x - body_.GetCircle().getRadius(),
		vec3Pos.y - body_.GetCircle().getRadius(),
		ResourceLoader::GetInstance().getTextureID(TextureID::BOSS_TEX), 1);
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
	auto actorName = actor.getName();
	// �}�b�v�̃u���b�N�ɓ���������A�������s��
	if (actorName == "MovelessFloor") {
		// �ʒu�̕��
		groundClamp(actor);
		return;
	}
	// �󒆂ɕ����ԏ��ɓ���������A�Ђ�݃J�E���g�����Z����
	if (actorName == "���Ƃ�Floor") {
		// �ʒu�̕��
		groundClamp(actor);
		return;
	}
	// ����̏�Ԃł̓v���C���[�ɐG��Ă������N����Ȃ��悤�ɂ���
	if (state_ == State::Flinch || state_ == State::Dead) return;
	// �v���C���[�ɓ���������A�ϋv�l��������
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

// �V�[�����I�������邩��Ԃ��܂�
bool BaseBoss::isSceneEnd()
{
	return isSceneEnd_;
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
	// �f�o�b�O
	/*auto deltaTimer = deltaTime * 60.0f;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L))
		position_.x += 4.0f * deltaTimer;
	else if (InputMgr::GetInstance().IsKeyOn(KeyCode::J))
		position_.x += -4.0f * deltaTimer;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::I))
		position_.y += -4.0f * deltaTimer;
	else if (InputMgr::GetInstance().IsKeyOn(KeyCode::K))
		position_.y += 4.0f * deltaTimer;*/
	// ��莞�Ԍo�߂ōU����ԂɑJ��
	if (stateTimer_ >= 5.0f) {
		// �c��̗͂ōU����Ԃ�ς���
		// initHp - hp
		changeAttackState(
			asContainer_[asContainer_.size() - hp_], BOSS_ATTACK);
		return;
	}
	// �d��
	if (!isGround_) {
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
	// ���S�����莞�Ԍo�߂Ȃ�A�V�[�����I��������
	if (stateTimer_ >= 3.0f)
		isSceneEnd_ = true;
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

//�n�ʂ̈ʒu�ɕ␳���܂�
void BaseBoss::groundClamp(Actor& actor)
{
	if (actor.body_.GetBox().getWidth() == 0) return;
	// �����`���m�̌v�Z
	// �������g��1f�O�̒��S�ʒu���擾
	auto pos = body_.GetCircle().previousPosition_;
	// ���葤�̎l�p�`��4�_���擾
	auto topLeft = actor.getBody().GetBox().component_.point[0];
	auto topRight = actor.getBody().GetBox().component_.point[1];
	auto bottomLeft = actor.getBody().GetBox().component_.point[2];
	auto bottomRight = actor.getBody().GetBox().component_.point[3];
	// �O�ς��g���āA�c�̒������v�Z����
	auto top = Vector2::Cross(
		(topLeft - topRight).Normalize(), (pos - topRight));
	auto bottom = Vector2::Cross(
		(bottomRight - bottomLeft).Normalize(), (pos - bottomLeft));
	auto right = Vector2::Cross(
		(topRight - bottomRight).Normalize(), (pos - bottomRight));
	auto left = Vector2::Cross(
		(bottomLeft - topLeft).Normalize(), (pos - topLeft));

	/*if (top >= 0 && left <= 0 && right <= 0) {
		position_.y = t_left.y - (body_.GetCircle().component_.radius + 5);
	}
	if (bottom >= 0 && left <= 0 && right <= 0) {
		position_.y = b_right.y + (body_.GetCircle().component_.radius + 5);
	}
	if (right >= 0 && top <= 0 && bottom <= 0) {
		position_.x = t_right.x + (body_.GetCircle().component_.radius + 5);
	}
	if (left >= 0 && top <= 0 && bottom <= 0) {
		position_.x = b_left.x - (body_.GetCircle().component_.radius + 5);
	}*/
	// Y�����Ɉʒu���Ԃ���
	if (left < body_.GetCircle().getRadius() &&
		right < body_.GetCircle().getRadius()) {
		// ��ɕ��
		if (top > 0) {
			position_.y = topLeft.y - body_.GetCircle().getRadius();
			// �ڒn
			isGround_ = true;
		}
		// ���ɕ��
		if (bottom > 0)
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
	}
	// X�����Ɉʒu���Ԃ���
	if (top < body_.GetCircle().getRadius() &&
		bottom < body_.GetCircle().getRadius()) {
		// ���ɕ��
		if (left > 0)
			position_.x = bottomLeft.x - body_.GetCircle().getRadius();
		// �E�ɕ��
		if (right > 0)
			position_.x = topRight.x + body_.GetCircle().getRadius();
	}
}