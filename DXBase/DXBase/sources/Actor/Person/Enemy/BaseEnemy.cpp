#include "BaseEnemy.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"
#include "FloorSearchPoint.h"
#include "PlayerSearchObj.h"
#include "Bosses/Effect/EnemyDeadEffect.h"
#include "Bosses/Effect/EnemyCollideEffect.h"
//#include "DeadEnemy.h"

BaseEnemy::BaseEnemy(
	IWorld * world,
	const Vector2& position,
	const float bodyScale,
	const Vector2& direction) :
	Actor(world, "BaseEnemy", position,
		CollisionBase(
			Vector2(position.x + bodyScale / 2.0f, position.y + bodyScale / 2.0f),
			Vector2(position.x - bodyScale / 2.0f, position.y + bodyScale / 2.0f),
			Vector2(position.x + bodyScale / 2.0f, position.y - bodyScale / 2.0f),
			Vector2(position.x - bodyScale / 2.0f, position.y - bodyScale / 2.0f)
			)),
	hp_(10),
	ap_(0),
	texSize_(256),
	turnMotion_(ENEMY_WALK),
	speed_(1.0f),
	initSpeed_(speed_),
	scale_(bodyScale),
	direction_(direction),
	prevDirection_(direction),
	playerLength_(0.0f),
	TexDegress_(0),
	hitTimer_(0.0f),
	isPlayer_(false),
	isMove_(false),
	isScreen_(false),
	isBlockCollideBegin_(false),
	isBlockCollideEnter_(false),
	isBlockCollidePrevEnter_(false),
	isBlockCollideExit_(false),
	isGround_(false),
	isUseGravity_(true),
	isInvincible_(false),
	isMoveFloor_(false),
	discoveryLenght_(500),
	stateTimer_(0.0f),
	state_(State::Idel),
	discoveryPosition_(Vector2::Zero),
	addTexPosition_(Vector2(0.0f, 40.0f)),
	player_(nullptr),
	psObj_(nullptr),
	fspScript_(nullptr),
	wsScript_(nullptr),
	pricleObj_(nullptr),
	enemyManager_(EnemyManager(position, direction)),
	animation_(EnemyAnimation2D()),
	seHandle_(0)
{
	// ray�I�u�W�F�N�g�̒ǉ�
	auto player = world_->findActor("PlayerBody1");
	if (player != nullptr) {
		auto ray = std::make_shared<PlayerSearchObj>(
			world_, position_, player->getPosition());
		world_->addActor(ActorGroup::EnemyBullet, ray);
		psObj_ = &*ray;
		objContainer_.push_back(psObj_);
		isPlayer_ = true;
	}
	// SE�̒ǉ�
	seHandle_ = LoadSoundMem("./resources/sounds/enemy/enemy_hakkenn.mp3");
}

BaseEnemy::~BaseEnemy()
{
	fspPositionContainer_.clear();
	fspScaleContainer_.clear();
	objContainer_.clear();
}

void BaseEnemy::Initialize()
{
	// ���{���I�u�W�F�N�g�̒ǉ�
	auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, 0.0f + scale_ / 2.0f),
		Vector2(scale_, 2.0f));
	// ���[���h�ɒǉ�
	world_->addActor(ActorGroup::Enemy, fsObj);
	fspScript_ = &*fsObj;
	objContainer_.push_back(fspScript_);
	fspScript_->setPosition(position_);
	// �Ǒ{���I�u�W�F�N�g
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(scale_ / 2.0f, 0.0f),
		Vector2(2.0f, scale_ - 30.0f));
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsScript_ = &*wsObj;
	objContainer_.push_back(wsScript_);
	// �A�j���[�V�����̒ǉ�
	addAnimation();
	animation_.changeAnimation(ENEMY_WALK);
	animation_.changeDirType(direction_.x);
	//animation_.turnAnimation(turnMotion_, direction_.x);
}

