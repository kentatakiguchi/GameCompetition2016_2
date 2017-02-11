#include "MiniBoss.h"
#include "../../../Base/ActorGroup.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../FloorSearchPoint.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"
#include <random>

MiniBoss::MiniBoss(
	IWorld * world, 
	const Vector2 & position, 
	const float scale) : 
	Actor(world, "MiniRunBoss", position,
		CollisionBase(const_cast<Vector2&>(position), 64.0f * scale)),
	stateTimer_(0.0f),
	speed_(6.0f),
	scale_(scale),
	bossPositionRX_(0.0f),
	isConfusion_(true),
	isBossPosition_(false),
	isLift_(false),
	direction_(Vector2::One * -1),
	state_(State::Confusion),
	animation_(EnemyAnimation2D()),
	fspObj_(nullptr)
{
	// ������ς���
	auto size = (int)(scale * 100);
	if (size % 2 == 1) direction_.x = 1;
	// �A�j���[�V�����̒ǉ�
	animation_.addAnimation(MINI_BOSS_RUN,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WALLATTACK_DASH_TEX));
	animation_.addAnimation(MINI_BOSS_LIFT,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_DAMAGE_TEX));
	animation_.changeAnimation(MINI_BOSS_RUN);
	animation_.changeDirType(direction_.x);
	// ���{���I�u�W�F�N�g
	auto fspObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(body_.GetCircle().getRadius(), body_.GetCircle().getRadius()), 
		10.0f);
	world_->addActor(ActorGroup::EnemyBullet, fspObj);
	fspObj_ = fspObj.get();
	fspObj_->setDirection(direction_);
}

void MiniBoss::onUpdate(float deltaTime)
{
	// ��Ԃ̍X�V
	updateState(deltaTime);
	animation_.update(deltaTime);
}

void MiniBoss::onDraw() const
{
	auto size = 256;
	animation_.draw(
		position_, 
		Vector2(size / 2.0f, size / 1.5f),
		scale_);
}

void MiniBoss::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	//���֘A�̃I�u�W�F�N�g�ɓ������Ă���Ȃ�
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	if (actorName == "Door") {
		// �h�A����
		if (state_ == State::RunAway) {
			actor.dead();
			auto se =
				ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_CHAKUCHI);
			if (CheckSoundMem(se) == 0)
				PlaySoundMem(se, DX_PLAYTYPE_BACK);
			return;
		}
		else if (state_ == State::Approach) {
			// �ړI�̈ʒu�ɂ��ǂ蒅���Ȃ��ꍇ�́A���B�������Ƃɂ���B
			groundClamp(actor);
			/*if (std::abs(position_.x - bossPositionRX_) < 100.0f) {
				isBossPosition_ = true;
				animation_.setIsLoop(false);
				animation_.stopAnime();
			}*/
			return;
		}
	}
	// �}�b�v�̃u���b�N�ɓ���������A�������s��
	if (getFloorName != NULL || actorName == "Door") {
		// �ʒu�̕��
		groundClamp(actor);
		return;
	}
}

void MiniBoss::onMessage(EventMessage event, void *)
{
}

// ��Ԃ̍X�V
void MiniBoss::updateState(float deltaTime)
{
	// ��Ԃ̍X�V
	switch (state_)
	{
	case State::Confusion: Confusion(deltaTime); break;
	case State::CalmDown: CalmDown(deltaTime); break;
	case State::Approach: Approach(deltaTime); break;
	case State::Lift: Lift(deltaTime); break;
	case State::RunAway: RunAway(deltaTime); break;
	}

	stateTimer_ += deltaTime;
}

// ��Ԃ̕ύX���s���܂�
void MiniBoss::changeState(State state, int num)
{
	if (state_ == state) return;
	stateTimer_ = 0.0f;
	state_ = state;
	animation_.changeAnimation(num);
	animation_.setIsLoop(true);
}

