#include "BaseEnemy.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"
#include "FloorSearchPoint.h"
#include "PlayerSearchObj.h"

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
	speed_(1.0f),
	initSpeed_(speed_),
	scale_(bodyScale),
	direction_(direction),
	isMove_(false),
	isBlockCollideBegin_(false),
	isBlockCollideEnter_(false),
	isBlockCollidePrevEnter_(false),
	isBlockCollideExit_(false),
	isGround_(false),
	isUseGravity_(true),
	isInvincible_(false),
	discoveryLenght_(125),
	stateTimer_(0.0f),
	state_(State::Idel),
	stateString_(""),
	discoveryPosition_(Vector2::Zero),
	animation_(),
	player_(nullptr),
	psObj_(nullptr),
	fspScript(nullptr),
	wsScript(nullptr),
	pricleObj_(nullptr),
	enemyManager_(EnemyManager(position, direction)),
	handle_(0)
{
	//Initialize();

	// ray�I�u�W�F�N�g�̒ǉ�
	// auto player = world_->findActor("PlayerBody1");
	auto player = world_->findActor("PlayerBody1");
	auto ray = std::make_shared<PlayerSearchObj>(
		world_, position_, player->getPosition());
	world_->addActor(ActorGroup::EnemyBullet, ray);
	psObj_ = &*ray;

	handle_ = CreateFontToHandle("�l�r ����", 40, 10, DX_FONTTYPE_NORMAL);
}

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::Initialize()
{
	// ���{���I�u�W�F�N�g�̒ǉ�
	/*auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector2(0.0f, 0.0f + scale_ / 2.0f), position_);*/
	auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, 0.0f + scale_ / 2.0f),
		Vector2(scale_, 2.0f));
	// ���[���h�ɒǉ�
	world_->addActor(ActorGroup::Enemy, fsObj);
	fspScript = &*fsObj;
	fspScript->setPosition(position_);
	// �Ǒ{���I�u�W�F�N�g
	/*auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector2(-scale_ / 2.0f, 0.0f), position_);*/
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, position_, 
		Vector2(scale_ / 2.0f, 0.0f),
		Vector2(2.0f, scale_- 30.0f));
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsScript = &*wsObj;
}

void BaseEnemy::onUpdate(float deltaTime)
{
	// �q���p��update(�e��update�O�ɍs���܂�)
	beginUpdate(deltaTime);
	// �f���^�^�C���̒l��ݒ肷��
	setDeltaTime(deltaTime);
	// �G�l�~�[�}�l�[�W���[�̍X�V
	enemyManager_.update(deltaTime);
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

	// �A�j���[�V�����̕ύX
	//animation_.change(motion_);
	// �A�j���[�V�����̍X�V
	//animation_.update(deltaTime);
}

void BaseEnemy::onDraw() const
{
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �G�̕\��
	DrawGraph(
		vec3Pos.x - scale_ / 2.0f, vec3Pos.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);
	// �����̕\��
	DrawString(
		vec3Pos.x - scale_, vec3Pos.y - 20 - scale_,
		stateChar, GetColor(255, 255, 255));

	// �f�o�b�O
	/*DrawFormatString(25, 25, GetColor(255, 255, 255), "body x:%d,y:%d", (int)body_.GetBox().component_.point[0].x, (int)body_.GetBox().component_.point[0].y);
	DrawFormatString(25, 50, GetColor(255, 255, 255), "pos  x:%d,y:%d", (int)position_.x, (int)position_.y);
	DrawFormatString(25, 75, GetColor(255, 255, 255), "�v���C���[�Ƃ̋���:%d", (int)distance_);*/

	/*DrawFormatStringToHandle(50, 50, GetColor(255, 255, 255),
		handle_, "�u���b�N�Ƃ̈ʒu=>��:%d ��:%d", (int)testTop, (int)testBottom);
	DrawFormatStringToHandle(50, 100, GetColor(255, 255, 255),
		handle_, "�u���b�N�Ƃ̈ʒu=>�E:%d ��:%d", (int)testRight, (int)testLeft);
	DrawFormatStringToHandle(50, 150, GetColor(255, 255, 255),
		handle_, "�������Ă���u���b�N�̐�:%d", collideCount_);*/
	/*DrawFormatStringToHandle(50, 150, GetColor(255, 255, 255),
		handle_, "�ڒn���Ă��邩:%d", (int)isGround_);*/
	/*DrawFormatString(25, 200, GetColor(255, 255, 255),
		"�u���b�N�Ƃ̈ʒu=>�E:%d ��:%d",
		(int)testRight, (int)testLeft);*/
	/*DrawFormatString(25, 250, GetColor(255, 255, 255),
		"�u���b�N�Ƃ�t:%d",
		(int)test_t);*/

	//char lengthChar = static_cast<char>(enemyManager_.getPlayerLength());
	//DrawString(position_.x + 50, position_.y - 20, &lengthChar, GetColor(255, 255, 255));
	body_.draw(inv_);
}

