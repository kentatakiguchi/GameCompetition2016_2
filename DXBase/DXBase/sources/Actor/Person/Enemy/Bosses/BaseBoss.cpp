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
// �{�X�̗͕̑\��
#include "../../../UIActor/BossGaugeUI/BossGaugeUI.h"

// �{�X�N���X(�x�[�X�\��)
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
	stateString_("�ҋ@"),
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

	// �U����Ԃ��R���e�i�ɒǉ�(�U�����ɒǉ�����)
	asContainer_.push_back(AttackState::JumpAttack);
	asContainer_.push_back(AttackState::WallAttack);
	asContainer_.push_back(AttackState::SpeacialAttack);
	// �U���A�j���[�V�����R���e�i
	asAnimations_.push_back(BossAnimationNumber::JUMP_UP_NUMBER);
	asAnimations_.push_back(BossAnimationNumber::WALLATTACK_DASH_NUMBER);
	asAnimations_.push_back(BossAnimationNumber::BREATH_NUMBER);

	// �{�X�}�l�[�W���[�ɍU����ǉ�
	bossManager_.addAttack(std::make_shared<ThreeJumpAttack>(world_, position));
	bossManager_.addAttack(std::make_shared<WallAttack>(world_, position));
	bossManager_.addAttack(std::make_shared<DysonAttack>(world_, position));

	//// �U����Ԃ��R���e�i�ɒǉ�(�U�����ɒǉ�����)
	//asContainer_.push_back(AttackState::SpeacialAttack);
	//asContainer_.push_back(AttackState::JumpAttack);
	//asContainer_.push_back(AttackState::WallAttack);
	//// �U���A�j���[�V�����R���e�i
	//asAnimations_.push_back(BossAnimationNumber::BREATH_NUMBER);
	//asAnimations_.push_back(BossAnimationNumber::JUMP_UP_NUMBER);
	//asAnimations_.push_back(BossAnimationNumber::WALLATTACK_DASH_NUMBER);

	//// �{�X�}�l�[�W���[�ɍU����ǉ�
	//bossManager_.addAttack(std::make_shared<DysonAttack>(world_, position));
	//bossManager_.addAttack(std::make_shared<ThreeJumpAttack>(world_, position));
	//bossManager_.addAttack(std::make_shared<WallAttack>(world_, position));

	// �̗͂����b�N����R���e�i�ɒǉ�
	lockHps_.clear();
	lockHps_.push_back(200);
	lockHps_.push_back(100);
	lockHps_.push_back(0);
	// �X�^�[�R���e�i�̏�����
	stars_.clear();
	// �A�j���[�V�����̒ǉ�
	addAnimation();
	animation_.changeAnimation(
		static_cast<int>(BossAnimationNumber::WAIT_NUMBER));

	// ���{���I�u�W�F�N�g
	auto wspObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(
			body_.GetCircle().getRadius(),
			body_.GetCircle().getRadius()), 10.0f);
	world_->addActor(ActorGroup::Enemy, wspObj);
	wspObj_ = &*wspObj;
	// �{�X�����I�u�W�F�N�g
	auto entryObj = std::make_shared<BossEntry>(
		world_, position_, 
		Vector2(bodyScale / 2.0f, -bodyScale / 1.5f),
		bodyScale / 4.0f);
	world_->addActor(ActorGroup::Enemy, entryObj);
	entryObj_ = &*entryObj;
	// �{�X�̗̑̓Q�[�W
	auto bossUI = std::make_shared<BossGaugeUI>(world_, Vector2::Zero);
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

	// ��ԃ^�C�}(�ő�l�P)�̍X�V
	setTimer(deltaTime);
	// �̗͂̍X�V
	bossGaugeUI_->SetHp(hp_);
	//bossManager_.setHeartHP(heartObj_->getHeartHp());
	// �A�j���[�V�����̍X�V
	animation_.update(deltaTime);

	entryObj_->setBossPosition(position_);
	wspObj_->setPosition(position_);
	// wspObj_->setDirection(direction_);
	// ��Ԃ̍X�V
	updateState(deltaTime);
	// �ڒn(��)
	bossManager_.setIsGround(isGround_);
	bossManager_.setIsBottom(isBottomHit_);

	if (damageTimer_ > 0) {
		damageTimer_ -= deltaTime;
	}
	
	// bool�n
	isGround_ = false;
	isBottomHit_ = false;
}

