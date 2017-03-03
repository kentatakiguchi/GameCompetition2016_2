#include "FighterMiniBossh.h"
#include "ImportAnimationNumber.h"
#include "../../../../../ResourceLoader/ResourceLoader.h"
#include "../../../../../World/IWorld.h"
#include "../../../../../Math/Math.h"
#include "../../../../../Define.h"

FighterMiniBoss::FighterMiniBoss(
	IWorld * world, 
	const Vector2 & position,
	const float bodyScale,
	const std::string name) :
	Actor(world, name, position,
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	animeNum_(WAIT_NUMBER),
	stateTimer_(0.0f),
	speed_(4.0f),
	size_(0.0f),
	degree_(90.0f),
	damegeTimer_(0.0f),
	isClamp_(false),
	isGround_(false),
	isAttackHit_(false),
	isInvincible_(false),
	playerName_(""),
	addTexPos_(Vector2::Zero),
	orizin_(Vector2::One * (256 / 2)),
	prevPlayerDirection_(Vector2::Zero),
	color_(Vector3::One * 255.0f),
	state_(State::Idel),
	animation_(EnemyAnimation2D())
{
	addAnimation();
	animation_.changeAnimation(WAIT_NUMBER);
	animation_.timeRandom();
	// �e�N�X�`���̈ʒu�̐ݒ�
	//setTexPosition(10.0f);
	addTexPos_ = Vector2::Up * 10.0f;
	// �T�C�Y�̐ݒ�
	size_ = body_.GetCircle().getRadius() / (128.0f / 1.5f);
	// �v���C���[�̕���������
	animation_.changeDirType(-getPlayerDirection().x);
}

void FighterMiniBoss::onUpdate(float deltaTime)
{
	// ��Ԃ̍X�V
	updateState(deltaTime);
	// �A�j���[�V�����̍X�V
	animation_.update(deltaTime);
	// �e�N�X�`���̃A���t�@�ݒ�
	texAlpha(deltaTime);

	isGround_ = false;
	isBottom_ = false;
	isLeft_ = false;
	isRight_ = false;
}

void FighterMiniBoss::onDraw() const
{
	auto position = position_ + -addTexPos_;
	//auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	auto vec3Pos = Vector3(position.x, position.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// size_
	animation_.draw(
		Vector2(vec3Pos.x, vec3Pos.y),
		orizin_,
		size_,
		degree_ + 270.0f,
		color_);
}

void FighterMiniBoss::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	auto getPlayerName = strstr(actorName.c_str(), "PlayerBody");
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	// ��������ԂȂ�Ԃ�
	// ���ɓ����������̏���
	if (getFloorName != NULL) {
		groundClamp(actor);
		floorHit();
		return;
	}
	// �v���C���[�֘A�̃I�u�W�F�N�g�ɓ���������
	if (getPlayerName != NULL) {
		playerHit(actor);
		return;
	}
	// ���S��ԂȂ�Ԃ� 
	if (state_ == State::Dead) return;
	// �v���C���[�̍U���ɓ���������A�������s��
	if (actorName == "PlayerAttackCollider") {
		// ���G���A�_���[�W�^�C�}���O�łȂ��Ȃ�Ԃ�
		if (isInvincible_ || damegeTimer_ > 0.0f) return;
		playerAttackHit(actor);
		return;
	}
}

void FighterMiniBoss::onMessage(EventMessage event, void *)
{
}

void FighterMiniBoss::changeState(State state, int animation)
{
	state_ = state;
	if (animeNum_ != animation)
		animation_.changeAnimation(animation);
	animeNum_ = animation;
	stateTimer_ = 0.0f;
}

void FighterMiniBoss::updateState(float deltaTime)
{
	// �v���C���[�����̒��ɓ������玀�S
	if (world_->isEntered())
		changeState(State::Dead, DEAD_NUMBER);
	if (damegeTimer_ > 0.0f)
		damegeTimer_ = max(damegeTimer_ -= deltaTime, 0.0f);
	else isAttackHit_ = false;

	switch (state_)
	{
	case State::BattleIdel: battleIdel(deltaTime); break;
	case State::Idel: idel(deltaTime); break;
	case State::Move: move(deltaTime); break;
	case State::Attack: attack(deltaTime); break;
	case State::Dead: deadMove(deltaTime); break;
	}

	stateTimer_ += deltaTime;
}