void BaseEnemy::onUpdate(float deltaTime)
{
	// �q���p��update(�e��update�O�ɍs���܂�)
	beginUpdate(deltaTime);
	// �f���^�^�C���̒l��ݒ肷��
	setDeltaTime(deltaTime);
	// �G�l�~�[�}�l�[�W���[�̍X�V
	enemyManager_.update(deltaTime);
	// �A�j���[�V�����̍X�V
	animation_.update(deltaTime);
	// ��Ԃ̍X�V
	updateState(deltaTime);
	// �{���I�u�W�F�N�g�̍X�V
	updateSearchObjct();
	// �q��update�̑O�̏���
	// �����Ŏq��update���Ă΂Ȃ��ƕςɂȂ邱�Ƃ�����
	update(deltaTime);
	// �q��update���I�������̏���
	// �Փˊ֘A�̍X�V
	updateCollide();
	// �摜�̕��������킹��
	//animation_.turnAnimation(turnMotion_, direction_.x);
	animation_.changeDirType(direction_.x);
}

void BaseEnemy::onDraw() const
{
	if (!isScreen_) return;
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �A�j���[�V�����̕`��
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	animation_.draw(
		pos, Vector2::One * (body_.GetBox().getWidth() * 2) + addTexPosition_,
		0.5f, TexDegress_);
}

void BaseEnemy::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	// �v���C���[�֘A�̃I�u�W�F�N�g�ɓ������Ă���Ȃ�
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	// �������֘A�ɓ������Ă��邩
	auto getMoveFloorName = strstr(actorName.c_str(), "MoveFloor");
	// �}�b�v�̃u���b�N�ɓ���������A�������s��
	if (getFloorName != NULL) {
		// �ʒu�̕��
		groundClamp(actor);
		// �������Ă���I�u�W�F�N�g�̈ʒu���Đݒ肷��
		setObjPosition();
		// �Փ˒���true������
		isBlockCollideEnter_ = true;
		// �ߋ��̏Փ˒���false�ŁA�A�ߋ��ƌ��݂̏Փ˒����Ⴄ�Ȃ�ꍇ
		// �Փ˒���ɂȂ�
		if (!isBlockCollidePrevEnter_ &&
			isBlockCollidePrevEnter_ != isBlockCollideEnter_)
			isBlockCollideBegin_ = true;
		// �������ɐG�ꂽ��~�܂�(�ꕔ�̓G)
		if (getMoveFloorName != NULL)
			isMoveFloor_ = true;
		return;
	}

	// ���S���͍s��Ȃ�
	if (state_ == State::Dead) return;
	// �v���C���[�ɓ�����Ȃ��H
	// Player��ActorGroup���ς��̂ŁA Player_AttackRange�ɓ�����悤�ɂ���
	if ((actorName == "PlayerAttackCollider" || actorName == "BodyPoint") &&
		!isInvincible_) {
		// �_���[�W
		//circleClamp(actor);
		//// ����������������Ԃ�
		if (Vector2(actor.getPosition() - position_).Length() >= 
			actor.getBody().GetCircle().getRadius() + scale_) return;
		changeState(State::Dead, ENEMY_DAMAGE);
		// �G�t�F�N�g�̒ǉ�(�v���C���[�̃`���[�W�G�t�F�N�g)
		world_->addActor(ActorGroup::Effect,
			std::make_shared<EnemyCollideEffect>(world_, position_));
		world_->setIsStopTime(true);
		TexDegress_ = 0.0f;
		isUseGravity_ = true;
		return;
	}
}

void BaseEnemy::onMessage(EventMessage event, void *) {}

// �q���p��update(�e��update�O�ɍs���܂�)
void BaseEnemy::beginUpdate(float deltaTime) {}

// �q���p��update
void BaseEnemy::update(float deltaTime) {}

// �ҋ@��Ԃł�
void BaseEnemy::idle()
{
	// �v���C���[�Ƃ̋������v�Z���āA
	// �X�N���[���̕��̔��� + �G�̑傫����肿�������Ȃ瓮��
	auto a = enemyManager_.getPlayerLength();
	if (isScreen())
		changeState(State::Search, ENEMY_WALK);
}
// ���G�ړ��ł�(�f�t�H���g)
void BaseEnemy::search()
{
	// �v���C���[�̑{��
	findPlayer();
	turnMotion_ = ENEMY_WALKTURN;
	// �������x�ɖ߂�
	speed_ = initSpeed_;
	// �{���s��
	searchMove();
	// �v���C���[�����݂��Ȃ���΁A�{���Ƒҋ@��ԈȊO�͍s��Ȃ�
	if (!isPlayer_) return;
	// ��苗�����ŁA�v���C���[�Ƃ̊ԂɃu���b�N���Ȃ�������
	// �p�x
	auto a = enemyManager_.getPlayerNormalizeDirection();
	auto b = Vector2::Left * direction_.x;
	auto radius = std::atan2(b.y - a.y, b.x - a.x);
	auto deg = radius * 180.0f / MathHelper::Pi;
	// �ǐՂ���
	if (enemyManager_.getPlayerLength() <= discoveryLenght_ &&
		std::abs(deg) <= 30.0f &&
		psObj_->isPlayerLook()) {
		changeState(State::Discovery, ENEMY_DISCOVERY);
		// ����SE�̍Đ�
		PlaySoundMem(seHandle_, DX_PLAYTYPE_BACK);
		discoveryPosition_ = position_;
	}
}

