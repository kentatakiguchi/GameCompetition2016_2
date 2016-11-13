#include "BaseEnemy.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"
#include "FloorSearchPoint.h"
#include "PlayerSearchObj.h"

BaseEnemy::BaseEnemy(IWorld * world, const Vector2& position, const float bodyScale) :
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
	direction_(Vector2(1.0f, 1.0f)),
	isMove_(false),
	isBlockCollideBegin_(false),
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
	enemyManager_(EnemyManager(position)),
	isTestGround_(false),
	testTop(0.0f),
	testBottom(0.0f),
	testRight(0.0f),
	testLeft(0.0f),
	test_t(0.0f)
{
	//Initialize();

	// ray�I�u�W�F�N�g�̒ǉ�
	// auto player = world_->findActor("PlayerBody1");
	auto player = world_->findActor("PlayerBody1");
	auto ray = std::make_shared<PlayerSearchObj>(
		world_, position_, player->getPosition());
	world_->addActor(ActorGroup::EnemyBullet, ray);
	psObj_ = &*ray;
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
		Vector2(-scale_ / 2.0f, 0.0f),
		Vector2(2.0f, scale_- 30.0f));
	world_->addActor(ActorGroup::Enemy, wsObj);
	wsScript = &*wsObj;
}

void BaseEnemy::onUpdate(float deltaTime)
{
	// �f���^�^�C���̒l��ݒ肷��
	setDeltaTime(deltaTime);
	// �G�l�~�[�}�l�[�W���[�̍X�V
	enemyManager_.update(deltaTime);
	// ��Ԃ̍X�V
	updateState(deltaTime);
	// �{���I�u�W�F�N�g�̍X�V
	updateSearchObjct();
	
	isGround_ = false;
	// �Փ˔�����bool��ture�Ȃ�Afalse�ɕς���
	if (!isBlockCollideExit_) return;
	isBlockCollideExit_ = false;

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
	DrawFormatString(25, 150, GetColor(255, 255, 255),
		"�u���b�N�Ƃ̈ʒu=>��:%d ��:%d", 
		(int)testTop, (int)testBottom);
	DrawFormatString(25, 200, GetColor(255, 255, 255),
		"�u���b�N�Ƃ̈ʒu=>�E:%d ��:%d",
		(int)testRight, (int)testLeft);
	DrawFormatString(25, 250, GetColor(255, 255, 255),
		"�u���b�N�Ƃ�t:%d",
		(int)test_t);

	//char lengthChar = static_cast<char>(enemyManager_.getPlayerLength());
	//DrawString(position_.x + 50, position_.y - 20, &lengthChar, GetColor(255, 255, 255));
	body_.draw(inv_);
}

