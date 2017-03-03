#include "DeadEnemy.h"
#include "EnemyHeaderImport.h"
#include "Bosses/Effect/EnemyDeadEffect.h"
#include "../../../Scene/Base/SceneDataKeeper.h"
#include "../../../World/IWorld.h"
#include "../../Item/Items.h"
#include "../../Base/ActorGroup.h"
#include "../../Body/CollisionBase.h"
#include "../../../ResourceLoader/ResourceLoader.h"

DeadEnemy::DeadEnemy(
	IWorld * world,
	const Vector2 & position,
	const float bodyScale,
	const Vector2 & direction,
	const AnimationID animaID) :
	Actor(world, "DeadEnemy", position, 
		CollisionBase(CollisionBase(
			Vector2(position.x + bodyScale / 2.0f, position.y + bodyScale / 2.0f),
			Vector2(position.x - bodyScale / 2.0f, position.y + bodyScale / 2.0f),
			Vector2(position.x + bodyScale / 2.0f, position.y - bodyScale / 2.0f),
			Vector2(position.x - bodyScale / 2.0f, position.y - bodyScale / 2.0f)
			))),
	stateTimer_(0.0f),
	playerSpeed_(0.0f),
	isGround_(false),
	holdLength_(0.0f),
	prevHoldDegree_(0.0f),
	throwDegree_(0.0f),
	playerPravPosition_(Vector2::Zero),
	holdPosition_(Vector2::Zero),
	prevPosition_(position),
	throwVector_(Vector2::Zero),
	color_(Vector3::One * 255.0f),
	isHold_(false),
	playerName_(""),
	otherName_(""),
	isBlockCollideBegin_(false),
	isBlockCollideEnter_(false),
	isBlockCollidePrevEnter_(false),
	isBlockCollideExit_(false),
	animation_(EnemyAnimation2D()),
	state_(State::Dead)
{
	auto id = 0;
	animation_.addAnimation(id,
		ResourceLoader::GetInstance().getAnimationIDs(animaID));
	animation_.changeAnimation(id);
	animation_.setIsLoop(false);
}

void DeadEnemy::onUpdate(float deltaTime)
{
	animation_.update(deltaTime);
	// ��Ԃ̍X�V
	updateState(deltaTime);
	// �Փ˔���̍X�V
	updateCollide();
}

