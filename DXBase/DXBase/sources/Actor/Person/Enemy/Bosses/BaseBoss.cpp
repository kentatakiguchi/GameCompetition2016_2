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
	// �U����Ԃ��R���e�i�ɒǉ�(�U�����ɒǉ�����)
	asContainer_.push_back(AttackState::JumpAttack);
	asContainer_.push_back(AttackState::WallAttack);
	asContainer_.push_back(AttackState::SpeacialAttack);
	// �U���A�j���[�V�����R���e�i
	asAnimations_.push_back(JUMP_UP_NUMBER);
	asAnimations_.push_back(WALLATTACK_DASH_NUMBER);
	asAnimations_.push_back(BREATH_NUMBER);
	// �{�X�}�l�[�W���[�ɍU����ǉ�
	bossManager_.addAttack(std::make_shared<ThreeJumpAttack>(world_, position));
	bossManager_.addAttack(std::make_shared<WallAttack>(world_, position));
	bossManager_.addAttack(std::make_shared<DysonAttack>(world_, position));

	//// �U����Ԃ��R���e�i�ɒǉ�(�U�����ɒǉ�����)
	//asContainer_.push_back(AttackState::SpeacialAttack);
	//asContainer_.push_back(AttackState::WallAttack);
	//asContainer_.push_back(AttackState::JumpAttack);
	//// �U���A�j���[�V�����R���e�i
	//asAnimations_.push_back(BREATH_NUMBER);
	//asAnimations_.push_back(WALLATTACK_DASH_NUMBER);
	//asAnimations_.push_back(JUMP_UP_NUMBER);

	//// �{�X�}�l�[�W���[�ɍU����ǉ�
	//bossManager_.addAttack(std::make_shared<DysonAttack>(world_, position));
	//bossManager_.addAttack(std::make_shared<WallAttack>(world_, position));
	//bossManager_.addAttack(std::make_shared<ThreeJumpAttack>(world_, position));

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
		static_cast<int>(WAIT_NUMBER));
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
		world_, position_ + Vector2::Left * 50,
		Vector2(bodyScale / 1.75f, -bodyScale / 1.25f),
		bodyScale / 4.0f);
	world_->addActor(ActorGroup::Enemy, entryObj);
	entryObj_ = &*entryObj;
	// �{�X�̗̑̓Q�[�W
	auto bossUI = std::make_shared<BossGaugeUI>(world_, Vector2(64, -256));
	world_->addUIActor(bossUI);
	bossGaugeUI_ = bossUI.get();
	bossGaugeUI_->SetHp(hp_);
	// �Փ˔������񖳂���
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
	// ��ԃ^�C�}(�ő�l�P)�̍X�V
	setTimer(deltaTime);
	// �̗͂̍X�V
	bossGaugeUI_->SetHp(hp_);
	// �A�j���[�V�����̍X�V
	animation_.update(deltaTime);
	// �������Ă���I�u�W�F�N�g�̈ʒu�X�V
	entryObj_->setBossPosition(position_ + Vector2::Left * 50);
	wspObj_->setPosition(position_);
	// ��Ԃ̍X�V
	updateState(deltaTime);
	// �ڒn(��)
	bossManager_.setIsGround(isGround_);
	bossManager_.setIsBottom(isBottomHit_);
	// ��e������A�_���[�W�^�C�}�����Z����
	if (damageTimer_ > 0)
		damageTimer_ -= deltaTime;
	// bool�n
	isGround_ = false;
	isBottomHit_ = false;
}

void BaseBoss::onEnd()
{
	bossManager_.attackRefresh();
	// SE���Đ����Ȃ�A�~�߂�
	if (CheckSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_POKO)) == 1)
		StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_POKO));
}

void BaseBoss::onDraw() const
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
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
		groundClamp(actor);
		bossManager_.setFloorName(actorName.c_str());
		return;
	}
	// �v���C���[�̍U���ɓ�����Ȃ��ꍇ�͕Ԃ�
	if (!isAttackHit_ || damageTimer_ > 0 || attackCount_ == 2) return;
	if (state_ == State::Flinch) return;
	//if (damageTimer_ > 0 || attackCount_ == 2) return;
	// �v���C���[�̍U���͈͂ɓ��������ꍇ�̏���
	if (actorName == "PlayerAttackCollider") {
		// �J�E���g�����炷
		piyoriCount_--;
		// �_���[�W����
		damage(30, actor.getPosition(), 2.0f);
		// �{�X�}�l�[�W���[�ɐݒ�
		bossManager_.setCollideObj(actor);
		return;
	}
}

void BaseBoss::onMessage(EventMessage event, void *){}

