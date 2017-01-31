#include "MiniBoss.h"
#include "../../../Base/ActorGroup.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../FloorSearchPoint.h"

MiniBoss::MiniBoss(
	IWorld * world, 
	const Vector2 & position, 
	const float scale) : 
	Actor(world, "MiniRunBoss", position,
		CollisionBase(const_cast<Vector2&>(position), 64.0f * scale)),
	scale_(scale),
	direction_(Vector2::One * -1),
	animation_(EnemyAnimation2D()),
	fspObj_(nullptr)
{
	// ������ς���
	auto size = (int)(scale * 100);
	if (size % 2 == 1) direction_.x = 1;
	// �A�j���[�V�����̒ǉ�
	int animID = 0;
	animation_.addAnimation(animID,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WALLATTACK_DASH_TEX));
	animation_.changeAnimation(animID);
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
	animation_.update(deltaTime);

	auto speed = 6.0f;
	position_.y += 9.8f * (deltaTime * 60.0f);
	position_.x += direction_.x * speed * (deltaTime * 60.0f);
	fspObj_->setPosition(position_);
	// ������ς���
	if (fspObj_->isGround()) {
		direction_.x *= -1;
		animation_.changeDirType(direction_.x);
	}
	fspObj_->setDirection(direction_);
}

void MiniBoss::onDraw() const
{
	auto size = 256;
	animation_.draw(
		position_, 
		Vector2(size / 2, size / 1.5f),
		scale_);
}

void MiniBoss::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	//���֘A�̃I�u�W�F�N�g�ɓ������Ă���Ȃ�
	auto getFloorName = strstr(actorName.c_str(), "Floor");
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
	}
}