void BaseBoss::onDraw() const
{
	// �f�o�b�O
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	//// ��Ԃ̕\��
	//DrawString(
	//	vec3Pos.x, vec3Pos.y - 250,
	//	stateChar, GetColor(255, 255, 255));
	// �A�j���[�V�����̕`��
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	animation_.draw(
		pos - Vector2::Up * 10,
		Vector2::One * (body_.GetCircle().getRadius()) + Vector2::Up * 20,
		body_.GetCircle().getRadius() / (128 / 2), angle_);
}

void BaseBoss::onCollide(Actor & actor)
{
	auto actorName = actor.getName();

	// �u���b�N�̉����ɂԂ�������A������悤�ɂ���?
	// �v���O�����������āA�R�����g�A�E�g����
	// �}�b�v�̃u���b�N�ɓ���������A�������s��
	if (actorName == "MovelessFloor") {
		// �ʒu�̕��
		groundClamp(actor);
		bossManager_.setFloorName(actorName.c_str());
		return;
	}
	// �󒆂ɕ����ԏ��ɓ���������A�Ђ�݃J�E���g�����Z����
	if (actorName == "BossAreaFloor") {
		// �ʒu�̕��
		/*if (state_ == State::Attack)
			flinchCount_++;*/
		groundClamp(actor);
		bossManager_.setFloorName(actorName.c_str());
		return;
	}
	// ����̏�Ԃł̓v���C���[�ɐG��Ă������N����Ȃ��悤�ɂ���
	if (state_ == State::Flinch || state_ == State::Dead) return;
	if (damageTimer_ > 0) return;
	// �v���C���[�̍U���͈͂ɓ��������ꍇ�̏���
	if (actorName == "PlayerAttackCollider") {
		// �v���C���[�̍U���ɓ�����Ȃ��ꍇ�͕Ԃ�
		if (!isAttackHit_) return;
		// �_���[�W����
		damage(30, actor.getPosition(), 2.0f);
		// �{�X�}�l�[�W���[�ɐݒ�
		bossManager_.setCollideObj(actor);
		return;
	}
	//// �v���C���[�{�̂ɓ��������ꍇ�̏���
	//if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
	//	// �v���C���[�ɓ�����Ȃ��ꍇ�͕Ԃ�
	//	if (!isBodyHit_) return;
	//	// �_���[�W����
	//	damage(10, actor.getPosition(), 0.3f);
	//	//// �{�X�}�l�[�W���[�ɐݒ�
	//	//bossManager_.setCollideObj(actor);
	//	// �������̂��߂�return
	//	return;
	//}
}

void BaseBoss::onMessage(EventMessage event, void *)
{
}

// �V�[�����I�������邩��Ԃ��܂�
bool BaseBoss::isSceneEnd()
{
	return isSceneEnd_;
}

// �ړI�n�Ɉړ����܂�
void BaseBoss::movePosition(float deltaTime)
{
	/*movePos_ = position;
	moveSpeed_ = speed;*/
	// �����̈ʒu��
	auto distance = movePos_ - position_;
	//auto thisSpeed = speed;
	// �ړI�n�Ƒ��x�̍������x�ȉ��Ȃ�A�ʒu��ς���
	if (distance.Length() < moveSpeed_) {
		position_ = movePos_;
		//return true;
	}
	else
		position_ += Vector2::Normalize(distance)
		* moveSpeed_ * (deltaTime * 60.0f);
}