void BaseEnemy::onCollide(Actor & actor)
{
	name_ = actor.getName();
	auto actorName = actor.getName();
	// �v���C���[�֘A�̃I�u�W�F�N�g�ɓ������Ă���Ȃ�
	// actorName != "Player_AttackRange"
	// if (actorName != "Player") return;

	// �}�b�v�̃u���b�N�ɓ���������A�������s��
	if (actorName == "MovelessFloor") {
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
		// ��������݂̂ɂ���̂ŏ���
		//body_.enabled(false);
		return;
	}

	// �v���C���[�ɓ�����Ȃ��H
	if ((actorName == "PlayerBody2" || actorName == "PlayerBody1") &&
		!isInvincible_) {
		// �_���[�W
		/*hp_ -= 10;
		if (hp_ <= 0) changeState(State::Dead, ENEMY_DEAD);
		else changeState(State::Damage, ENEMY_DAMAGE);*/
		changeState(State::Dead, ENEMY_DEAD);
		isUseGravity_ = true;
		return;
		/*body_.enabled(false);
		return;*/
	}
}

void BaseEnemy::onMessage(EventMessage event, void *)
{
}

// �q���p��update(�e��update�O�ɍs���܂�)
void BaseEnemy::beginUpdate(float deltaTime){}

// �q���p��update
void BaseEnemy::update(float deltaTime){}

// �ҋ@��Ԃł�
void BaseEnemy::idle()
{
	stateString_ = "�ҋ@";
	// �v���C���[�Ƃ̋������v�Z���āA
	// �X�N���[���̕��̔��� + �G�̑傫����肿�������Ȃ瓮��
	if (enemyManager_.getPlayerLength() < 
		SCREEN_SIZE.x / 2.0f + body_.GetBox().getHeight())
		changeState(State::Search, ENEMY_WALK);
}
// ���G�ړ��ł�(�f�t�H���g)
void BaseEnemy::search()
{
	// �v���C���[�̑{��
	findPlayer();
	stateString_ = "�{��";
	// �������x�ɖ߂�
	speed_ = initSpeed_;
	// �{���s��
	searchMove();
	// ��苗�����Ȃ�ǐՂ���
	if (enemyManager_.getPlayerLength() <= discoveryLenght_) {
		changeState(State::Discovery, ENEMY_DISCOVERY);
		discoveryPosition_ = position_;
	}
	//else if(enemyManager_.getPlayerLength() >= 100) changeState(State::Idel, ENEMY_IDLE);
}

// �v���C���[�𔭌��������̍s���ł�
void BaseEnemy::discovery()
{
	isUseGravity_ = false;
	stateString_ = "����";
	// �W�����v���[�V����
	position_.y += (-0.5f + stateTimer_) * GRAVITY_ * deltaTimer_;
	// �W�����v��ɏ��ɐڒn������ǐՏ�ԂɑJ��
	if (isGround_ && stateTimer_ >= 0.2f) {
		changeState(State::Chase, ENEMY_WALK);
		isUseGravity_ = true;
	}
}

