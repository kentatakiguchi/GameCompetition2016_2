#include "Stage3MiniBoss.h"
#include "../ImportAnimationNumber.h"
#include "../FlyingMiniBoss.h"
#include "../../Effect/PiyoriEffect.h"
#include "../../../FloorSearchPoint.h"
#include "../../../../../Base/ActorGroup.h"
#include "../../../../../../World/IWorld.h"
#include "../../../../../../Define.h"

Stage3MiniBoss::Stage3MiniBoss(
	IWorld * world, 
	const Vector2 & position, 
	const float bodyScale) : 
	MediumBoss(world, position, bodyScale),
	wallCount_(0),
	effectCreateTimer_(0.0f),
	groundTimer_(0.0f),
	mbTimer_(0.0f),
	isEffectCreate_(false),
	isPiyori_(false),
	isPrevWspHit_(false),
	prevAttackPosition_(position),
	wspObj_(nullptr)
{
	color_ = Vector3(240.0f, 80.0f, 0.0f);
	// ���{���I�u�W�F�N�g
	auto wspObj = std::make_shared<FloorSearchPoint>(
		world_, position_, Vector2::One * body_.GetCircle().getRadius(), 10.0f);
	world_->addActor(ActorGroup::Enemy, wspObj);
	wspObj_ = &*wspObj;

	// �����R���e�i�ɒǉ�
	moveDirections_.clear();
	moveDirections_.push_back(0.0f);
	moveDirections_.push_back(-1.0f);
	moveDirections_.push_back(0.0f);
	moveDirections_.push_back(1.0f);
	moveDirections_.push_back(0.0f);
}

void Stage3MiniBoss::onUpdate(float deltaTime)
{
	MediumBoss::onUpdate(deltaTime);
	wspObj_->setPosition(position_);
}

void Stage3MiniBoss::battleIdel(float deltaTime)
{
	if (!isGround_)
		position_.y += 9.8f * (deltaTime * 60.0f);
	MediumBoss::battleIdel(deltaTime);
}

void Stage3MiniBoss::idel(float deltaTime)
{
	if (stateTimer_ < 2.0f) return;
	changeState(State::Attack, RUN_NUMBER);
	wspObj_->setDirection(Vector2::Left);
}

void Stage3MiniBoss::move(float deltaTime)
{
	if (isPiyori_)
		piyoriMove(deltaTime);
	else restMove(deltaTime);
}

void Stage3MiniBoss::attack(float deltaTime)
{
	// �ǈړ��U��
	wallAttack(deltaTime);
	// �~�j�{�X�̐���
	createMiniBoss(deltaTime);
}

void Stage3MiniBoss::deadMove(float deltaTime)
{
	// �X�^�[�̍폜
	if (stars_.size() != 0) {
		for (auto i = stars_.begin(); i != stars_.end(); i++) {
			auto star = *i;
			star->dead();
		}
		stars_.clear();
	}
	MediumBoss::deadMove(deltaTime);
}

void Stage3MiniBoss::piyoriMove(float deltaTime)
{
	auto dir = direction_;
	dir.y = 1.0f;
	animation_.setIsLoop(true);
	// ���̐���
	if (isEffectCreate_ && (int)effectCreateTimer_ % 50 <= 24 && stars_.size() < 6) {
		auto star = std::make_shared<PiyoriEffect>(
			world_, position_, 0.5f);
		world_->addActor(ActorGroup::Effect, star);
		stars_.push_back(star);
		isEffectCreate_ = false;
	}
	else if ((int)effectCreateTimer_ % 50 > 24) {
		isEffectCreate_ = true;
	}
	effectCreateTimer_ += deltaTime * 60.0f;
	// �҂��G�t�F�N�g�̈ʒu
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto addPos = Vector2::Up * -50.0f;
		i->get()->position_ = position_ + addPos;
	}
	// �d��
	if (!isGround_) {
		position_.y += 9.8f * (deltaTime * 60.0f);
	}
	// ��莞�Ԍo�߂őҋ@��ԂɑJ��
	if (stateTimer_ < 5.0f) return;
	changeState(State::Idel, WAIT_NUMBER);
	isPiyori_ = false;
	isEffectCreate_ = true;
	// �X�^�[�̍폜
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto star = *i;
		star->dead();
	}
	stars_.clear();
	effectCreateTimer_ = 0.0f;
}

// �x�ݍs��
void Stage3MiniBoss::restMove(float deltaTime)
{
	if (stateTimer_ < 3.0f) return;
	changeState(State::Idel, WAIT_NUMBER);
}

void Stage3MiniBoss::playerAttackHit(Actor & actor)
{
	MediumBoss::playerAttackHit(actor);
	// ����̈ʒu�ɋ���ꍇ�́A�҂���ԂɑJ��
	if (state_ == State::Attack) {
		if (wallCount_ % 4 != 0) {
			isPiyori_ = true;
			wallCount_ = 0;
			degree_ = 90.0f;
			changeState(State::Move, PIYORI_NUMBER);
		}
	}
}

// �ǈړ��U������
void Stage3MiniBoss::wallAttack(float deltaTime)
{
	// ���v����ňړ�
	auto speed = 10.0f * (deltaTime * 60.0f);
	if (wspObj_->isGround() && isPrevWspHit_ != wspObj_->isGround()) wallCount_++;
	isPrevWspHit_ = wspObj_->isGround();
	auto direction = Vector2(
		moveDirections_[(wallCount_ + 1) % 4],
		moveDirections_[wallCount_ % 4]
		);
	direction_ = direction;
	wspObj_->setDirection(direction_);
	degree_ = (float)(wallCount_ * 90 % 360) + 90.0f;
	auto pos = direction * speed * (deltaTime * 60.0f);
	position_ += pos;
}

// ���V�~�j�{�X�̐������s���܂�
void Stage3MiniBoss::createMiniBoss(float deltaTime)
{
	mbTimer_ = max(mbTimer_ - deltaTime, 0.0f);
	if (mbTimer_ > 0.0f) return;
	mbTimer_ = getRandomInt(40, 100) / 10.0f;
	// ����
	int chipsize = static_cast<int>(CHIPSIZE);
	auto pos = Vector2::Zero;
	auto count = getRandomInt(0, 2);
	if (count < 2) {
		// ���ӁE�E�ӂɐ���
		if (count == 0) pos.x = chipsize * 18.0f;
		else if (count == 1) pos.x = chipsize * 2.0f;
		pos.y = (float)getRandomInt(chipsize * 2, chipsize * 7);
	}
	else if (count == 2) {
		// ��ӂɐ���
		pos.y = chipsize * 2.0f;
		pos.x = (float)getRandomInt(chipsize * 2, chipsize * 18);
	}
	// �~�j�{�X(���V)�̐���
	// �ʒu�̕␳
	auto position = position_;
	auto scrollPoint = world_->findActor("BossScrollPoint");
	if (scrollPoint != nullptr)
		position = scrollPoint->getPosition() -
		Vector2(chipsize * 10, chipsize * 6);
	auto miniBoss = std::make_shared<FlyingMiniBoss>(world_, pos + position);
	world_->addActor(ActorGroup::Enemy, miniBoss);
	PlaySoundMem(
		ResourceLoader::GetInstance().getSoundID(SoundID::SE_MINIBOSS_CRY),
		DX_PLAYTYPE_BACK);
}