// �v���C���[�𔭌��������̍s���ł�
void BaseEnemy::discovery()
{
	isUseGravity_ = false;
	// �W�����v���[�V����
	position_.y += (-0.5f + stateTimer_) * GRAVITY_ * deltaTimer_;
	// �W�����v��ɏ��ɐڒn������ǐՏ�ԂɑJ��
	if (isGround_ && stateTimer_ >= 0.2f) {
		changeState(State::Chase, ENEMY_ATTACK);
		turnMotion_ = ENEMY_ATTACKTURN;
		//animation_.turnAnimation(ENEMY_ATTACK);
		isUseGravity_ = true;
	}
}

// �v���C���[�̒ǐՍs���ł�(�f�t�H���g)
void BaseEnemy::chase()
{
	// �v���C���[�̑{��
	findPlayer();
	// �ړ����x��{���ɂ���
	speed_ = initSpeed_ * 1.5f;
	// �ǐՍs��
	chaseMove();
	// �摜�̕��������킹��
	/*if (direction_.x != prevDirection_.x)
	animation_.turnAnimation(turnMotion_, direction_.x);*/
	// �v���C���[���ǐՋ����O���A�v���C���[�̊ԂɃu���b�N������Ȃ�A
	// �{����ԂɑJ��
	if (enemyManager_.getPlayerLength() > discoveryLenght_ + 100.0f &&
		!psObj_->isPlayerLook()) {
		changeState(State::Search, ENEMY_WALK);
		turnMotion_ = ENEMY_WALKTURN;
	}
}

// �U���s���ł�
void BaseEnemy::attack()
{
	if (stateTimer_ >= 3.0f)
		changeState(State::Search, ENEMY_WALK);
}

// ��e�s���ł�
void BaseEnemy::damageMove()
{
	if (stateTimer_ >= 3.0f) {
		changeState(State::Chase, ENEMY_WALK);
		turnMotion_ = ENEMY_ATTACKTURN;
	}
}

// ���S�s���ł�
void BaseEnemy::deadMove()
{
	animation_.setIsLoop(false);
	name_ = "";
	if (hitTimer_ > 0.1f)
		world_->setIsStopTime(false);
	else {
		world_->setIsStopTime(true);
		// �|�[�Y���Ɏ~�߂鏈��
		if (deltaTimer_ == 0.0f && world_->isStopTime())
			hitTimer_ += world_->getDeltaTime();
		//// �|�[�Y���Ɏ~�߂鏈��
		//if (deltaTimer_ == 0.0f && !world_->isStopTime())
		//	return;
		//hitTimer_ += world_->getDeltaTime();
		//world_->setIsStopTime(true);
		return;
	}
	//world_->setIsStopTime(false);
	// �������Ă���I�u�W�F�N�g�̍폜
	for (auto i = objContainer_.begin(); i != objContainer_.end(); i++) {
		auto a = *i;
		a->dead();
	}
	if (!animation_.isEndAnimation()) return;
	// ���S�G�t�F�N�g�̒ǉ�
	world_->addActor(ActorGroup::Effect,
		std::make_shared<EnemyDeadEffect>(
			world_, position_ - Vector2::Up * 325.0f, EFFECT_DEAD));
	dead();
}

// �v���C���[�����������Ƃ��̍s���ł�
void BaseEnemy::lostMove(){}

// ��Ԃ̕ύX���s���܂�
void BaseEnemy::changeState(State state, unsigned int motion)
{
	state_ = state;
	stateTimer_ = 0.0f;
	motion_ = motion;
	// �A�j���[�V�����̕ύX
	animation_.changeAnimation(motion);
}

