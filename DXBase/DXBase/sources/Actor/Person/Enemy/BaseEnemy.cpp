#include "BaseEnemy.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"
#include "Enemy_AttackRange.h"
#include "FloorSearchPoint.h"


BaseEnemy::BaseEnemy(IWorld * world, const Vector3& position, const float bodyScale) :
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
	directionX_(1.0f),
	directionY_(1.0f),
	isGround_(false),
	isUseGravity_(true),
	isInvincible_(false),
	discoveryLenght_(125),
	color_(GetColor(255, 255, 255)),
	stateTimer_(0.0f),
	state_(State::Idel),
	stateString_(""),
	discoveryPosition_(Vector3(0.0f, 0.0f, 0.0f)),
	animation_(),
	player_(nullptr),
	fsPointScript(nullptr),
	wsScript(nullptr),
	enemyManager_(EnemyManager(position))
{
	// ���{���I�u�W�F�N�g�̒ǉ�
	auto fsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector3(0.0f, 0.0f + scale_ / 2.0f, 0.0f), position_);
	// ���[���h�ɒǉ�
	world_->addActor(ActorGroup::Enemy, fsObj);
	fsPointScript = &*fsObj;
	// �Ǒ{���I�u�W�F�N�g
	auto wsObj = std::make_shared<FloorSearchPoint>(
		world_, Vector3(-scale_ / 2.0f, 0.0f, 0.0f), position_);
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsScript = &*wsObj;
	// fspContainer_[i]->setEnemyScale(Vector2(scale_, scale_));
	// fspContainer_[i]->setPosition(position_ + fspPositionContainer_[i]);

	// fsPointScript
}

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::onUpdate(float deltaTime)
{
	deltaTimer_ = deltaTime;
	// �G�l�~�[�}�l�[�W���[�̍X�V
	enemyManager_.update(deltaTime);
	// ��Ԃ̍X�V
	updateState(deltaTime);
	// �ڒn���Ă��Ȃ��Ȃ�d�͉��Z
	if (!fsPointScript->isGround() && isUseGravity_) {
		position_.y += GRAVITY_;
	}
	// �ǂɓ�������������]��(X)
	if (wsScript->isGround()) {
		directionX_ *= -1.0f;
	}
	wsScript->setDirectionX(directionX_);
	/*if (!isGround_)
		position_.y += GRAVITY_;*/

	fsPointScript->setPosition(position_);
	wsScript->setPosition(position_);
	// �f�o�b�O
	distance_ = enemyManager_.getPlayerLength();
	isGround_ = false;

	// �A�j���[�V�����̕ύX
	//animation_.change(motion_);
	// �A�j���[�V�����̍X�V
	//animation_.update(deltaTime);

	//auto position = Vector2(position_.x, position_.y);
	//body_.setPosition(position);
}

void BaseEnemy::onDraw() const
{
	auto stateChar = stateString_.c_str();
	DrawGraph(
		position_.x - scale_ / 2.0f, position_.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);
	DrawString(
		position_.x - scale_, position_.y - 20 - scale_,
		stateChar, GetColor(255, 255, 255));

	// �f�o�b�O
	/*DrawFormatString(25, 25, GetColor(255, 255, 255), "body x:%d,y:%d", (int)body_.GetBox().component_.point[0].x, (int)body_.GetBox().component_.point[0].y);
	DrawFormatString(25, 50, GetColor(255, 255, 255), "pos  x:%d,y:%d", (int)position_.x, (int)position_.y);
	DrawFormatString(25, 75, GetColor(255, 255, 255), "�v���C���[�Ƃ̋���:%d", (int)distance_);*/

	//char lengthChar = static_cast<char>(enemyManager_.getPlayerLength());
	//DrawString(position_.x + 50, position_.y - 20, &lengthChar, GetColor(255, 255, 255));
	body_.draw();
}

void BaseEnemy::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	// �ڒn���Ă���Ȃ�
	/*if (actorName == "MapChip") {
		isGround_ = true;
		if (actor.position_.y < position_.y)
			position_.y = MathHelper::Clamp(
				position_.y, actor.position_.y, actor.position_.y + 1.0f);
		return;
	}*/
	// �v���C���[�֘A�̃I�u�W�F�N�g�ɓ������Ă���Ȃ�
	// actorName != "Player_AttackRange"
	// if (actorName != "Player") return;

	// �v���C���[�ɓ�����Ȃ��H
	if (actorName == "PlayerBody2" && !isInvincible_) {
		// �_���[�W
		/*hp_ -= 10;
		if (hp_ <= 0) changeState(State::Dead, ENEMY_DEAD);
		else changeState(State::Damage, ENEMY_DAMAGE);*/
		changeState(State::Dead, ENEMY_DEAD);
		isUseGravity_ = true;
		body_.enabled(false);
	}
	//// �_���[�W
	//// hp_ -= player->GetAP(); �Ƃ�
	//hp_ -= 10;
	//if (hp_ <= 0) changeState(State::Dead, ENEMY_DEAD);
	//else changeState(State::Damage, ENEMY_DAMAGE);
	//body_.enabled(false);
}