// �퓬���J�n���邩��Ԃ��܂�
void BaseBoss::setIsBattle(bool isBattle)
{
	isBattle_ = isBattle;
}

// �ړI�̈ʒu��ݒ肵�܂�
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
	// ���݂͎g�p�s��
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
	case State::Piyori: piyori(deltaTime); break;
	case State::Dead: deadMove(deltaTime); break;
	}

	stateTimer_ += deltaTime;
	// �ʒu�̍X�V
	//position_ = bossManager_->getMovePosition();
}

void BaseBoss::changeState(State state, BossAnimationNumber num)
{
	// �A�j���[�V�����̕ύX
	animation_.setIsLoop(true);
	animation_.changeAnimation(static_cast<int>(num));
	// ������ԂȂ�Ԃ�
	if (state_ == state) return;
	state_ = state;
	stateTimer_ = 0.0f;
	angle_ = 0.0f;
}

void BaseBoss::changeAttackState(AttackState aState, BossAnimationNumber num)
{
	// �U����Ԃɋ����J�ڂ���
	//if (attackState_ == aState) return;
	changeState(State::Attack, num);
	attackState_ = aState;
	bossManager_.prevPosition();
}

// �퓬�ҋ@���
void BaseBoss::battleIdel(float deltaTime)
{
	// �ړI�n���ݒ肳��Ă��Ȃ��Ȃ�Ԃ�
	if (movePos_.x == Vector2::Zero.x && 
		movePos_.y == Vector2::Zero.y) return;

	// �ړI�n�Ɉړ�
	movePosition(deltaTime);
	setBMStatus();

	// �o�g���J�n�łȂ��Ȃ�
	if (!isBattle_) return;
	// �ҋ@��ԂɑJ��
	//changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
	changeAttackState(AttackState::JumpAttack,
		BossAnimationNumber::JUMP_UP_NUMBER);
	body_.enabled(true);
}

