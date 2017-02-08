#include "JumpAttack.h"
#include "../Effect/ImportEffects.h"
#include "../../Rock.h"

JumpAttack::JumpAttack() :
	BossAttack(nullptr, Vector2::Zero),
	degrees_(0.0f),
	jumpPower_(0.0f),
	initJumpPower_(jumpPower_),
	recastTimer_(0.0f),
	initRecastTimer_(recastTimer_),
	isJump_(true),
	isFirstJump_(true),
	isJumpEnd_(true),
	isIdel_(false),
	isRockCreate_(true),
	speed_(Vector2::Zero),
	prevPlayerDistance_(Vector2::Zero)
{}

JumpAttack::JumpAttack(IWorld* world, const Vector2& position) :
	BossAttack(world, position),
	degrees_(60.0f),
	jumpPower_(15.0f),
	initJumpPower_(jumpPower_),
	recastTimer_(0.5f),
	initRecastTimer_(recastTimer_),
	isJump_(false),
	isFirstJump_(false),
	isJumpEnd_(false),
	isIdel_(false),
	isRockCreate_(false),
	speed_(Vector2::One * 2.0f),
	otherName_(""),
	prevOtherName_(""),
	prevPlayerDistance_(Vector2::One)
{
	isBodyHit_ = false;
	isAttackHit_ = true;
	animeNum_ = JUMP_UP_NUMBER;
}

// �U��
void JumpAttack::attack(float deltaTime)
{

	if (collideObj_ != nullptr)
		otherName_ = collideObj_->getName();
	if (otherName_ == "PlayerAttackCollider")
		isAttackHit_ = false;
	if (!isFirstJump_) {
		// �����̐ݒ�
		auto distance = pPosition_ - position_;
		// �����̒l����
		if (distance.x < 0)
			pDirection_.x = -1;
		else if (distance.x > 0)
			pDirection_.x = 1;
		direction_ = pDirection_;
		// ���x�̌���
		speed_.y = (float)getRandomInt(10, 20) * 0.1f;
		// SE�̍Đ�
		PlaySoundMem(
			ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_JUMP),
			DX_PLAYTYPE_BACK);
		//setJumpSpeed();
		isFirstJump_ = true;
	}
	// �W�����v�U�����ɏ��ɐڒn������A���L���X�g�Ɉڍs
	if (isJump_ && isGround_ && timer_ > 0.3f) {
		isIdel_ = true;
		isBodyHit_ = true;
		auto addPos = Vector2::Left * 40.0f;
		if (!isRockCreate_) {
			world_->addActor(ActorGroup::Effect,
				std::make_shared<BokoEffect>(world_, position_ + addPos, 255, 3.0f));
			// ��̐���
			createRock();
			// ���n���ɍU������ǉ�
			PlaySoundMem(
				ResourceLoader::GetInstance().getSoundID(SoundID::SE_BOSS_CHAKUCHI),
				DX_PLAYTYPE_BACK);
		}
		isRockCreate_ = true;
	}
	// �W�����v���I��������A���L���X�g�^�C�������Z����
	if (isIdel_) {
		recastTimer_ -= deltaTime;
		// ���L���X�g���Ԃ� 0 �ɂȂ�����A�W�����v�U���I��
		if (recastTimer_ > 0.0f) return;
		jumpPower_ = initJumpPower_;
		isJump_ = false;
		isJumpEnd_ = true;
		timer_ = 0.0f;
		// �����̐ݒ�
		auto distance = pPosition_.x - position_.x;
		// �����̒l����
		if (distance < 0)
			pDirection_.x = -1;
		else if (distance >= 0)
			pDirection_.x = 1;
		direction_ = pDirection_;
		return;
	}
	// ���L���X�g��ԂłȂ���΃W�����v�U��
	if (recastTimer_ == initRecastTimer_)
		jump(deltaTime);
	// �O��Փ˂����I�u�W�F�N�g�̖��O���X�V
	prevOtherName_ = otherName_;
	otherName_ = "";
	collideObj_ = nullptr;
}

// �W�����v�U��
void JumpAttack::jump(float deltaTime)
{
	if (isBottom_)
		jumpPower_ = 0;
	// �ړ�
	auto addPos = Vector2(
		-std::cos(degrees_) * speed_.x * pDirection_.x * (deltaTime * 60.0f),
		(-jumpPower_ / 10 + timer_ * speed_.y) * 9.8f * 
		((deltaTime * 60.0f)* speed_.y));
	position_ += addPos;
	// �ړ��ʂ� - �Ȃ��A+ �Ȃ牺�̃A�j���[�V�����ɂ���
	if (addPos.y <= 0) animeNum_ = JUMP_UP_NUMBER;
	else animeNum_ = JUMP_DOWN_NUMBER;
	// �W�����v������
	isJump_ = true;
	isAttackStart_ = true;
	// �v���C���[�ɓ������Ă��_���[�W�Ȃ�
	isBodyHit_ = false;
}

// �U���s���̃��t���b�V�����s���܂�
void JumpAttack::Refresh()
{
	BossAttack::Refresh();
	isJump_ = false;
	isFirstJump_ = false;
	isJumpEnd_ = false;
	isIdel_ = false;
	isRockCreate_ = false;
	isBodyHit_ = true;
	jumpPower_ = initJumpPower_;
	recastTimer_ = initRecastTimer_;
	animeNum_ = JUMP_UP_NUMBER;
}

// ��̐���
void JumpAttack::createRock()
{
	// �͈͂̎w��(int�^)
	int size = static_cast<int>(CHIPSIZE);
	// ��̐���
	for (int i = 0; i != 3; i++) {
		// X�̐����ʒu������
		world_->addActor(ActorGroup::Enemy,
			std::make_shared<Rock>(world_,
				Vector2((float)getRandomInt(size * 2, size * 18), 200.0f)));
	}
}