// �V�[�����I�������邩��Ԃ��܂�
bool BaseBoss::isSceneEnd()
{
	return isSceneEnd_;
}

// �ړI�n�Ɉړ����܂�
void BaseBoss::movePosition(float deltaTime)
{
	// �ړI�n�Ǝ����̕������o��
	auto distance = movePos_ - position_;
	// �ړI�n�Ƒ��x�̍������x�ȉ��Ȃ�A�ʒu��ς���
	if (distance.Length() < moveSpeed_) {
		position_ = movePos_;
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
	player_ = world_->findActor("PlayerBody1");
	// �̗͂�0�ȉ��ɂȂ����玀�S
	if (hp_ <= 0) {
		name_ = "DeadBoss";
		isAttackHit_ = false;
		changeState(State::Dead, DEATH_NUMBER);
	}
	// ��Ԃ̍X�V
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
	// �A�j���[�V�����̕ύX
	animation_.setIsLoop(true);
	animation_.changeAnimation(static_cast<int>(num));
	// ������ԂȂ�Ԃ�
	if (state_ == state) return;
	state_ = state;
	stateTimer_ = 0.0f;
	angle_ = 0.0f;
}

void BaseBoss::changeAttackState(AttackState aState, int num)
{
	// �U����Ԃɋ����J�ڂ���
	changeState(State::Attack, num);
	// �摜�̕��������킹��
	animation_.changeDirType(direction_.x);
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
	// �o�g���J�n�łȂ��Ȃ�Ԃ�
	if (!isBattle_) return;
	// �W�����v�U����ԂɑJ��
	changeAttackState(AttackState::JumpAttack, JUMP_UP_NUMBER);
	isAttackHit_ = true;
	body_.enabled(true);
}

void BaseBoss::idel(float deltaTime)
{
	// �v���C���[���擾�ł��Ă���΁A�G�l�~�[�}�l�[�W���[�Ɉʒu�Ȃǂ�����
	setBMStatus();
	// �摜�̕��������킹��
	animation_.changeDirType(direction_.x);
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
	// �U���������邩�̔��������
	isAttackHit_ = bossManager_.IsAttackHit();
}

// �_���[�W���
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

// ���ݏ��
void BaseBoss::flinch(float deltaTime)
{
	name_ = "flinchBoss";
	flinchCount_ = 0;
	// �s��
	piyoriMove(deltaTime);
}

// �҂����
void BaseBoss::piyori(float deltaTime)
{
	name_ = "piyoriBoss";
	piyoriCount_ = 5;
	piyoriMove(deltaTime);
}

void BaseBoss::boko(float deltaTime)
{
	name_ = "BokoBoss";
	// ���̐���
	if (isEffectCreate_ && (int)effectCreateTimer_ % 50 <= 24 && bokoCreateCount_ < 2) {
		// �G�t�F�N�g�̒ǉ�
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
	// �f���^�^�C����0�ȉ��Ȃ�ASE���ꎞ��~����
	auto se = ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_POKO);
	if (CheckSoundMem(se) == 1 &&
		deltaTime <= 0) {
		StopSoundMem(se);
	}
	else if (CheckSoundMem(se) == 0 && deltaTime > 0) {
		// SE�̍Đ�(��~�����ӏ�����Đ�)
		PlaySoundMem(se, DX_PLAYTYPE_LOOP, false);
	}
	if (stateTimer_ < 2.0f) return;
	direction_.x = -1.0f;
	animation_.changeDirType(direction_.x);
	world_->setEntry(false, true);
	entryObj_->setIsEntry(false);
	// SE���Đ����Ȃ�A�~�߂�
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
	// ���S�����莞�Ԍo�߂Ȃ�A�V�[�����I��������
	if (stateTimer_ >= 3.0f)
		isSceneEnd_ = true;
}

// �҂��s��
void BaseBoss::piyoriMove(float deltaTime)
{
	entryObj_->setIsEntry(true);
	auto dir = direction_;
	dir.y = 1.0f;
	entryObj_->setDirection(dir);
	animation_.setIsLoop(true);
	// ���̐���
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
	// �҂��G�t�F�N�g�̈ʒu
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto addPos = Vector2::Up * -150;
		i->get()->position_ = position_ + addPos;
	}
	// �d��
	if (!isGround_ && bossManager_.isUseGravity()) {
		position_.y += 9.8f * deltaTimer_;// * 60.0f);
	}
	// ���̈�̍X�V
	auto posEffect = world_->findActor("EntrySignEffect");
	auto addPos = Vector2::Up * -225;
	if (posEffect != nullptr) {
		posEffect->position_ = entryObj_->getPosition() + addPos;
	}
	// �̓��ɓ����Ă�����A�n�[�g�ɓ��������Ƃ�m�点��
	if (entryObj_->isEntered()) {
		// �v���C���[���o�Ă�����A�ҋ@��Ԃɂ���
		stateTimer_ = 5.0f;
		// �X�^�[�̍폜
		for (auto i = stars_.begin(); i != stars_.end(); i++) {
			auto star = *i;
			star->dead();
		}
		// �G�t�F�N�g�̍폜
		auto effect = world_->findActor("EntrySignEffect");
		if (effect != nullptr)
			effect->dead();
		stars_.clear();
		effectCreateTimer_ = 0.0f;
		entryObj_->letOut();
		isEffectCreate_ = true;
		// ��Ԃɂ���čs����ς���
		if (state_ == State::Flinch) {
			// �J�E���g�����炷
			piyoriCount_--;
			// �_���[�W����
			damage(30, entryObj_->getPosition(), 0.8f);
			return;
		}
		else if (state_ == State::Piyori) {
			if (attackCount_ < asContainer_.size() - 1)
				attackCount_++;
			// �ڂ����ԂɕύX
			changeState(State::Boko, DAMAGE_BOKO_NUMBER);
			isAttackHit_ = false;
			world_->setEntry(true, false);
			// SE�̍Đ�
			PlaySoundMem(
				ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_POKO),
				DX_PLAYTYPE_LOOP);
			return;
		}
	}
	// ��莞�Ԍo�߂őҋ@��ԂɑJ��
	if (stateTimer_ < 5.0f) return;
	changeState(State::Idel, WAIT_NUMBER);
	name_ = "BaseEnemy";
	isAttackHit_ = true;
	entryObj_->setIsEntry(false);
	isEffectCreate_ = true;
	// �G�t�F�N�g�̍폜
	auto effect = world_->findActor("EntrySignEffect");
	if (effect != nullptr)
		effect->dead();
	// �X�^�[�̍폜
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto star = *i;
		star->dead();
	}
	stars_.clear();
	effectCreateTimer_ = 0.0f;
}

