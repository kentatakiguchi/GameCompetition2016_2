#include "BaseBoss.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../../../Base/ActorGroup.h"
#include "../../../Body/CollisionBase.h"
#include "../../../../Define.h"
#include "BossManager.h"
#include "BossEntry.h"
#include "BossHeart.h"
#include "../FloorSearchPoint.h"
// �{�X�̗͕̑\��
#include "../../../UIActor/BossGaugeUI/BossGaugeUI.h"

// �{�X�N���X(�x�[�X�\��)
BaseBoss::BaseBoss(IWorld * world, const Vector2 & position, const float bodyScale) :
	Actor(world, "BaseBoss", position,
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	dp_(100),
	initDp_(dp_),
	hp_(3),
	flinchCount_(0),
	// initHp_(hp_),
	stateTimer_(0.0f),
	timer_(0.0f),
	deltaTimer_(0.0f),
	isGround_(false),
	isBottomHit_(false),
	isBodyHit_(false),
	isAttackHit_(true),
	isSceneEnd_(true),
	stateString_("�ҋ@"),
	// bossManager_(nullptr),
	playerPastPosition_(Vector2::Zero),
	player_(nullptr),
	state_(State::Idel),
	attackState_(AttackState::JumpAttack),
	fspObj_(nullptr),
	entryObj_(nullptr),
	heartObj_(nullptr),
	bossGaugeUI_(nullptr),
	bossManager_(BossManager(position)),
	top_(0.0f), bottom_(0.0f), right_(0.0f), left_(0.0f),
	handle_(CreateFontToHandle("�l�r ����", 40, 10, DX_FONTTYPE_NORMAL))
{
	// �R���e�i�ɒǉ�(�U�����ɒǉ�����)
	asContainer_.push_back(AttackState::JumpAttack);
	asContainer_.push_back(AttackState::WallAttack);
	asContainer_.push_back(AttackState::SpeacialAttack);
	// �{�X�}�l�[�W���[
	/*auto manager = std::make_shared<BossManager>(position);
	bossManager_ = &*manager;*/
	// ���{���I�u�W�F�N�g
	auto fspObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, bodyScale + 1.0f), 0.1f
		);
	world_->addActor(ActorGroup::Enemy, fspObj);
	fspObj_ = &*fspObj;
	// �{�X�����I�u�W�F�N�g
	auto entryObj = std::make_shared<BossEntry>(
		world_, position_, 
		Vector2(bodyScale / 2.0f, bodyScale / 2.0f),
		bodyScale / 2.0f);
	world_->addActor(ActorGroup::Enemy, entryObj);
	entryObj_ = &*entryObj;
	// �{�X�S���I�u�W�F�N�g
	auto heartHP = 100;
	auto heartObj = std::make_shared<BossHeart>(
		world_, Vector2(position_.x + 128.0f, position_.y -32.0f), heartHP, hp_);
	world_->addActor(ActorGroup::Enemy, heartObj);
	heartObj_ = &*heartObj;
	// �{�X�̗̑̓Q�[�W
	auto bossUI = std::make_shared<BossGaugeUI>(world_, Vector2::Zero);
	world_->addUIActor(bossUI);
	bossGaugeUI_ = bossUI.get();
	bossGaugeUI_->SetHp(heartObj_->getHeartHp() * hp_);
}

BaseBoss::~BaseBoss()
{
}

void BaseBoss::onUpdate(float deltaTime)
{

	clampList_.clear();

	// ��ԃ^�C�}(�ő�l�P)�̍X�V
	setTimer(deltaTime);

	// �̗͂̍X�V
	hp_ = heartObj_->getBossHp();
	bossGaugeUI_->SetHp(heartObj_->getHeartHp());

	entryObj_->setBossPosition(position_);
	// ��Ԃ̍X�V
	updateState(deltaTime);
	// �ڒn(��)
	bossManager_.setIsGround(isGround_);
	bossManager_.setIsBottom(isBottomHit_);

	fspObj_->setPosition(position_);
	/*entryObj_->setBossPosition(position_);*/
	// entryObj_->setDirection(direction_);
	//position_.y = MathHelper::Clamp(position_.y, -1000, 500.0f);

	// bool�n
	isGround_ = false;
	isBottomHit_ = false;
}