// �������
void MiniBoss::Confusion(float deltaTime)
{
	position_.y += 9.8f * (deltaTime * 60.0f);
	position_.x += direction_.x * speed_ * (deltaTime * 60.0f);
	fspObj_->setPosition(position_);
	// ������ς���
	if (fspObj_->isGround()) {
		direction_.x *= -1;
		animation_.changeDirType(direction_.x);
	}
	fspObj_->setDirection(direction_);

	// ������ԂłȂ���΁A����������ԂɑJ��
	if (!isConfusion_) {
		//changeState(State::CalmDown, MINI_BOSS_RUN);
		auto boss = world_->findActor("DeadBoss");
		if (boss == nullptr) {
			changeState(State::Approach, MINI_BOSS_RUN);
			return;
		}
		auto posX = (int)boss->position().x;
		// �����̎擾
		std::random_device random;
		// �����Z���k�c�C�X�^�[�@ ��Œ��ׂ�
		// ����Seed�l��n��
		std::mt19937 mt(random());
		// �͈͂̎w��(int�^)
		std::uniform_int_distribution<> bpos(-100, 100);
		bossPositionRX_ = (float)(posX + bpos(mt));
		changeState(State::Approach, MINI_BOSS_RUN);
	}
}

// �����������
void MiniBoss::CalmDown(float deltaTime)
{
	animation_.setIsLoop(false);
	if (stateTimer_ >= 2.0f) {
		auto boss = world_->findActor("DeadBoss");
		if (boss == nullptr) {
			changeState(State::Approach, MINI_BOSS_RUN);
			return;
		}
		auto posX = (int)boss->position().x;
		// �����̎擾
		std::random_device random;
		// �����Z���k�c�C�X�^�[�@ ��Œ��ׂ�
		// ����Seed�l��n��
		std::mt19937 mt(random());
		// �͈͂̎w��(int�^)
		std::uniform_int_distribution<> bpos(-100, 100);
		bossPositionRX_ = (float)(posX + bpos(mt));
		changeState(State::Approach, MINI_BOSS_RUN);
	}
}

// �{�X�ɋ߂Â����
void MiniBoss::Approach(float deltaTime)
{
	if (isBossPosition_) return;
	//auto boss = world_->findActor("DeadBoss");
	//if (boss == nullptr) return;
	auto distance = position_.x - bossPositionRX_;
	// �ړ�
	if (distance < 0) direction_.x = 1.0f;
	else direction_.x = -1.0f;
	animation_.changeDirType(direction_.x);
	//auto speed = speed_;
	//if (distance < speed) speed = std::abs(distance);
	position_.x += direction_.x * speed_ * (deltaTime * 60.0f);
	if (std::abs(distance) < speed_) {
		isBossPosition_ = true;
		animation_.setIsLoop(false);
		animation_.stopAnime();
	}
}

// �{�X�������グ����
void MiniBoss::Lift(float deltaTime)
{
	animation_.setIsLoop(false);
	animation_.changeDirType(-1.0f);
	if (stateTimer_ >= 2.0f) isLift_ = true;
}

// ���S���
void MiniBoss::RunAway(float deltaTime)
{
	direction_.x = -1.0f;
	position_.x += direction_.x * speed_ * (deltaTime * 60.0f);
}

//�n�ʂ̈ʒu�ɕ␳���܂�
void MiniBoss::groundClamp(Actor& actor)
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
	// �ߋ��̈ʒu
	// Y�����Ɉʒu���Ԃ���
	if (left < 0 &&
		right < 0) {
		// ��ɕ��
		if (top > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = topLeft.y - body_.GetCircle().getRadius();
		}
		// ���ɕ��
		if (bottom > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
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
		if (state_ == State::Approach) {
			if (std::abs(position_.x - bossPositionRX_) < 100.0f) {
				isBossPosition_ = true;
				animation_.setIsLoop(false);
				animation_.stopAnime();
			}
		}
	}

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
		}
		// ���ɕ��
		if (bottom > -actor.getBody().GetBox().getHeight() / 2.0f) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
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
		if (state_ == State::Approach) {
			if (std::abs(position_.x - bossPositionRX_) < 100.0f) {
				isBossPosition_ = true;
				animation_.setIsLoop(false);
				animation_.stopAnime();
			}
		}
	}
}

//�@�~�j�{�X�𐳋C�ɖ߂��܂�
void MiniBoss::backToSanity()
{
	isConfusion_ = false;
}

// �{�X�������グ���Ԃɂ��܂�
void MiniBoss::bossLift()
{
	changeState(State::Lift, MINI_BOSS_LIFT);
}

// �{�X�̈ʒu�ɂ��邩��Ԃ��܂�
bool MiniBoss::isBossPosition()
{
	return isBossPosition_;
}

// �����グ����
bool MiniBoss::isLift()
{
	return isLift_;
}

void MiniBoss::setLiftMove(const float speed)
{
	speed_ = speed;
	changeState(State::RunAway, MINI_BOSS_RUN);
}