// �������Ă���I�u�W�F�N�g�̈ʒu��ݒ肵�܂�
void BaseEnemy::setObjPosition()
{
	if (fspScript_ == nullptr) return;
	fspScript_->setPosition(position_);
	wsScript_->setPosition(position_);
}

// �v���C���[��{�����܂�
void BaseEnemy::findPlayer()
{
	// �v���C���[�����Ȃ���Αҋ@���
	if (player_ == nullptr) {
		changeState(State::Idel, ENEMY_WALK);
		isPlayer_ = false;
		return;
	}
}

void BaseEnemy::searchMove(){}

void BaseEnemy::chaseMove(){}

// ���{���I�u�W�F�N�g�̐���
void BaseEnemy::createFSP()
{
	// �ǉ����ꂽ�ʒu��������������
	for (int i = 0; i != fspPositionContainer_.size(); ++i) {
		// �{���I�u�W�F�N�g�̒ǉ�
		auto fsObj =
			std::make_shared<FloorSearchPoint>(
				world_, position_,
				fspPositionContainer_[i],
				fspScaleContainer_[i]
				);
		world_->addActor(ActorGroup::Enemy, fsObj);
		// ���I�u�W�F�N�g�̃X�N���v�g�擾
		auto fspScript = &*fsObj;
		// �G�l�~�[�}�l�[�W���[�ɒǉ�
		enemyManager_.addFSP(fspScript);
		objContainer_.push_back(fspScript);
	}
}

void BaseEnemy::setDeltaTime(float deltatime)
{
	deltaTimer_ = deltatime * 60.0f;
}

// �G�����ݍ��܂ꂽ���̃X�P�[���|�C���g��Ԃ��܂�
float BaseEnemy::getSP()
{
	return 1.0f;
}

// �G�̑傫����Ԃ��܂�
int BaseEnemy::getScale()
{
	return (int)scale_;
}

void BaseEnemy::updateState(float deltaTime)
{
	// �v���C���[�̑{��
	player_ = world_->findActor("PlayerBody1");
	// �v���C���[���擾�ł���΁A�G�l�~�[�}�l�[�W���[�Ɉʒu������
	if (player_ != nullptr) {
		enemyManager_.setEMPosition(position_, player_->getPosition(), direction_);
		psObj_->setPosition(position_, player_->getPosition());
	}

	switch (state_)
	{
	case State::Idel: idle(); break;
	case State::Search: search(); break;
	case State::Discovery: discovery(); break;
	case State::Chase: chase(); break;
	case State::Lost: lostMove(); break;
	case State::attack: attack(); break;
	case State::Damage: damageMove(); break;
	case State::Dead: deadMove(); break;
	}

	// �X�N���[���̕��̔��� + �G�̑傫�����傫���Ȃ�ҋ@��Ԃɂ���
	if (!isScreen())
		changeState(State::Idel, ENEMY_WALK);
	prevDirection_ = direction_;
	stateTimer_ += deltaTime;
}

// �{���I�u�W�F�N�g�̍X�V
void BaseEnemy::updateSearchObjct()
{
	// �ڒn���Ă��Ȃ��Ȃ�d�͉��Z
	if (!isGround_ && isUseGravity_)
		position_.y += GRAVITY_ * deltaTimer_;
	if (fspScript_ != nullptr) {
		// �ǂɓ�������������]��(X)
		if (wsScript_->isGround())
			direction_.x *= -1.0f;
		// �{���I�u�W�F�N�g�Ƀv���C���[�̕���������
		wsScript_->setDirection(direction_);
		// �e�{���I�u�W�F�N�g�Ɉʒu������
		fspScript_->setPosition(position_);
		wsScript_->setPosition(position_);
	}
}

