#include "AdhereMiniBoss.h"
#include "ImportAnimationNumber.h"
#include "../../../../../ResourceLoader/ResourceLoader.h"
#include "../../../../../Define.h"
#include "../../../../../World/IWorld.h"
#include <random>

AdhereMiniBoss::AdhereMiniBoss(
	IWorld * world, const Vector2 & position, 
	const float bodyScale) :
	FighterMiniBoss(world, position, bodyScale),
	adhereDeadTime_(4.0f)
{
}

void AdhereMiniBoss::changeDeadState(DeadState dState, int animation)
{
	if (dState_ == dState) return;
	changeState(State::Dead, animation);
	dState_ = dState;
}

void AdhereMiniBoss::idel(float deltaTime)
{
	if (stateTimer_ < 0.5f) return;
	changeState(State::Move, WAIT_NUMBER);
	auto player = world_->findActor("PlayerBody1");
	auto distance = player->getPosition() - position_;
	prevPlayerDirection_ = distance.Normalize();
}

void AdhereMiniBoss::move(float deltaTime){}

void AdhereMiniBoss::attack(float deltaTime)
{
	auto player = world_->findActor(playerName_);
	// �v���C���[�����Ȃ��Ȃ玀�S
	if (player == nullptr) {
		//changeState(State::Dead, DEAD_NUMBER);
		changeDeadState(DeadState::HitDead, DEAD_NUMBER);
		body_.enabled(false);
		return;
	}
	auto addPos = Vector2(
		100.0f * MathHelper::Cos(degree_),
		100.0f * MathHelper::Sin(degree_));
	position_ = player->getPosition() + addPos;
	setTexPosition(10.0f);
	if (stateTimer_ < adhereDeadTime_) return;
	//changeState(State::AdhereDead, DEAD_NUMBER);
	changeDeadState(DeadState::AdhereDead, DEAD_NUMBER);
	body_.enabled(false);
}

void AdhereMiniBoss::deadMove(float deltaTime){

	switch (dState_)
	{
	case DeadState::HitDead: FighterMiniBoss::deadMove(deltaTime); break;
	case DeadState::AdhereDead: adhereDead(deltaTime); break;
	}
}

// ���������S���
void AdhereMiniBoss::adhereDead(float deltaTime)
{
	name_ = "DeadMiniBoss";
	size_ -= deltaTime;
	size_ = max(0.0f, size_);
	if (size_ == 0.0f)
		dead();
}

// ���ɓ����������̏���
void AdhereMiniBoss::floorHit(){}

// �v���C���[�Ɠ����������̏���
void AdhereMiniBoss::playerHit(Actor & actor)
{
	changeState(State::Attack, ADHERE_NUMBER);
	animation_.setIsLoop(false);
	playerName_ = actor.getName();
	position_ = actor.getPosition();
	degree_ = getRandomDegree();
}

void AdhereMiniBoss::addAnimation()
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
}

// �����_���̊p�x���擾���܂�
float AdhereMiniBoss::getRandomDegree()
{
	// �����̎擾
	std::random_device random;
	// �����Z���k�c�C�X�^�[�@ ��Œ��ׂ�
	// ����Seed�l��n��
	std::mt19937 mt(random());
	// �͈͂̎w��(int�^)
	std::uniform_int_distribution<> degree(0, 360);
	return (float)degree(mt);
}
