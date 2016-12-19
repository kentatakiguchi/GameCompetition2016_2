#include "DeadEnemy.h"
#include "../../../Define.h"

DeadEnemy::DeadEnemy(
	IWorld * world,
	const Vector2 & position,
	const float bodyScale) : 
	Actor(world_, "DeadEnemy", position, 
		std::make_shared<BoundingBox>(Vector2::One * bodyScale / -2.0f, Matrix::Identity, bodyScale, bodyScale, true)),

	timer_(0.0f),
	isGround_(false),
	animation_(EnemyAnimation2D())
{

}

void DeadEnemy::onUpdate(float deltaTime)
{
	// �d��
	if (isGround_) {
		timer_ += deltaTime;
		position_.y += timer_ * 9.8f * (deltaTime * 60.0f);
	}

	//timer_ += deltaTime;

	isGround_ = false;
}

void DeadEnemy::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	// �v���C���[�֘A�̃I�u�W�F�N�g�ɓ������Ă���Ȃ�
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	// �}�b�v�̃u���b�N�ɓ���������A�������s��
	if (getFloorName != NULL) {
		groundClamp(actor);
	}
}

void DeadEnemy::onMessage(EventMessage event, void *)
{
}

// �n�ʂ̈ʒu�ɕ␳���܂�
void DeadEnemy::groundClamp(Actor & actor)
{
	if (actor.body_->width() == 0) return;
	// �����`���m�̌v�Z
	// �������g��1f�O�̒��S�ʒu���擾
	auto pos = body_->pre_pos();
	// ���葤�̎l�p�`��4�_���擾
	auto topLeft = actor.getBody()->points()[0];
	auto topRight = actor.getBody()->points()[1];
	auto bottomLeft = actor.getBody()->points()[2];
	auto bottomRight = actor.getBody()->points()[3];
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
	if (left < body_->width() / 2.0f &&
		right < body_->width() / 2.0f) {
		// ��ɕ��
		if (top > 0) {
			position_.y = topLeft.y - body_->height() / 2.0f;
			// �ڒn
			isGround_ = true;
			timer_ = 0.0f;
		}
		// ���ɕ��
		if (bottom > 0)
			position_.y = bottomRight.y + body_->height() / 2.0f;
	}
	// X�����Ɉʒu���Ԃ���
	if (top < body_->height() / 2.0f &&
		bottom < body_->height() / 2.0f) {
		// ���ɕ��
		if (left > 0)
			position_.x = bottomLeft.x - body_->width() / 2.0f;
		// �E�ɕ��
		if (right > 0)
			position_.x = topRight.x + body_->width() / 2.0f;
	}
}

