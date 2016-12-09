#include "DeadEnemy.h"
#include "../../../Define.h"

DeadEnemy::DeadEnemy(
	IWorld * world,
	const Vector2 & position,
	const Vector2 & bodyScale,
	const int id,
	const int res,
	const Vector2 & direction) : 
	Actor(world_, "DeadEnemy", position, 
		CollisionBase(CollisionBase(
			Vector2(position.x + bodyScale.x / 2.0f, position.y + bodyScale.y / 2.0f),
			Vector2(position.x - bodyScale.x / 2.0f, position.y + bodyScale.y / 2.0f),
			Vector2(position.x + bodyScale.x / 2.0f, position.y - bodyScale.y / 2.0f),
			Vector2(position.x - bodyScale.x / 2.0f, position.y - bodyScale.y / 2.0f)
			))),
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

void DeadEnemy::onDraw() const
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �f�o�b�O
	body_.draw(inv_);
	// �A�j���[�V�����̕`��
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	/*animation_.draw(
		pos, Vector2::One * (body_.GetBox().getWidth() * 2) + addTexPosition_,
		0.5f, 0);*/
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
	if (left < body_.GetBox().getWidth() / 2.0f &&
		right < body_.GetBox().getWidth() / 2.0f) {
		// ��ɕ��
		if (top > 0) {
			position_.y = topLeft.y - body_.GetBox().getHeight() / 2.0f;
			// �ڒn
			isGround_ = true;
			timer_ = 0.0f;
		}
		// ���ɕ��
		if (bottom > 0)
			position_.y = bottomRight.y + body_.GetBox().getHeight() / 2.0f;
	}
	// X�����Ɉʒu���Ԃ���
	if (top < body_.GetBox().getHeight() / 2.0f &&
		bottom < body_.GetBox().getHeight() / 2.0f) {
		// ���ɕ��
		if (left > 0)
			position_.x = bottomLeft.x - body_.GetBox().getWidth() / 2.0f;
		// �E�ɕ��
		if (right > 0)
			position_.x = topRight.x + body_.GetBox().getWidth() / 2.0f;
	}
}