void DeadEnemy::onDraw() const
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �A�j���[�V�����̕`��
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha_);
	SetDrawBright((int)color_.x, (int)color_.y, (int)color_.z);
	animation_.draw(
		pos, Vector2::One * (body_.GetBox().getWidth() * 2) + Vector2(0.0f, 40.0f),
		0.5f);
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void DeadEnemy::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	//auto getPlayerName = strstr(actorName.c_str(), "Player");
	// �v���C���[�֘A�̃I�u�W�F�N�g�ɓ������Ă���Ȃ�
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	// �}�b�v�̃u���b�N�ɓ���������A�������s��
	if (getFloorName != NULL) {
		groundClamp(actor);
		// �Փ˒���true������
		isBlockCollideEnter_ = true;
		// �ߋ��̏Փ˒���false�ŁA�A�ߋ��ƌ��݂̏Փ˒����Ⴄ�Ȃ�ꍇ
		// �Փ˒���ɂȂ�
		if (!isBlockCollidePrevEnter_ &&
			isBlockCollidePrevEnter_ != isBlockCollideEnter_)
			isBlockCollideBegin_ = true;
		// ���ݏ�Ԃŏ��ɐG��Ă�����A�A�C�e����r�o����
		if (state_ == State::Hold && isBlockCollideBegin_ && playerSpeed_) {
			// �A�C�e���̐���
			world_->addActor(ActorGroup::Item,
				std::make_shared<Items>(world_, position_));
		}
		return;
	}
	if (state_ == State::Throw || state_ == State::Delete) return;
	// �v���C���[�̂��ݔ���ɏՓ˂�����A���ݏ�ԂɑJ��
	if (actorName == "PlayerHoldCollider") {
		isHold_ = true;
		if (state_ == State::Hold) return;
		changeState(State::Hold);
		holdPosition_ = position_;
		prevPosition_ = position_;
		// �v���C���[�̖��O��ݒ肵�܂�
		setPlayerName();
		return;
	}
}

void DeadEnemy::onMessage(EventMessage event, void *){}

// ��Ԃ̍X�V
void DeadEnemy::updateState(float deltaTime)
{
	switch (state_)
	{
	case State::Dead: deadMove(); break;
	case State::Hold: holdMove(deltaTime); break;
	case State::Throw: throwMove(deltaTime); break;
	case State::Delete: deleteMove(deltaTime); break;
	}
	// �d��
	if (!isGround_)
		position_.y += 9.8f * (deltaTime * 60.0f);

	stateTimer_ += deltaTime;
}

// ��Ԃ̕ύX
void DeadEnemy::changeState(State state)
{
	if (state_ == state) return;
	state_ = state;
	stateTimer_ = 0.0f;
}

// ���S���
void DeadEnemy::deadMove()
{
	if (stateTimer_ < 5.0f) return;
	changeState(State::Delete);
}

// �����グ���
void DeadEnemy::holdMove(float deltaTime)
{
	auto player = world_->findActor(playerName_);
	auto otherPlayer = world_->findActor(otherName_);
	// �v���C���[�����Ȃ���Ύ��S
	if (player == nullptr || otherPlayer == nullptr) {
		changeState(State::Delete);
		return;
	}
	// �p�x�����߂�
	// ���񂾃v���C���[�Ƃ����Е��̃v���C���[�Ƃ̃x�N�g�������߂�
	auto playerVector = player->getPosition() - otherPlayer->getPosition();
	auto direction = Vector2(playerVector).Normalize();
	// �p�x�̌v�Z
	auto degree = std::atan2(direction.y, direction.x) * 180.0f / MathHelper::Pi;
	// �z�[���h�R���C�_�ɓ������Ă��Ȃ��ꍇ�́A������ԂɑJ��
	if (!isHold_) {
		changeState(State::Throw);
		throwVector_ = Vector2(prevPosition_ - position_);
		throwDegree_ = degree;
		return;
	}
	if (degree < 0) degree += 360.0f;
	// ���ɐG��Ă���Ƃ��͊p�x�̏C��
	if (isGround_) {
		if (degree > 180)
			degree = prevHoldDegree_;
		//degree = MathHelper::Clamp(degree, 0.0f, 180.0f);
	}
		
	auto degreePos = Vector2(
		MathHelper::Cos(degree),
		MathHelper::Sin(degree));
	// ����ł��鑊��̈ʒu + �p�x * ���܂ꂽ���̒���
	position_ = player->getPosition() + degreePos * holdLength_;
	// ���̐���
	auto length = Vector2(position_ - prevPosition_).Length();
	if (isBlockCollideBegin_ && length >= 20.0f) {
		auto star = std::make_shared<Items>(world_, position_);
		world_->addActor(ActorGroup::Item, star);
		starCount_++;
		if (starCount_ >= 5)
			changeState(State::Delete);
	}
	prevPosition_ = position_;
	prevHoldDegree_ = degree;
}

// �������
void DeadEnemy::throwMove(float deltaTime)
{
	auto timer = 0.0f;
	auto power = 15.0f;
	//position_.y += (power + stateTimer_) * (deltaTime * 60.0f);
	//position_ += throwVector_ * 2.0f;
	position_ += Vector2(
		MathHelper::Cos(throwDegree_), MathHelper::Sin(throwDegree_)) *
		(power + throwVector_.Length() / 10.0f);
	position_.y += stateTimer_ * 9.8f * (deltaTime * 60.0f);
	if (isGround_)
		changeState(State::Delete);
}

// ���ŏ��
void DeadEnemy::deleteMove(float deltaTime)
{
	alpha_ = max(alpha_ - 255 * deltaTime , 0.0f);
	if (!isGround_)
		position_.y += 9.8f * (deltaTime * 60.0f);
	if (alpha_ > 0.0f) return;
	// ���S�G�t�F�N�g�̒ǉ�
	world_->addActor(ActorGroup::Effect,
		std::make_shared<EnemyDeadEffect>(
			world_, position_ - Vector2::Up * 325.0f, 0));
	auto se =
		ResourceLoader::GetInstance().getSoundID(SoundID::SE_ENEMY_DEAD);
	PlaySoundMem(se, DX_PLAYTYPE_BACK);
	dead();
}

// �Փˊ֘A�̍X�V
void DeadEnemy::updateCollide()
{
	// bool�n��
	// �ڒn��false�ɂ���
	isGround_ = false;
	isHold_ = false;
	// �ŏ��ɏՓ˒���ƏՓˌ�̔����false�ɂ���
	isBlockCollideBegin_ = false;
	isBlockCollideExit_ = false;
	// �ߋ��̏Փ˒���ture�ŁA�ߋ��ƌ��݂̏Փ˒����Ⴄ�Ȃ�ꍇ
	// �Փˌ�ɂȂ�
	if (isBlockCollidePrevEnter_ &&
		isBlockCollidePrevEnter_ != isBlockCollideEnter_) {
		// �Փˌ�̔���
		isBlockCollideBegin_ = false;
		isBlockCollideExit_ = true;
	}
	// �ߋ��̏Փ˒��ɁA���݂̏Փ˒�������
	isBlockCollidePrevEnter_ = isBlockCollideEnter_;
	// �u���b�N�ɓ������Ă����true�ɂȂ�̂ŁAfalse������
	isBlockCollideEnter_ = false;
}

// �n�ʂ̈ʒu�ɕ␳���܂�
void DeadEnemy::groundClamp(Actor & actor)
{
	auto clampScale = 3.0f;
	if (actor.body_.GetBox().getWidth() == 0) return;
	// �����`���m�̌v�Z
	// �������g��1f�O�̒��S�ʒu���擾
	auto pos = body_.GetBox().previousPosition_;
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
	// Y�����Ɉʒu���Ԃ���
	if (left < body_.GetBox().getWidth() / clampScale &&
		right < body_.GetBox().getWidth() / clampScale) {
		// ��ɕ��
		if (top > 0) {
			position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
			// �ڒn
			isGround_ = true;
		}
		// ���ɕ��
		if (bottom > 0)
			position_.y = bottomRight.y + body_.GetBox().getHeight() / 2.0f;
	}
	// X�����Ɉʒu���Ԃ���
	if (top < body_.GetBox().getHeight() / clampScale &&
		bottom < body_.GetBox().getHeight() / clampScale) {
		// ���ɕ��
		if (left > 0)
			position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;
		// �E�ɕ��
		if (right > 0)
			position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;
	}
}

// �v���C���[�̖��O��ݒ肵�܂�
void DeadEnemy::setPlayerName()
{
	auto player1 = world_->findActor("PlayerBody1");
	auto player2 = world_->findActor("PlayerBody2");
	if (player1 == nullptr || player2 == nullptr) return;
	auto lenght1 = Vector2(position_ - player1->getPosition()).Length();
	auto lenght2 = Vector2(position_ - player2->getPosition()).Length();
	if (lenght1 < lenght2) {
		playerName_ = player1->getName();
		otherName_ = player2->getName();
		holdLength_ = Vector2(position_ - player1->getPosition()).Length();
		//holdPosition_ = player1->getPosition();
	}
	else {
		playerName_ = player2->getName();
		otherName_ = player1->getName();
		holdLength_ = Vector2(position_ - player2->getPosition()).Length();
		//holdPosition_ = player2->getPosition();
	}
	//// ���܂ꂽ�ʒu�Ƃ̋������v�Z
	//holdLength_ = Vector2(position_ - holdPosition_).Length();
}

// �F�̕ύX���s���܂�
void DeadEnemy::setColor(Vector3 color)
{
	color_ = color;
}