void BaseBoss::onDraw() const
{
	// �f�o�b�O
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �{�X�̕\��
	DrawGraph(
		vec3Pos.x - body_.GetCircle().getRadius(),
		vec3Pos.y - body_.GetCircle().getRadius(),
		ResourceLoader::GetInstance().getTextureID(TextureID::BOSS_TEX), 1);
	// �G�̕\��
	/*DrawGraph(
		position_.x - scale_ / 2.0f, position_.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);*/
	DrawFormatStringToHandle(50, 300, GetColor(255, 255, 255),
		handle_, "�u���b�N�Ƃ̈ʒu=>��:%d ��:%d", (int)top_, (int)bottom_);
	DrawFormatStringToHandle(50, 350, GetColor(255, 255, 255),
		handle_, "�u���b�N�Ƃ̈ʒu=>�E:%d ��:%d", (int)right_, (int)left_);
	// ��Ԃ̕\��
	DrawString(
		vec3Pos.x, vec3Pos.y - 100,
		stateChar, GetColor(255, 255, 255));
	// �̗͂̕\��
	// �̗͂̕\��
	DrawFormatString(
		vec3Pos.x, vec3Pos.y - 150,
		GetColor(255, 255, 255), "�̗�:%d", hp_);
	DrawFormatString(
		vec3Pos.x, vec3Pos.y - 175,
		GetColor(255, 255, 255), "����:%d", (int)stateTimer_);
	body_.draw(inv_);
}

void BaseBoss::onCollide(Actor & actor)
{
	auto actorName = actor.getName();

	// �u���b�N�̉����ɂԂ�������A������悤�ɂ���?
	// �v���O�����������āA�R�����g�A�E�g����

	// �}�b�v�̃u���b�N�ɓ���������A�������s��
	if (actorName == "MovelessFloor") {
		// �ʒu�̕��
		groundClamp(actor);
		return;
	}
	// �󒆂ɕ����ԏ��ɓ���������A�Ђ�݃J�E���g�����Z����
	if (actorName == "BossAreaFloor") {
		// �ʒu�̕��
		if (state_ == State::Attack)
			flinchCount_++;
		groundClamp(actor);
		return;
	}
	// ����̏�Ԃł̓v���C���[�ɐG��Ă������N����Ȃ��悤�ɂ���
	if (state_ == State::Flinch || state_ == State::Dead) return;
	// �v���C���[�̍U���͈͂ɓ��������ꍇ�̏���
	if (actorName == "Player_AttackCollider") {
		// �v���C���[�̍U���ɓ�����Ȃ��ꍇ�͕Ԃ�
		if (!isAttackHit_) return;
		// �_���[�W����
		damage(3);
		return;
	}
	// �v���C���[�{�̂ɓ��������ꍇ�̏���
	if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
		// �v���C���[�ɓ�����Ȃ��ꍇ�͕Ԃ�
		if (!isBodyHit_) return;
		// �_���[�W����
		damage(1);
		// �������̂��߂�return
		//return;
	}
}

void BaseBoss::onMessage(EventMessage event, void *)
{
}

// �V�[�����I�������邩��Ԃ��܂�
bool BaseBoss::isSceneEnd()
{
	return isSceneEnd_;
}

void BaseBoss::updateState(float deltaTime)
{
	// ���݂͎g�p�s��
	// player_ = world_->findActor("Player");
	player_ = world_->findActor("PlayerBody1");

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
	// ������ԂȂ�Ԃ�
	if (state_ == state) return;
	state_ = state;
	stateTimer_ = 0.0f;
}

void BaseBoss::changeAttackState(AttackState aState, unsigned int motion)
{
	// �U����Ԃɋ����J�ڂ���
	changeState(State::Attack, BOSS_ATTACK);
	attackState_ = aState;
	bossManager_.prevPosition();
}

