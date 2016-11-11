#include "BaseBoss.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../../../Base/ActorGroup.h"
#include "../../../Body/CollisionBase.h"
#include "BossManager.h"

BaseBoss::BaseBoss(IWorld * world, const Vector2 & position, const float bodyScale) : 
	Actor(world, "BaseEnemy", position,
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	dp_(20),
	initDp_(dp_),
	hp_(3),
	stateTimer_(0.0f),
	timer_(0.0f),
	deltaTimer_(0.0f),
	stateString_("�ҋ@"),
	// bossManager_(nullptr),
	playerPastPosition_(Vector2::Zero),
	player_(nullptr),
	state_(State::Idel),
	attackState_(AttackState::JumpAttack),
	bossManager_(BossManager(position))
{
	// �{�X�}�l�[�W���[
	/*auto manager = std::make_shared<BossManager>(position);
	bossManager_ = &*manager;*/
}

BaseBoss::~BaseBoss()
{
}

void BaseBoss::onUpdate(float deltaTime)
{
	// ��ԃ^�C�}(�ő�l�P)�̍X�V
	setTimer(deltaTime);
	// ��Ԃ̍X�V
	updateState(deltaTime);
	// �ʒu���N�����v����
	position_.y = MathHelper::Clamp(position_.y, -1000, 500.0f);
}

void BaseBoss::onDraw() const
{
	// �f�o�b�O
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �G�̕\��
	/*DrawGraph(
		position_.x - scale_ / 2.0f, position_.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);*/
	// �����̕\��
	DrawString(
		vec3Pos.x, vec3Pos.y,
		stateChar, GetColor(255, 255, 255));
	body_.draw(inv_);
}

void BaseBoss::onCollide(Actor & actor)
{
	// �v���C���[�ɓ���������A�ϋv�l��������

	//auto actorName = actor.getName();
	//if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
	//	auto damage = 10;
	//	hp_ -= damage;
	//	dp_ -= damage;
	//	// �̗͂�0�ɂȂ����玀�S
	//	if (hp_ <= 0) {
	//		changeState(State::Dead, BOSS_DEAD);
	//		body_.enabled(false);
	//		return;
	//	}
	//	// �ϋv�l��0�ɂȂ�����A�Ђ��
	//	if (dp_ <= 0) {
	//		changeState(State::Flinch, BOSS_FLINCH);
	//		body_.enabled(false);
	//		return;
	//	}
	//	// �������̂��߂�return
	//	return;
	//}
}

void BaseBoss::onMessage(EventMessage event, void *)
{
}

void BaseBoss::updateState(float deltaTime)
{
	switch (state_)
	{
	case State::Idel: idel(deltaTime); break;
	case State::Attack: attack(deltaTime); break;
	case State::Flinch: flinch(deltaTime); break;
	case State::Dead: deadMove(deltaTime); break;
	}

	stateTimer_ += deltaTime;
	// �ʒu�̍X�V
	//position_ = bossManager_->getMovePosition();
}

void BaseBoss::changeState(State state, unsigned int motion)
{
	state_ = state;
	stateTimer_ = 0.0f;
}

void BaseBoss::changeAttackState(AttackState aState, unsigned int motion)
{
	attackState_ = aState;
}

void BaseBoss::idel(float deltaTime)
{
	stateString_ = "�ҋ@���";
	// ����Ԃ�ς���
	if (stateTimer_ >= 5.0f) {
		changeAttackState(AttackState::JumpAttack, BOSS_ATTACK);
		changeState(State::Attack, BOSS_ATTACK);
	}

	// bossManager_->attackMove(ATTACK_JUMPATTACK_NUMBER);
	// position_ = bossManager_->getMovePosition();

	// jumpAttack_.update(deltaTime);
}

void BaseBoss::attack(float deltaTime)
{
	// �U����Ԃ̑I��
	switch (attackState_) {
	case AttackState::JumpAttack: jumpAttack(deltaTime); break;
	case AttackState::WallAttack: wallAttack(deltaTime); break;
	case AttackState::SpeacialAttack: specialAttack(deltaTime); break;
	}

	// �U�����I��������A�ҋ@��ԂɑJ��
	//if (bossManager_->isAttackEnd()) {
	//	changeState(State::Idel, BOSS_IDLE);
	//	// �{�X�}�l�[�W���[�̓����l�����t���b�V��
	//	bossManager_->moveRefresh();
	//}
}

void BaseBoss::flinch(float deltaTime)
{
	stateString_ = "�Ђ��";
	// ��莞�Ԍo�߂őҋ@��ԂɑJ��
	if (stateTimer_ < 5.0f) return;
	changeState(State::Idel, BOSS_IDLE);
	dp_ = initDp_;
}

void BaseBoss::deadMove(float deltaTime)
{
	stateString_ = "���S";
	//dead();
}

void BaseBoss::jumpAttack(float deltaTime)
{
	stateString_ = "�W�����v�U��";
	// �W�����v�U��
	bossManager_.attackMove(ATTACK_JUMPATTACK_NUMBER, deltaTime);
	position_ = bossManager_.getMovePosition();
	// �W�����v�U�����I�������A�ҋ@��Ԃɂ���
	if (bossManager_.isAttackEnd())
		changeState(State::Idel, BOSS_IDLE);
	// bossManager_.jumpAttack(deltaTime);
	// bossManager_->attackMove(ATTACK_JUMPATTACK_NUMBER);
}

void BaseBoss::wallAttack(float deltaTime)
{
	stateString_ = "�ǍU��";
	// bossManager_.wallAttack(deltaTime);
}

void BaseBoss::specialAttack(float deltaTime)
{
	stateString_ = "�X�y�V�����ȍU��";
	// bossManager_.specialAttack(deltaTime);
}

void BaseBoss::setTimer(float deltaTime)
{
	timer_ = deltaTime * 60.0f;
}