void FighterMiniBoss::battleIdel(float deltaTime)
{
}

void FighterMiniBoss::idel(float deltaTime)
{
}

void FighterMiniBoss::move(float deltaTime)
{
}

void FighterMiniBoss::attack(float deltaTime)
{
}

void FighterMiniBoss::deadMove(float deltaTime)
{
	name_ = "DeadMiniBoss";
	size_ -= deltaTime;
	size_ = max(0.0f, size_);
	if (size_ == 0.0f)
		dead();
}

void FighterMiniBoss::floorHit()
{
}

// �v���C���[�ɓ����������̏���	
void FighterMiniBoss::playerHit(Actor & actor)
{
}

// �v���C���[�̍U���ɓ����������̏���
void FighterMiniBoss::playerAttackHit(Actor & actor)
{
	changeState(State::Dead, DEAD_NUMBER);
	body_.enabled(false);
}

Vector2 FighterMiniBoss::getPlayerDirection()
{
	auto player = world_->findActor("PlayerBody1");
	// �v���C���[�����Ȃ�������A�P�ʃx�N�g����Ԃ�
	if (player == nullptr) return Vector2::One;
	// �����̌v�Z
	auto distance = position_ - player->getPosition();
	auto direction = Vector2::One;
	// �����̒l����
	// X
	if (distance.x < 0)
		direction.x = -1;
	else if (distance.x > 0)
		direction.x = 1;
	else direction.x = 0;
	// Y
	if (distance.y < 0)
		direction.y = 1;
	else if (distance.y > 0)
		direction.y = -1;
	else direction.y = 0;
	return direction;
}

void FighterMiniBoss::addAnimation()
{
	animation_.addAnimation(
		WAIT_NUMBER,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WAIT_TEX));
	animation_.addAnimation(
		RUN_NUMBER,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WALLATTACK_DASH_TEX));
	animation_.addAnimation(
		ADHERE_NUMBER,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_BREATH_DYSFUNCTION_TEX));
	animation_.addAnimation(
		DEAD_NUMBER,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_DEATH_TEX));
	animation_.addAnimation(
		WING_ATTACK_NUMBER,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_JUMP_DOWN_TEX));
	animation_.addAnimation(
		WALL_ATTACK_NUMBER,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WALLATTACK_DASHJUMP_TEX));
	animation_.addAnimation(
		PIYORI_NUMBER,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_PIYO_TEX));
}

// �{�X�̃A���t�@�l��ݒ肵�܂�
void FighterMiniBoss::texAlpha(float deltaTime)
{
	if (isAttackHit_) {
		if ((int)(stateTimer_ * 10) % 2 < 1) alpha_ -= (int)(deltaTime * 750);
		else alpha_ += deltaTime * 750;
		alpha_ = MathHelper::Clamp((float)alpha_, 100, 255);
	}
	else alpha_ = 255;
}

void FighterMiniBoss::groundClamp(Actor & actor)
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
			isGround_ = true;
			isHit = true;
		}
		// ���ɕ��
		if (bottom > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
			isBottom_ = true;
			isHit = true;
		}
	}
	// X�����Ɉʒu���Ԃ���
	else if (top < 0 &&
		bottom < 0) {
		// ���ɕ��
		if (left > 0) {
			position_.x = bottomLeft.x - body_.GetCircle().getRadius();
			isLeft_ = true;
			isHit = true;
		}
		// �E�ɕ��
		if (right > 0) {
			position_.x = topRight.x + body_.GetCircle().getRadius();
			isRight_ = true;
			isHit = true;
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
			isGround_ = true;
		}
		// ���ɕ��
		if (bottom > -actor.getBody().GetBox().getHeight() / 2.0f) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
			isBottom_ = true;
		}
	}
	// X�����Ɉʒu���Ԃ���
	if (top < 0 &&
		bottom < 0) {
		// ���ɕ��
		if (left > -actor.getBody().GetBox().getWidth() / 2.0f) {
			position_.x = bottomLeft.x - body_.GetCircle().getRadius();
			isLeft_ = true;
		}
		// �E�ɕ��
		if (right > -actor.getBody().GetBox().getWidth() / 2.0f) {
			position_.x = topRight.x + body_.GetCircle().getRadius();
			isRight_ = true;
		}
	}
}