void BaseBoss::idel(float deltaTime)
{
	stateString_ = "�ҋ@���";
	// �v���C���[���擾�ł��Ă���΁A�G�l�~�[�}�l�[�W���[�Ɉʒu�Ȃǂ�����
	setBMStatus();
	// �U���������邩�̔��������
	isAttackHit_ = true;
	isBodyHit_ = true;
	// �摜�̕��������킹��
	animation_.turnAnimation(motion_, direction_.x);

	//bossManager_.changeAttackNumber(asContainer_.size() - hp_);
	bossManager_.changeAttackNumber(attackCount_);

	// ��莞�Ԍo�߂ōU����ԂɑJ��
	if (stateTimer_ >= 5.0f) {
		// �U���s���̃J�E���g�ōs�������߂�
		changeAttackState(
			asContainer_[attackCount_],
			asAnimations_[attackCount_]);
		return;
	}
	// �d��
	if (!isGround_ && bossManager_.isUseGravity()) {
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
	// 
	//animation_.setIsLoop(bossManager_.isAnimeLoop());
	//animation_.changeAnimation(static_cast<int>(bossManager_.getAnimaNum()));

	/*if(!bossManager_.isAttackEnd())
		animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));*/
	// �U���������邩�̔��������
	isAttackHit_ = bossManager_.IsAttackHit();
	isBodyHit_ = bossManager_.IsBodyHit();

	// �U�����I��������A�ҋ@��ԂɑJ��
	//if (bossManager_->isAttackEnd()) {
	//	changeState(State::Idel, BOSS_IDLE);
	//	// �{�X�}�l�[�W���[�̓����l�����t���b�V��
	//	bossManager_->attackRefresh();
	//}
}

// ���ݏ��
void BaseBoss::flinch(float deltaTime)
{
	stateString_ = "�Ђ��";
	name_ = "flinchBoss";
	entryObj_->setIsEntry(true);
	flinchCount_ = 0;
	animation_.setIsLoop(true);

	//if (starCreateCount_ % 50 == 0 && stars_.size() < 6){
	//	auto addPos = Vector2::Right * 100;
	//	auto star = std::make_shared<PiyoriEffect>(
	//		world_, position_ + addPos);
	//	world_->addActor(ActorGroup::Effect, star);
	//	stars_.push_back(star);
	//}
	//starCreateCount_++;
	//// �҂��G�t�F�N�g�̈ʒu
	//for (auto i = stars_.begin(); i != stars_.end(); i++) {
	//	auto addPos = Vector2::Right * 100;
	//	i->get()->position_ = position_ + addPos;
	//}

	// �d��
	if (!isGround_ && bossManager_.isUseGravity()) {
		position_.y += 9.8f * (1.0f);// * 60.0f);
	}

	//// �̓��ɓ������ꍇ�A�̗͂����炷
	//if (entryObj_->isEntered()) {
	//	entryObj_->letOut();
	//	entryObj_->setIsEntry(false);
	//	heartObj_->addBossHp(-50);
	//	changeState(State::Idel, BOSS_IDLE);
	//}

	// �̓��ɓ����Ă�����A�n�[�g�ɓ��������Ƃ�m�点��
	if (entryObj_->isEntered()) {
		// �v���C���[���o�Ă�����A�ҋ@��Ԃɂ���
		//stateTimer_ = 5.0f;
		stateTimer_ = 5.0f;
		//heartObj_->setIsEntered(true);
		//heartObj_->addBossHp(-30);
		// �_���[�W����
		damage(30, entryObj_->getPosition(), 0.8f);
		/*if (attackCount_ < asContainer_.size() - 1)
			attackCount_++;*/
		entryObj_->letOut();
	}
	//// �̓��ɓ������牽������
	//if (entryObj_->isEntered()) {
	//	// �v���C���[��ǂ��o���Ă��Ȃ��Ȃ�Ԃ�
	//	//if (!heartObj_->isLetOut()) return;
	//	// �v���C���[���o�Ă���
	//	entryObj_->letOut();
	//}

	//// �̗͂�0�ɂȂ����玀�S
	//if (hp_ <= 0) {
	//	changeState(State::Dead, BossAnimationNumber::DEATH_NUMBER);
	//	return;
	//}
	// ��莞�Ԍo�߂őҋ@��ԂɑJ��
	if (stateTimer_ < 5.0f) return;
	changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
	name_ = "BaseEnemy";
	entryObj_->setIsEntry(false);
	//dp_ = initDp_;
	//// �X�^�[�̍폜
	//for (auto i = stars_.begin(); i != stars_.end(); i++) {
	//	auto star = *i;
	//	star->dead();
	//}
	//stars_.clear();
	//starCreateCount_ = 0;
}

// �҂����
void BaseBoss::piyori(float deltaTime)
{
	stateString_ = "�҂��";
	name_ = "piyoriBoss";
	entryObj_->setIsEntry(true);
	//flinchCount_ = 0;
	animation_.setIsLoop(true);
	// ���̐���
	if (starCreateCount_ % 50 == 0 && stars_.size() < 6) {
		auto addPos = Vector2::Right * 100;
		auto star = std::make_shared<PiyoriEffect>(
			world_, position_ + addPos);
		world_->addActor(ActorGroup::Effect, star);
		stars_.push_back(star);
	}
	starCreateCount_++;
	// �҂��G�t�F�N�g�̈ʒu
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto addPos = Vector2::Right * 100;
		i->get()->position_ = position_ + addPos;
	}

	// �d��
	if (!isGround_ && bossManager_.isUseGravity()) {
		position_.y += 9.8f * (1.0f);// * 60.0f);
	}
	// �̓��ɓ����Ă�����A�n�[�g�ɓ��������Ƃ�m�点��
	if (entryObj_->isEntered()) {
		// �v���C���[���o�Ă�����A�ҋ@��Ԃɂ���
		stateTimer_ = 5.0f;
		if (attackCount_ < asContainer_.size() - 1)
			attackCount_++;
		// �G�t�F�N�g�̒ǉ�
		auto addPos = Vector2::One * 220.0f;
		world_->addActor(ActorGroup::Effect,
			std::make_shared<BokoEffect>(world_, position_ + addPos));
		world_->setEntry(true, false);
		entryObj_->letOut();
	}
	// ��莞�Ԍo�߂őҋ@��ԂɑJ��
	if (stateTimer_ < 5.0f) return;
	changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
	name_ = "BaseEnemy";
	entryObj_->setIsEntry(false);
	// �X�^�[�̍폜
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto star = *i;
		star->dead();
	}
	stars_.clear();
	starCreateCount_ = 0;
}