void BaseEnemy::onMessage(EventMessage event, void *)
{
}

// �ҋ@��Ԃł�
void BaseEnemy::idle()
{
	color_ = GetColor(255, 255, 255);
	stateString_ = "�ҋ@";
	//position_ += BaseEnemy::getPlayerNormalizeDirection() * -speed_;
	// if (enemyManager_.getPlayerLength() < 100) changeState(State::Search, ENEMY_WALK);
	changeState(State::Search, ENEMY_WALK);
}
// ���G�ړ��ł�(�f�t�H���g)
void BaseEnemy::search()
{
	// �v���C���[�̑{��
	findPlayer();
	color_ = GetColor(0, 255, 0);
	stateString_ = "�{��";
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
	// �v���C���[�̑{��
	/*if (!fsPointScript->isGround()) {
		discoveryPosition_ = position_;
		return;
	}*/
	//findPlayer();
	stateString_ = "����";
	//isUseGravity_ = false;
	//position_.y += -4.0f + stateTimer_ * GRAVITY_;
	position_.y += (-0.5f + stateTimer_) * GRAVITY_;
	position_.y = MathHelper::Clamp(
		position_.y, discoveryPosition_.y - 100.0f, discoveryPosition_.y);
	if (position_.y == discoveryPosition_.y) {
		changeState(State::Chase, ENEMY_WALK);
		isUseGravity_ = true;
	}
}

// �v���C���[�̒ǐՍs���ł�(�f�t�H���g)
void BaseEnemy::chase()
{
	// �v���C���[�̑{��
	findPlayer();
	color_ = GetColor(255, 0, 0);
	stateString_ = "�ǐ�";
	// �ǐՍs��
	chaseMove();
	if (enemyManager_.getPlayerLength() > discoveryLenght_)
		changeState(State::Search, ENEMY_WALK);
	// �O���Ɉړ�(��)
	//auto distance = position_ - player_->getPosition();
	////auto direction = 1.0f;
	//if (distance.x < 0)
	//	directionX_ = -1;
	//else if(distance.x > 0) directionX_ = 1;
	//else directionX_ = 0;

	//// ���������Ɉړ�
	//position_ += position_.Left * -speed_ * getPlayerDirection().x;
	//// �ړ�
	//position_ += BaseEnemy::getPlayerNormalizeDirection() * -speed_;
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
void BaseEnemy::Attack()
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
	color_ = GetColor(255, 255, 0);
	stateString_ = "�_���[�W";
	if (stateTimer_ >= 3.0f)
		changeState(State::Chase, ENEMY_WALK);
}

// ���S�s���ł�
void BaseEnemy::deadMove()
{
	//if (stateTimer_ >= 3.0f) dead();
	stateString_ = "���S";
	color_ = GetColor(10, 10, 10);
	//dead();
}

// ��Ԃ̕ύX���s���܂�
void BaseEnemy::changeState(State state, unsigned int motion)
{
	state_ = state;
	stateTimer_ = 0.0f;
	motion_ = motion;
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
		auto fsObj = std::make_shared<FloorSearchPoint>(world_, Vector3::Zero, position_);
		//fsPoint_ = std::make_shared<FloorSearchPoint>(world_, position_);
		world_->addActor(ActorGroup::Effect, fsObj);
		// ���I�u�W�F�N�g�̃X�N���v�g�擾
		auto fspScript = &*fsObj;
		//fsPointScript->setEnemyScale(Vector2(scale_, scale_));
		// �ǉ�
		fspContainer_.push_back(fspScript);
		fspContainer_[i]->setEnemyScale(Vector2(scale_, scale_));
		fspContainer_[i]->setPosition(position_ + fspPositionContainer_[i]);
		// �G�l�~�[�}�l�[�W���[
		enemyManager_.addFSP(fspScript);
	}
}

// �G�����ݍ��܂ꂽ���̃X�P�[���|�C���g��Ԃ��܂�
float BaseEnemy::getSP()
{
	return 1.0f;
}

// �G�̑傫����Ԃ��܂�
int BaseEnemy::getScale()
{
	return 1;
}

void BaseEnemy::updateState(float deltaTime)
{
	// �v���C���[�̑{��
	player_ = world_->findActor("Player");
	// �v���C���[���擾�ł���΁A�G�l�~�[�}�l�[�W���[�Ɉʒu������
	if (player_ != nullptr)
		enemyManager_.setEMPosition(position_, player_->getPosition());
	switch (state_)
	{
	case State::Idel: idle(); break;
	case State::Search: search(); break;
	case State::Discovery: discovery(); break;
	case State::Chase: chase(); break;
	case State::Attack: Attack(); break;
		// State::Return: ; break;
	case State::Damage: damageMove(); break;
	case State::Dead: deadMove(); break;
	}

	stateTimer_ += deltaTime;
}