void BaseBoss::idel(float deltaTime)
{
	stateString_ = "�ҋ@���";
	// �v���C���[���擾�ł��Ă���΁A�G�l�~�[�}�l�[�W���[�Ɉʒu�Ȃǂ�����
	setBMStatus();


	// �f�o�b�O
	auto speed = 4.0f;
	auto deltaTimer = deltaTime * 60.0f;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L))
		position_.x += speed * deltaTimer;
	else if (InputMgr::GetInstance().IsKeyOn(KeyCode::J))
		position_.x += -speed * deltaTimer;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::I))
		position_.y += -speed * deltaTimer;
	else if (InputMgr::GetInstance().IsKeyOn(KeyCode::K))
		position_.y += speed * deltaTimer;

	// ��莞�Ԍo�߂ōU����ԂɑJ��
	if (stateTimer_ >= 5.0f) {
		// �c��̗͂ōU����Ԃ�ς���
		// initHp - hp
		changeAttackState(
			asContainer_[asContainer_.size() - hp_], BOSS_ATTACK);
		return;
	}
	// �d��
	if (!isGround_) {
		position_.y += 9.8f * (1.0f);// * 60.0f);
	}
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
	//	bossManager_->attackRefresh();
	//}
}

void BaseBoss::flinch(float deltaTime)
{
	stateString_ = "�Ђ��";
	entryObj_->setIsEntry(true);
	// �d��
	if (position_.y < FIELD_SIZE.y) {
		position_.y += 9.8f * (1.0f);// * 60.0f);
	}

	// �̓��ɓ����Ă�����A�n�[�g�ɓ��������Ƃ�m�点��
	if (entryObj_->isEntered() && !heartObj_->isLetOut()) {
		// �v���C���[���o�Ă�����A�ҋ@��Ԃɂ���
		stateTimer_ = 5.0f;
		heartObj_->setIsEntered(true);
	}
	// �̓��ɓ������牽������
	if (entryObj_->isEntered()) {
		// �v���C���[��ǂ��o���Ă��Ȃ��Ȃ�Ԃ�
		if (!heartObj_->isLetOut()) return;
		// �v���C���[���o�Ă���
		entryObj_->letOut();
	}
	// �̗͂�0�ɂȂ����玀�S
	if (hp_ <= 0) 
		changeState(State::Dead, BOSS_DEAD);
	// ��莞�Ԍo�߂őҋ@��ԂɑJ��
	if (stateTimer_ < 5.0f) return;
	changeState(State::Idel, BOSS_IDLE);
	entryObj_->setIsEntry(false);
	dp_ = initDp_;
}

void BaseBoss::deadMove(float deltaTime)
{
	stateString_ = "���S";
	// ���S�����莞�Ԍo�߂Ȃ�A�V�[�����I��������
	if (stateTimer_ >= 3.0f)
		isSceneEnd_ = true;
	//dead();
}

void BaseBoss::jumpAttack(float deltaTime)
{
	stateString_ = "�W�����v�U��";
	// �v���C���[�{�̂ɓ�����Ȃ�
	//isBodyHit_ = false;
	// �W�����v�U��
	bossManager_.attackMove(ATTACK_JUMPATTACK_NUMBER, deltaTime);
	position_ = bossManager_.getMovePosition();
	// �W�����v�U�����I�������A�ҋ@��Ԃɂ���
	if (bossManager_.isAttackEnd()) {
		changeState(State::Idel, BOSS_IDLE);
		//isBodyHit_ = true;
		bossManager_.attackRefresh();
	}
}