// �v���C���[�̒ǐՍs���ł�(�f�t�H���g)
void BaseEnemy::chase()
{
	// �v���C���[�̑{��
	findPlayer();
	stateString_ = "�ǐ�";
	// �ړ����x��{���ɂ���
	speed_ = initSpeed_ * 1.5f;
	// �ǐՍs��
	chaseMove();
	if (enemyManager_.getPlayerLength() > discoveryLenght_ + 30.0f)
		changeState(State::Search, ENEMY_WALK);
}

//void BaseEnemy::shortDistanceAttack()
//{
//}
//
//void BaseEnemy::centerDistanceAttack()
//{
//}
//
//void BaseEnemy::longDistanceAttack()
//{
//}

// �U���s���ł�
void BaseEnemy::attack()
{
	/*world_->addActor(
		ActorGroup::Enemy_AttackRange, std::make_shared<Enemy_AttackRange>(world_, position_));*/
	stateString_ = "�U��";
	if (stateTimer_ >= 3.0f)
		changeState(State::Search, ENEMY_IDLE);
}

// ��e�s���ł�
void BaseEnemy::damageMove()
{
	stateString_ = "�_���[�W";
	if (stateTimer_ >= 3.0f)
		changeState(State::Chase, ENEMY_WALK);
}

// ���S�s���ł�
void BaseEnemy::deadMove()
{
	//if (stateTimer_ >= 3.0f) dead();
	stateString_ = "���S";
	dead();
}

// �v���C���[�����������Ƃ��̍s���ł�
void BaseEnemy::lostMove()
{
}

// ��Ԃ̕ύX���s���܂�
void BaseEnemy::changeState(State state, unsigned int motion)
{
	state_ = state;
	stateTimer_ = 0.0f;
	motion_ = motion;
}

// �������Ă���I�u�W�F�N�g�̈ʒu��ݒ肵�܂�
void BaseEnemy::setObjPosition()
{
	if (fspScript == nullptr) return;
	fspScript->setPosition(position_);
	wsScript->setPosition(position_);
}

// �v���C���[��{�����܂�
void BaseEnemy::findPlayer()
{
	// �v���C���[�����Ȃ���Αҋ@���
	if (player_ == nullptr) {
		changeState(State::Idel, ENEMY_IDLE);
		return;
	}
}

void BaseEnemy::searchMove()
{
}

void BaseEnemy::chaseMove()
{
}

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
		//fspScript->setEnemyScale(Vector2(scale_, scale_));
		// �ǉ�
		/*wspContainer_.push_back(fspScript);
		wspContainer_[i]->setEnemyScale(Vector2(scale_, scale_));
		wspContainer_[i]->setPosition(position_ + fspPositionContainer_[i]);*/
		// �G�l�~�[�}�l�[�W���[�ɒǉ�
		enemyManager_.addFSP(fspScript);
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
	// player_ = world_->findActor("Player");
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
		// State::Return: ; break;
	case State::Damage: damageMove(); break;
	case State::Dead: deadMove(); break;
	}

	// �X�N���[���̕��̔��� + �G�̑傫�����傫���Ȃ�ҋ@��Ԃɂ���
	if (enemyManager_.getPlayerLength() >=
		SCREEN_SIZE.x / 2.0f + body_.GetBox().getHeight())
		changeState(State::Idel, ENEMY_IDLE);

	stateTimer_ += deltaTime;
}

// �{���I�u�W�F�N�g�̍X�V
void BaseEnemy::updateSearchObjct()
{
	// �ڒn���Ă��Ȃ��Ȃ�d�͉��Z
	//if (!fspScript->isGround() && isUseGravity_)
	if (!isGround_ && isUseGravity_)
		position_.y += GRAVITY_ * deltaTimer_;
	if (fspScript != nullptr) {
		// �ǂɓ�������������]��(X)
		if (wsScript->isGround())
			direction_.x *= -1.0f;
		// �{���I�u�W�F�N�g�Ƀv���C���[�̕���������
		wsScript->setDirection(direction_);
		// �e�{���I�u�W�F�N�g�Ɉʒu������
		fspScript->setPosition(position_);
		wsScript->setPosition(position_);
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