void BaseBoss::deadMove(float deltaTime)
{
	stateString_ = "���S";
	animation_.setIsLoop(false);
	if (animation_.isEndAnimation()) {
		// �A�j���[�V�������~������
		//dead();
	}
	// ���S�����莞�Ԍo�߂Ȃ�A�V�[�����I��������
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

	stateString_ = "�W�����v�U��";
	// �v���C���[�{�̂ɓ�����Ȃ�
	//isBodyHit_ = false;
	// �W�����v�U��
	bossManager_.attackMove(deltaTime);
	bossManager_.setPlayerPosition(player_->getPosition());
	position_ = bossManager_.getMovePosition();
	// �A�j���[�V�����̕ύX
	animation_.setIsLoop(bossManager_.isAnimeLoop());
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	/*animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));*/
	animation_.turnAnimation(motion_, bossManager_.getAttackDirection().x);
	if (bossManager_.isPiyori()) {
		changeState(State::Piyori, BossAnimationNumber::PIYO_NUMBER);
		animation_.setIsLoop(true);
		bossManager_.attackRefresh();
	}
	// �W�����v�U�����I�������A�ҋ@��Ԃɂ���
	if (bossManager_.isAttackEnd()) {
		changeState(State::Idel, BossAnimationNumber::WAIT_NUMBER);
		//isBodyHit_ = true;
		animation_.setIsLoop(true);
		bossManager_.attackRefresh();
	}
}