void BaseBoss::jumpAttack(float deltaTime)
{
	// �W�����v�U��
	bossManager_.attackMove(deltaTime);
	bossManager_.setPlayerPosition(player_->getPosition());
	position_ = bossManager_.getMovePosition();
	// �A�j���[�V�����̕ύX
	animation_.setIsLoop(bossManager_.isAnimeLoop());
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	animation_.changeDirType(bossManager_.getAttackDirection().x);
	// �W�����v�U�����I�������A�ҋ@��Ԃɂ���
	if (bossManager_.isAttackEnd()) {
		animation_.setIsLoop(true);
		changeState(State::Idel, WAIT_NUMBER);
		// �U���������邩�̔��������
		isAttackHit_ = true;
		bossManager_.attackRefresh();
	}
}

void BaseBoss::wallAttack(float deltaTime)
{
	bossManager_.attackMove(deltaTime);
	position_ = bossManager_.getMovePosition();
	// �A�j���[�V�����̕ύX
	angle_ = static_cast<float>(bossManager_.getAnimeAngle());
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	animation_.setIsLoop(bossManager_.isAnimeLoop());
	//animation_.turnAnimation(WALLATTACK_DASH_NUMBER, Vector2::Left.x);
	animation_.changeDirType(Vector2::Left.x);
	// �U�����쒆�Ȃ�A�Ǒ{���I�u�W�F�N�g�Ȃǂ̔����ON�ɂ���
	if (bossManager_.isAttackStart()) {
		setBMStatus();
		bossManager_.getPlayerNormalizeDirection();
	}
	// �W�����v�U�����I�������A�ҋ@��Ԃɂ���
	if (bossManager_.isAttackEnd()) {
		flinchCount_++;
		// �{�X�}�l�[�W�����̂Ђ�݉񐔈ȏ�Ȃ�A�Ђ�ݏ�ԂɑJ��	
		if (bossManager_.getFlinchCount() > flinchCount_) {
			changeState(State::Idel, WAIT_NUMBER);
			// �U���������邩�̔��������
			isAttackHit_ = true;
			bossManager_.attackRefresh();
			return;
		}
		else if (bossManager_.getFlinchCount() <= flinchCount_) {
			changeState(State::Flinch, PIYO_NUMBER);
			flinchCount_ = 0;
			isAttackHit_ = false;
			// ���ݏ�Ԃ̐ݒ�
			setPiyori();
			// �����̕ύX
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
	// ���Ƀv���C���[���m���Ȃ�����������A
	// �Ђ�ގ��ԂɒB����܂ł�
	// �����痣�ꂽ��A������x�U�����s��
	if (bossManager_.isFlinch()) {
		changeState(State::Flinch, PIYO_NUMBER);
		bossManager_.attackRefresh();
		isAttackHit_ = false;
		// ���ݏ�Ԃ̐ݒ�
		setPiyori();
		return;
	}

	name_ = "suikomiBoss";
	// isBlock() == true => �ǂ���Ă���
	bossManager_.setIsAttackMove(!entryObj_->isBlock());
	bossManager_.attackMove(deltaTime);
	position_ = bossManager_.getMovePosition();
	// �ǂɓ������Ă���ꍇ
	bossManager_.setIsWallHit(wspObj_->isGround());
	wspObj_->setDirection(bossManager_.getWallMoveDirection());
	// �A�j���[�V�����̕ύX
	animation_.changeAnimation(
		static_cast<int>(bossManager_.getAnimaNum()));
	animation_.setIsLoop(bossManager_.isAnimeLoop());
	animation_.changeDirType(bossManager_.getAttackDirection().x);

	if (bossManager_.isAttackEnd()) {
		name_ = "BaseEnemy";
		changeState(State::Idel, WAIT_NUMBER);
		// �U���������邩�̔��������
		isAttackHit_ = true;
		bossManager_.attackRefresh();
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
		// �ǂɓ������Ă���ꍇ
		bossManager_.setIsWallHit(wspObj_->isGround());
		if (wspObj_->isGround()) {
			wspObj_->setDirection(bossManager_.getWallMoveDirection());
		}
		wspObj_->setDirection(bossManager_.getWallMoveDirection());
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
	// �̗͂����b�N�����������Ȃ������Ԃ���
	if (hp_ < lockHps_[attackCount_]) {
		hp_ = lockHps_[attackCount_];
	}
	damageTimer_ = 1.0f;
	// �ҋ@���ɍU�����󂯂��玟�̍s���܂łɍU�����󂯂Ȃ��悤�ɂ���
	if (state_ == State::Idel)
		isAttackHit_ = false;
	// �G�t�F�N�g�̐���
	world_->addActor(ActorGroup::Effect,
		std::make_shared<AttackEffect>(world_, position, scale));
	// �ϋv�l��0�ɂȂ�����A�҂��
	if (piyoriCount_ <= 0) {
		changeState(State::Piyori, PIYO_NUMBER);
		// �Փ˂��邩�ǂ����� bool ��S��true�ɂ���
		piyoriCount_ = 5;
		setBMStatus();
		// �摜�̕��������킹��
		animation_.setIsLoop(true);
		//animation_.turnAnimation(DAMAGE_NUMBER, direction_.x);
		animation_.changeDirType(direction_.x);
		bossManager_.attackRefresh();
		// ���ݏ�Ԃ̐ݒ�
		setPiyori();
		return;
	}
	else {
		if (state_ == State::Idel || state_ == State::Flinch) {
			setBMStatus();
			// �摜�̕��������킹��
			//animation_.turnAnimation(DAMAGE_NUMBER, direction_.x);
			animation_.changeDirType(direction_.x);
			changeState(State::Damage, DAMAGE_NUMBER);
			isAttackHit_ = false;
		}
	}
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
}

// �e�N�X�`���̒ǉ����s���܂�
void BaseBoss::addAnimation()
{
	// �ҋ@
	animation_.addAnimation(
		static_cast<int>(WAIT_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WAIT_TEX));
	animation_.addAnimation(
		static_cast<int>(WAIT_TURN_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WAIT_TURN_TEX));
	// �W�����v�U��
	animation_.addAnimation(
		static_cast<int>(JUMP_UP_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_JUMP_UP_TEX));
	animation_.addAnimation(
		static_cast<int>(JUMP_DOWN_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_JUMP_DOWN_TEX));
	// �ǈړ��U��
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
	// �z�����ݍU��
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
	// ����
	animation_.addAnimation(
		static_cast<int>(PIYO_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_PIYO_TEX));
	// �_���[�W
	animation_.addAnimation(
		static_cast<int>(DAMAGE_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_DAMAGE_TEX));
	animation_.addAnimation(
		static_cast<int>(DAMAGE_BOKO_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_DAMAGE_BOKO_TEX));
	// ���S
	animation_.addAnimation(
		static_cast<int>(DEATH_NUMBER),
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_DEATH_TEX));
}

// �҂���Ԃ̐ݒ���s���܂�
void BaseBoss::setPiyori()
{
	// �U���������邩�̔��������
	isAttackHit_ = false;
	// �G�t�F�N�g�̐���
	auto effect = std::make_shared<EntrySignEffect>(
		world_, entryObj_->getPosition() - Vector2::Up * 150.0f);
	world_->addActor(ActorGroup::Effect, effect);
}