// �Փˊ֘A�̍X�V
void BaseEnemy::updateCollide()
{
	// bool�n��
	// �ڒn��false�ɂ���
	isGround_ = false;
	// �ŏ��ɏՓ˒���ƏՓˌ�̔����false�ɂ���
	isBlockCollideBegin_ = false;
	isBlockCollideExit_ = false;
	// �ߋ��̏Փ˒���ture�ŁA�ߋ��ƌ��݂̏Փ˒����Ⴄ�Ȃ�ꍇ
	// �Փˌ�ɂȂ�
	if (isBlockCollidePrevEnter_ &&
		isBlockCollidePrevEnter_ != isBlockCollideEnter_) {
		// �Փˌ�̔���
		isBlockCollideBegin_ = false;
		isBlockCollideExit_ = true;
	}
	// �ߋ��̏Փ˒��ɁA���݂̏Փ˒�������
	isBlockCollidePrevEnter_ = isBlockCollideEnter_;
	// �u���b�N�ɓ������Ă����true�ɂȂ�̂ŁAfalse������
	isBlockCollideEnter_ = false;
	isMoveFloor_ = false;
}

//�n�ʂ̈ʒu�ɕ␳���܂�
void BaseEnemy::groundClamp(Actor& actor)
{
	if (actor.body_.GetBox().getWidth() == 0) return;
	// �����`���m�̌v�Z
	// �������g��1f�O�̒��S�ʒu���擾
	auto pos = body_.GetBox().previousPosition_;
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
	// Y�����Ɉʒu���Ԃ���
	if (left < body_.GetBox().getWidth() / 2.0f &&
		right < body_.GetBox().getWidth() / 2.0f) {
		// ��ɕ��
		if (top > 0) {
			position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
			// �ڒn
			isGround_ = true;
		}
		// ���ɕ��
		if (bottom > 0)
			position_.y = bottomRight.y + body_.GetBox().getHeight() / 2.0f;
	}
	// X�����Ɉʒu���Ԃ���
	if (top < body_.GetBox().getHeight() / 2.0f &&
		bottom < body_.GetBox().getHeight() / 2.0f) {
		// ���ɕ��
		if (left > 0)
			position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;
		// �E�ɕ��
		if (right > 0)
			position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;
	}
}

// �~�ƏՓ˂����Ƃ��Ɉʒu�ɕ␳���܂�
void BaseEnemy::circleClamp(Actor & actor)
{
	// ���������~�Ƃ̃x�N�g�����v�Z���āA�ʒu���Ԃ��܂�
	// ���������I�u�W�F�N�g���~�łȂ��ꍇ(�Ă��Ƃ�)
	if (actor.getBody().GetCapsule().getRadius() == 0) return;
	// �ߋ��̈ʒu���擾
	auto pos = body_.GetBox().previousPosition_;
	auto direction = actor.getPosition() - pos;
	// ��`�̕��
	auto lerpVelo = Vector2(
		(actor.getBody().GetCircle().getRadius() +
			body_.GetBox().getWidth() / 2.0f) * direction.Normalize().x,
		(actor.getBody().GetCircle().getRadius() +
			body_.GetBox().getHeight() / 2.0f) * direction.Normalize().y
		);
	position_ += lerpVelo;
}

// �e�N�X�`���̒ǉ����s���܂�
void BaseEnemy::addAnimation()
{
	// �G�̉摜�ɍ��킹�Ē���
	animation_.addAnimation(
		ENEMY_WALK,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_EGGENEMY_WALK_TEX));
	animation_.addAnimation(
		ENEMY_WALKTURN,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_EGGENEMY_WALKTURN_TEX));
	animation_.addAnimation(
		ENEMY_DISCOVERY,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_EGGENEMY_DISCORVER_TEX));
	animation_.addAnimation(
		ENEMY_ATTACK,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_EGGENEMY_ATTACK_TEX));
	animation_.addAnimation(
		ENEMY_ATTACKTURN,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_EGGENEMY_ATTACKTURN_TEX));
	animation_.addAnimation(
		ENEMY_DAMAGE,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::ENEMY_EGGENEMY_DAMAGE_TEX));
}

// �v���C���[�Ƃ�X������Y�������v�Z���A��ʊO�ɂ��邩��Ԃ��܂�
bool BaseEnemy::isScreen()
{
	if (std::abs(enemyManager_.getPlayerVector().x) <= 
		(SCREEN_SIZE.x - SCREEN_SIZE.x / 12) + body_.GetBox().getWidth() &&
		std::abs(enemyManager_.getPlayerVector().y) <= 
		(SCREEN_SIZE.y - SCREEN_SIZE.x / 12) + body_.GetBox().getHeight()) {
		isScreen_ = true;
		return true;
	}
	isScreen_ = false;
	// ��ʊO
	return false;
}