void BaseBoss::wallAttack(float deltaTime)
{
	stateString_ = "�ǍU��";
	bossManager_.attackMove(deltaTime);
	position_ = bossManager_.getMovePosition();
	// �A�j���[�V�����̕ύX
	angle_ = bossManager_.getAnimeAngle();
	animation_.setIsLoop(bossManager_.isAnimeLoop());
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	/*animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));*/
	animation_.turnAnimation(motion_, Vector2::Left.x);
	// �U�����쒆�Ȃ�A�Ǒ{���I�u�W�F�N�g�Ȃǂ̔����ON�ɂ���
	if (bossManager_.isAttackStart()) {
		setBMStatus();
		bossManager_.getPlayerNormalizeDirection();
	}
	// �W�����v�U�����I�������A�ҋ@��Ԃɂ���
	if (bossManager_.isAttackEnd()) {
		//flinchCount_ = 0;
		flinchCount_++;
		//if (flinchCount_ == 0)
		// �U�����̂Ђ�݉񐔂ƈȏ�Ȃ�A�Ђ�ݏ�ԂɑJ��
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
	// ���Ƀv���C���[���m���Ȃ�����������A
	// �Ђ�ގ��ԂɒB����܂ł�
	// �����痣�ꂽ��A������x�U�����s��

	if (bossManager_.isFlinch()) {
		changeState(State::Flinch, BossAnimationNumber::PIYO_NUMBER);
		bossManager_.attackRefresh();
		//angleCount_ = 0;
		//angle_ = 0.0f;
		return;
	}

	stateString_ = "�X�y�V�����ȍU��";
	// isBlock() == true => �ǂ���Ă���
	bossManager_.setIsAttackMove(!entryObj_->isBlock());
	bossManager_.attackMove(deltaTime);
	position_ = bossManager_.getMovePosition();
	// �p�x�̕ύX
	//angle_ = bossManager_.getAngle();

	// �ǂɓ������Ă���ꍇ
	bossManager_.setIsWallHit(wspObj_->isGround());
	wspObj_->setDirection(bossManager_.getWallMoveDirection());
	// �A�j���[�V�����̕ύX
	animation_.setIsLoop(bossManager_.isAnimeLoop());
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	/*animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));*/
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

// �{�X�}�l�[�W���[�̃X�e�[�^�X�̐ݒ�
void BaseBoss::setBMStatus()
{
	if (player_ != nullptr) {
		bossManager_.setPlayerPosition(player_->getPosition());
		bossManager_.setPosition(position_);
		// ����������
		auto direction = bossManager_.getPlayerDirection();
		direction_ = direction;
		//wspObj_->setDirection(direction);
		// �ǂɓ������Ă���ꍇ
		bossManager_.setIsWallHit(wspObj_->isGround());
		if (wspObj_->isGround()) {
			wspObj_->setDirection(bossManager_.getWallMoveDirection());
		}
		wspObj_->setDirection(bossManager_.getWallMoveDirection());
		/*if (wspObj_->isGround()) {
			
		}*/

		// �߂� y = -1.0f��
		// direction.y = -1.0f;
		direction.y = 1.0f;
		entryObj_->setDirection(direction);
	}
}

// �w�肵���l�̃_���[�W�ʂ����Z���܂�
void BaseBoss::damage(const int damage, const Vector2& position, const float scale)
{
	hp_ -= damage;
	//dp_--;
	// �̗͂����b�N�����������Ȃ������Ԃ���
	if (hp_ < lockHps_[attackCount_]) {
		hp_ = lockHps_[attackCount_];
	}
	damageTimer_ = 1.0f;
	// �G�t�F�N�g�̐���
	world_->addActor(ActorGroup::Effect,
		std::make_shared<AttackEffect>(world_, position, scale));
	// �ϋv�l��0�ɂȂ�����A�Ђ��
	//if (dp_ <= 0) {
	//	changeState(State::Flinch, BossAnimationNumber::PIYO_NUMBER);
	//	// �Փ˂��邩�ǂ����� bool ��S��true�ɂ���
	//	isBodyHit_ = true;
	//	isAttackHit_ = true;
	//	setBMStatus();
	//	// �摜�̕��������킹��
	//	animation_.turnAnimation(motion_, direction_.x);
	//}

	//if (dp_ <= 0) {
	//	changeState(State::Flinch, BossAnimationNumber::PIYO_NUMBER);
	//	// �Փ˂��邩�ǂ����� bool ��S��true�ɂ���
	//	isBodyHit_ = true;
	//	isAttackHit_ = true;
	//	setBMStatus();
	//	// �摜�̕��������킹��
	//	animation_.turnAnimation(motion_, direction_.x);
	//}
}

//�n�ʂ̈ʒu�ɕ␳���܂�
void BaseBoss::groundClamp(Actor& actor)
{
	if (actor.body_.GetBox().getWidth() == 0) return;
	// �V�~�Ɛ����`�̏Փ˔���
	// �������g��1f�O�̒��S�ʒu���擾
	auto isHit = false;
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

	top_ = top;
	bottom_ = bottom;
	right_ = right;
	left_ = left;
	// �ߋ��̈ʒu
	// Y�����Ɉʒu���Ԃ���
	if (left < 0 &&
		right < 0) {
		// ��ɕ��
		if (top > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = topLeft.y - body_.GetCircle().getRadius();
			// �ڒn
			isGround_ = true;
			isHit = true;
		}
		// ���ɕ��
		if (bottom > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
			// �u���b�N�̉����ɓ�������
			isBottomHit_ = true;
			isHit = true;
		}
	}
	// X�����Ɉʒu���Ԃ���
	else if (top < 0 &&
		bottom < 0) {
		// ���ɕ��
		if (left > 0) {
			position_.x = bottomLeft.x - body_.GetCircle().getRadius();
			isHit = true;
		}
		// �E�ɕ��
		if (right > 0) {
			position_.x = topRight.x + body_.GetCircle().getRadius();
			isHit = true;
		}
	}
	bossManager_.setPosition(position_);
	bossManager_.prevPosition();
	if (isHit) return;

	// ���݂̔���
	pos = position_;
	// �O�ς��g���āA�c�̒������v�Z����
	top = Vector2::Cross(
		(topLeft - topRight).Normalize(), (pos - topRight));
	bottom = Vector2::Cross(
		(bottomRight - bottomLeft).Normalize(), (pos - bottomLeft));
	right = Vector2::Cross(
		(topRight - bottomRight).Normalize(), (pos - bottomRight));
	left = Vector2::Cross(
		(bottomLeft - topLeft).Normalize(), (pos - topLeft));
	// Y�����Ɉʒu���Ԃ���
	if (left < 0 &&
		right < 0) {
		// ��ɕ��
		if (top > -actor.getBody().GetBox().getHeight() / 2.0f) {
			position_.y = topLeft.y - body_.GetCircle().getRadius();
			// �ڒn
			isGround_ = true;
		}
		// ���ɕ��
		if (bottom > -actor.getBody().GetBox().getHeight() / 2.0f) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
			// �u���b�N�̉����ɓ�������
			isBottomHit_ = true;
		}
	}
	// X�����Ɉʒu���Ԃ���
	if (top < 0 &&
		bottom < 0) {
		// ���ɕ��
		if (left > -actor.getBody().GetBox().getWidth() / 2.0f)
			position_.x = bottomLeft.x - body_.GetCircle().getRadius();
		// �E�ɕ��
		if (right > -actor.getBody().GetBox().getWidth() / 2.0f)
			position_.x = topRight.x + body_.GetCircle().getRadius();
	}
	bossManager_.setPosition(position_);
	bossManager_.prevPosition();

	// 60
	// 160
	//// ���ɕ��
	//if (left > -14)
	//	position_.x = bottomLeft.x - body_.GetCircle().getRadius();
	//// �E�ɕ��
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
	////	// pc = p1 + v * t + r * Vector2.Normalize(vn); // ���S���ړ�
	////	position_ = topLeft + topV * t + body_.GetCircle().getRadius() *
	////		Vector2::Normalize(vn);
	////}
	//top_ = vn.Length();
}

// �e�N�X�`���̒ǉ����s���܂�
void BaseBoss::addAnimation()
{
	// �ҋ@
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::WAIT_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WAIT_TEX));
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::WAIT_TURN_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WAIT_TURN_TEX));
	// �W�����v�U��
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::JUMP_UP_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_JUMP_UP_TEX));
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::JUMP_DOWN_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_JUMP_DOWN_TEX));
	// �ǈړ��U��
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::WALLATTACK_DASH_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WALLATTACK_DASH_TEX));
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::WALLATTACK_DASHJUMP_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WALLATTACK_DASHJUMP_TEX));
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::WALLATTACK_DASHJUMP_STOP_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WALLATTACK_DASHJUMP_STOP_TEX));
	// �z�����ݍU��
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::BREATH_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_BREATH_TEX));
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::BREATH_TURN_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_BREATH_TURN_TEX));
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::BREATH_DYSFUNCTION_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_BREATH_DYSFUNCTION_TEX));
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::BREATH_LESS_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_BREATH_LESS_TEX));
	// ����
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::PIYO_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_PIYO_TEX));
	// �_���[�W
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::DAMAGE_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_DAMAGE_TEX));
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::DAMAGE_BOKO_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_DAMAGE_BOKO_TEX));
	// ���S
	animation_.addAnimation(
		static_cast<int>(BossAnimationNumber::DEATH_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_DEATH_TEX));
}