void BaseBoss::wallAttack(float deltaTime)
{
	/*isBodyHit_ = false;
	isAttackHit_ = false;*/
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

// �{�X�}�l�[�W���[�̃X�e�[�^�X�̐ݒ�
void BaseBoss::setBMStatus()
{
	if (player_ != nullptr) {
		bossManager_.setPlayerPosition(player_->getPosition());
		bossManager_.setPosition(position_);
		// ����������
		auto direction = bossManager_.getPlayerDirection();
		// �߂� y = -1.0f��
		// direction.y = -1.0f;
		direction.y = 1.0f;
		entryObj_->setDirection(direction);
	}
}

// �w�肵���l�̃_���[�W�ʂ����Z���܂�
void BaseBoss::damage(const int damage)
{
	dp_ -= damage;
	// �ϋv�l��0�ɂȂ�����A�Ђ��
	if (dp_ <= 0) {
		changeState(State::Flinch, BOSS_FLINCH);
		// �Փ˂��邩�ǂ����� bool ��S��true�ɂ���
		isBodyHit_ = true;
		isAttackHit_ = true;
		setBMStatus();
		body_.enabled(false);
	}
}

//�n�ʂ̈ʒu�ɕ␳���܂�
void BaseBoss::groundClamp(Actor& actor)
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

	top_ = top;
	bottom_ = bottom;
	right_ = right;
	left_ = left;
	// �ߋ��̈ʒu
	// Y�����Ɉʒu���Ԃ���
	if (left < 0 &&
		right < 0) {
		// ��ɕ��
		if (top > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = topLeft.y - body_.GetCircle().getRadius();
			// �ڒn
			isGround_ = true;
			isHit = true;
		}
		// ���ɕ��
		if (bottom > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
			// �u���b�N�̉����ɓ�������
			isBottomHit_ = true;
			isHit = true;
		}
	}
	// X�����Ɉʒu���Ԃ���
	if (top < 0 &&
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
		if (top > -actor.getBody().GetBox().getHeight() / 2.0f + 1.0f) {
			position_.y = topLeft.y - body_.GetCircle().getRadius();
			// �ڒn
			isGround_ = true;
		}
		// ���ɕ��
		if (bottom > -actor.getBody().GetBox().getHeight() / 2.0f + 1.0f) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
			// �u���b�N�̉����ɓ�������
			isBottomHit_ = true;
		}
	}
	// X�����Ɉʒu���Ԃ���
	if (top < 0 &&
		bottom < 0) {
		// ���ɕ��
		if (left > -actor.getBody().GetBox().getWidth() / 2.0f + 1.0f)
			position_.x = bottomLeft.x - body_.GetCircle().getRadius();
		// �E�ɕ��
		if (right > -actor.getBody().GetBox().getWidth() / 2.0f + 1.0f)
			position_.x = topRight.x + body_.GetCircle().getRadius();
	}

	// 60
	// 160
	//// ���ɕ��
	//if (left > -14)
	//	position_.x = bottomLeft.x - body_.GetCircle().getRadius();
	//// �E�ɕ��
	//if (right > -body_.GetCircle().getRadius())
	//	position_.x = topRight.x + body_.GetCircle().getRadius();

	/*if (top >= 0 && left <= 0 && right <= 0) {
		position_.y = t_left.y - PLAYER_RADIUS;
	}
	if (bottom >= 0 && left <= 0 && right <= 0) {
		position_.y = b_right.y + PLAYER_RADIUS;
	}
	if (right >= 0 && top <= 0 && bottom <= 0) {
		position_.x = t_right.x + PLAYER_RADIUS;
	}
	if (left >= 0 && top <= 0 && bottom <= 0) {
		position_.x = b_left.x - PLAYER_RADIUS;
	}
	if (left <= 0 && right <= 0 && top <= 0 && bottom <= 0) {
		position_ = center + (pos - center).Normalize() * (t_left - center).Length();
	}*/

	//float r2 = body_.GetCircle().getRadius() * body_.GetCircle().getRadius();
	//Vector2 topV = topRight - topLeft;
	//Vector2 v1 = position_ - topLeft;
	//float t = Vector2::Dot(topV, v1) / Vector2::Dot(topV, topV);
	//Vector2 vn =t * topV;
	//// Vector2 vn = v1 - t * v;
	////if (0 < t && t < 1 && vn.LengthSquared() <= r2) {
	////	// pc = p1 + v * t + r * Vector2.Normalize(vn); // ���S���ړ�
	////	position_ = topLeft + topV * t + body_.GetCircle().getRadius() *
	////		Vector2::Normalize(vn);
	////}
	//top_ = vn.Length();
}