#include "Stage2MiniBoss.h"
#include "../ImportAnimationNumber.h"
#include "../../Effect/PiyoriEffect.h"
#include "../../../../../Base/ActorGroup.h"
#include "../../../../../../World/IWorld.h"
#include "../../../../../../Define.h"

Stage2MiniBoss::Stage2MiniBoss(
	IWorld * world, 
	const Vector2 & position, 
	const float bodyScale) : 
	MediumBoss(world, position, bodyScale),
	movePositionCount_(0.0f),
	effectCreateTimer_(0.0f),
	isEffectCreate_(false),
	isReturn_(false),
	prevAttackPosition_(position_)
{
	direction_ = Vector2::Left;
	color_ = Vector3(180.0f, 250.0f, 0.0f);
	stars_.clear();
}

void Stage2MiniBoss::idel(float deltaTime)
{
	auto speed = 6.0f;
	auto addPos = speed * direction_.x * (deltaTime * 60.0f);
	position_.x += addPos;
	movePositionCount_ += std::abs(addPos);
	// ��苗���ړ���������A���Ε����Ɉړ�
	if (movePositionCount_ >= CHIPSIZE * 8) {
		direction_.x *= -1.0f;
		movePositionCount_ = 0.0f;
	}
	animation_.changeDirType(direction_.x);
	// ��莞�Ԍo�߂ŁA�U����ԂɑJ��
	if (stateTimer_ < 2.0f) return;
	changeState(State::Attack, WALL_ATTACK_NUMBER);
	prevAttackPosition_ = position_;
	animation_.setIsLoop(false);
	// SE�̍Đ�
	PlaySoundMem(
		ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_WALLATTACK),
		DX_PLAYTYPE_BACK);
	auto player = world_->findActor("PlayerBody1");
	if (player == nullptr) return;
	// �v���C���[�������ꏊ�Ƃ̋������v�Z
	prevPlayerDirection_ = Vector2(player->getPosition() - position_).Normalize();
	// �v���C���[�̕���������
	auto angle = 
		std::atan2(prevPlayerDirection_.y, prevPlayerDirection_.x) * 
		180.0f / MathHelper::Pi;
	degree_ = angle + 180.0f;
}

void Stage2MiniBoss::move(float deltaTime)
{
	// �҂��s��
	if (!isReturn_) piyoriMove(deltaTime);
	else returnMove(deltaTime);
}

void Stage2MiniBoss::attack(float deltaTime)
{
	auto speed = 18.0f;
	position_ += speed * prevPlayerDirection_ * (deltaTime * 60.0f);
}

void Stage2MiniBoss::deadMove(float deltaTime)
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

// ���ɓ����������̏���
void Stage2MiniBoss::floorHit()
{
	// �U����Ԃ̂Ƃ��ɁA�ǂɓ���������҂���ԂɑJ��
	if (state_ != State::Attack) return;
	changeState(State::Move, PIYORI_NUMBER);
	degree_ = 90.0f;
	animation_.setIsLoop(true);
}

// �҂��s��
void Stage2MiniBoss::piyoriMove(float deltaTime)
{
	auto dir = direction_;
	dir.y = 1.0f;
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
	isReturn_ = true;
	isEffectCreate_ = true;
	animation_.changeAnimation(WAIT_NUMBER);
	// �X�^�[�̍폜
	for (auto i = stars_.begin(); i != stars_.end(); i++) {
		auto star = *i;
		star->dead();
	}
	stars_.clear();
	effectCreateTimer_ = 0.0f;
}

// �߂�s��
void Stage2MiniBoss::returnMove(float deltaTime)
{
	auto speed = 4.0f;
	auto distance = prevAttackPosition_ - position_;
	if (speed > distance.Length()) {
		position_ = prevAttackPosition_;
		changeState(State::Idel, WAIT_NUMBER);
		isReturn_ = false;
	}
	else position_ += speed * distance.Normalize() * (deltaTime * 60.0f);
	animation_.changeDirType(distance.Normalize().x);
}