void BaseEnemy::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	// �v���C���[�֘A�̃I�u�W�F�N�g�ɓ������Ă���Ȃ�
	// actorName != "Player_AttackRange"
	// if (actorName != "Player") return;

	// �������Ȃ�,bool���Փˌ�̂��̂ɂ���
	if (actorName == "") {
		isBlockCollideExit_ = true;
		isBlockCollideEnter_ = false;
		body_.enabled(false);
		return;
	}
	// �}�b�v�̃u���b�N�ɓ���������A�������s��
	if (actorName == "MovelessFloor") {
		// Enter��false�Ȃ�Abegin��true�ɂ���
		// �t�Ȃ�΁Abegin��false�ɕς���
		if(!isBlockCollideEnter_)
			isBlockCollideBegin_ = true;
		else isBlockCollideBegin_ = false;
		isBlockCollideEnter_ = true;
		body_.enabled(false);
		return;

		//// ���葤�̓����蔻�肪�l�p�`�ȊO�Ȃ�s��Ȃ�(�Ă��Ƃ�����)
		//if (actor.body_.GetBox().getWidth() == 0) return;
		// �����`���m�̌v�Z
		// �������g��1f�O�̈ʒu���擾
		auto pos = body_.GetBox().previousPosition_;
		// ���葤�̎l�p�`��4�_���擾
		auto topLeft = actor.getBody().GetBox().component_.point[0];
		auto topRight = actor.getBody().GetBox().component_.point[1];
		auto bottomLeft = actor.getBody().GetBox().component_.point[2];
		auto bottomRight = actor.getBody().GetBox().component_.point[3];
		// �e�ӂɑ΂���ʒu�̊O�ς��v�Z����
		// �c�����̃x�N�g��(H)�����߂�
		auto top = Vector2::Cross(
			(topLeft - topRight).Normalize(), (pos - topRight));
		auto bottom = Vector2::Cross(
			(bottomRight - bottomLeft).Normalize(), (pos - bottomLeft));
		auto right = Vector2::Cross(
			(topRight - bottomRight).Normalize(), (pos - bottomRight));
		auto left = Vector2::Cross(
			(bottomLeft - topLeft).Normalize(), (pos - topLeft));

		testTop = top * 100;
		testBottom = bottom * 100;
		testRight = right * 100;
		testLeft = left * 100;
		// Y����ŏՓ˂����ꍇ
		//if (left <= 0 && right <= 0) {
		//	// top > 0 �Ȃ��ɕ�� bottom > 0 �Ȃ牺�ɕ�Ԃ���
		//	if (top > 0)
		//		position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
		//	if (bottom > 0)
		//		position_.y = bottomRight.y + body_.GetBox().getHeight() / 2.0f;
		//}	// X����ŏՓ˂����ꍇ
		//if (top <= 0 && bottom <= 0) {
		//	// left > 0 �Ȃ�E�ɕ�� right > 0 �Ȃ獶�ɕ�Ԃ���
		//	if (left > 0)
		//		position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;
		//	if (right > 0)
		//		position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;
		//}

		// ���S��������ɉ������_��p1�܂ł̋�����
		/*Vector2 other_v = actor.body_.GetBox().component_.point[3] - 
			actor.body_.GetBox().component_.point[2];
		Vector2 left_v1 = body_.GetBox().component_.point[2] -
			actor.body_.GetBox().component_.point[2];
		float left_t = Vector2::Dot(other_v, left_v1) /
			Vector2::Dot(other_v, other_v);*/

		// 
		//Vector2 right_v1 = body_.GetBox().component_.point[3] -
		//	actor.body_.GetBox().component_.point[2];
		//// ���S��������ɉ������_��p1�܂ł̋�����
		//float right_t = Vector2::Dot(other_v, right_v1) /
		//	Vector2::Dot(other_v, other_v);

		//if (left <= 0 && right <= 0) {
		//	// top > 0 �Ȃ��ɕ�� bottom > 0 �Ȃ牺�ɕ�Ԃ���
		//	
		//}

		/*if (top > 0)
			position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
		else
			position_.y = bottomRight.y + body_.GetBox().getHeight() / 2.0f;*/
		// ���������u���b�N�̑傫��
		// top < actor.body_.GetBox().getWidth

		// ��ɕ��
		//if (top > 0 && 
		//	(-body_.GetBox().getWidth() < right && 
		//	-body_.GetBox().getWidth() < left))
		//	position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
		//// �E�ɕ��
		//if (right >= actor.body_.GetBox().getWidth() &&
		//	top < actor.body_.GetBox().getHeight())
		//	position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;
		//// ���ɕ��
		//if (left >= actor.body_.GetBox().getWidth() &&
		//	top < actor.body_.GetBox().getHeight())
		//	position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;

		// ��
		//if (top >= 32 && left > -64) {
		//	/*if(left >= -body_.GetBox().getWidth() && 
		//		right >= -body_.GetBox().getWidth())
		//		position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;*/
		//	position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
		//}
		//if (right >= 0) {
		//	if (top < 32) {
		//		if(bottom < 0)
		//		position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;
		//	}
		//	else {
		//		if (bottom > -64 && bottom < -63)
		//		position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;
		//	}
		//		
		//}
		//if (left >= 0) {
		//	if(top < 32)
		//		position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;
		//}

		//else {
		//	// ���ɕ��
		//	/*if (left >= -64)
		//		position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;*/
		//	// �E�ɕ��
		//	// top == 32 �ŏՓ˂��Ȃ�
		//	/*if (right >= 0)
		//		position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;*/
		//}

		// �E�ɕ�Ԃ���
		/*if (left_t > 0 && right >= 0)
			position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;*/

		// ��ɕ��
		//if (top > 0)
		//	position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
		//// ���ɕ��
		//if (left_t >= 0 && left >= 0)
		//	position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;

		//test_t = right_t * 100;

		/*Vector2 otherCenter = actor.body_.GetBox().position_;
		Vector2 thisCenter = body_.GetBox().position_;*/

		//Vector2 otherCenter = actor.body_.GetBox().component_.point[3] / 2.0f;
		//Vector2 thisCenter = body_.GetBox().component_.point[3] / 2.0f;
		//// ����
		//Vector2 dir = thisCenter - otherCenter;

		//if (std::abs(dir.x) >std::abs(dir.y))
		//{
		//	if (dir.x > 0)
		//	{
		//		position_.x = actor.position_.x + body_.GetBox().getWidth();
		//		//position.X = gameObj.getRectangle().Right;
		//	}
		//	else
		//	{
		//		position_.x = actor.position_.x - body_.GetBox().getWidth() / 2.0f;
		//		//position.X = gameObj.getRectangle().Left - this.width;
		//	}
		//}
		//else
		//{
		//	if (dir.y > 0)
		//	{
		//		position_.y = actor.position_.y + body_.GetBox().getHeight();
		//		//position.Y = gameObj.getRectangle().Bottom;
		//	}
		//	else
		//	{
		//		position_.y = actor.position_.y - body_.GetBox().getHeight() / 2.0f;
		//		//position.Y = gameObj.getRectangle().Top - this.hight;
		//	}
		//}
		

		isTestGround_ = true;

		body_.enabled(false);
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
		body_.enabled(false);
		return;
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
	stateString_ = "�ҋ@";
	// if (enemyManager_.getPlayerLength() < 100) changeState(State::Search, ENEMY_WALK);
	changeState(State::Search, ENEMY_WALK);
}
// ���G�ړ��ł�(�f�t�H���g)
void BaseEnemy::search()
{
	// �v���C���[�̑{��
	findPlayer();
	stateString_ = "�{��";
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
	// �v���C���[�̑{��
	//findPlayer();
	stateString_ = "����";
	// �W�����v���[�V����
	position_.y += (-0.5f + stateTimer_) * GRAVITY_ * deltaTimer_;
	// �ʒu��␳
	groundClamp();
	// �␳���ꂽ��A�ǐՂɈڍs
	if (position_.y >= fspScript->getFloorPosition().y) {
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
	speed_ = initSpeed_ * 1.5f;
	// �ǐՍs��
	chaseMove();
	if (enemyManager_.getPlayerLength() > discoveryLenght_ + 30.0f)
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
	//dead();
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

	stateTimer_ += deltaTime;
}

// �{���I�u�W�F�N�g�̍X�V
void BaseEnemy::updateSearchObjct()
{
	// �ڒn���Ă��Ȃ��Ȃ�d�͉��Z
	if (!fspScript->isGround() && isUseGravity_)
	// if (!isTestGround_)
		position_.y += GRAVITY_ * deltaTimer_;
	// ���̈ʒu�ɕ␳����
	if (fspScript->isGround())
		groundClamp();
	// �ǂɓ�������������]��(X)
	if (wsScript->isGround())
		direction_.x *= -1.0f;
	// �{���I�u�W�F�N�g�Ƀv���C���[�̕���������
	wsScript->setDirection(direction_);
	// �e�{���I�u�W�F�N�g�Ɉʒu������
	fspScript->setPosition(position_);
	wsScript->setPosition(position_);
}

//�n�ʂ̈ʒu�ɕ␳���܂�
void BaseEnemy::groundClamp()
{
	position_.y = MathHelper::Clamp(position_.y,
		fspScript->getFloorPosition().y - 100.0f,
		fspScript->getFloorPosition().y);
}
