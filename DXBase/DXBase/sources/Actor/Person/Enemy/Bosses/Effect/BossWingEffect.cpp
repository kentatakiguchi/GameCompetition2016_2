#include "BossWingEffect.h"
#include "../../../../../ResourceLoader/ResourceLoader.h"

BossWingEffect::BossWingEffect(
	IWorld * world, 
	const Vector2 & position, 
	const float bodyScale) :
	Actor(world, "WingEffect", position, 
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	rotaSpeed_(0.0f),
	degree_(0.0f),
	texDegree_(0.0f),
	stateTimer_(0.0f),
	bezierTimer_(0.0f),
	flyPower_(0.0f),
	//alpha_(255.0f),
	isTexTurn_(false),
	direction_(Vector2::One),
	color_(Vector3::Zero),
	state_(State::FlyOut),
	mt_(std::mt19937())
{
	// �����̎擾
	std::random_device random;
	// �����Z���k�c�C�X�^�[�@ ��Œ��ׂ�
	// ����Seed�l��n��
	std::mt19937 mt(random());
	mt_ = mt;
	if (getRandomInt(0, 1) > 0)
		direction_.x = 1;
	else {
		direction_.x = -1;
		isTexTurn_ = true;
	}
	// �p�x
	degree_ = (float)getRandomInt(20, 180 - 20);
	// ��
	flyPower_ = getRandomInt(200, 400) / 10.0f;
	// ��]���x
	rotaSpeed_ = getRandomInt(30, 40) / 10.0f;
	// �F
	color_ = Vector3::One * 255;
	color_.y = (float)getRandomInt(0, 255);
}

void BossWingEffect::onUpdate(float deltaTime)
{
	// ��Ԃ̍X�V
	switch (state_)
	{
	case State::FlyOut: flyOut(deltaTime); break;
	case State::Fall: fall(deltaTime); break;
	case State::Dead: deadMove(deltaTime); break;
	}
	// ��������
	alpha_ -= 255 * deltaTime;
	alpha_ = max(alpha_, 0.0f);
	if (alpha_ <= 0.0f)
		dead();

	stateTimer_ += deltaTime;
}

void BossWingEffect::onDraw() const
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	// �摜�̕\��
	auto scale = 16.0f;
	// ���u�����h�̐ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha_);
	SetDrawBright((int)color_.x, (int)color_.y, (int)color_.z);
	DrawRotaGraph3(
		(int)pos.x, (int)pos.y,
		(int)body_.GetCircle().getRadius(), (int)body_.GetCircle().getRadius(),
		body_.GetCircle().getRadius() / scale,
		body_.GetCircle().getRadius() / scale, MathHelper::ToRadians(texDegree_),
		ResourceLoader::GetInstance().getTextureID(TextureID::BOSS_WING_TEX), 1, isTexTurn_);
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void BossWingEffect::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	//���֘A�̃I�u�W�F�N�g�ɓ������Ă���Ȃ玀�S����
	if (getFloorName != NULL || actorName == "Door") {
		// �ʒu�̕��
		groundClamp(actor);
		//changeState(State::Dead);
		return;
	}
}

// ��Ԃ̕ύX
void BossWingEffect::changeState(State state)
{
	if (state_ == state)return;
	state_ = state;
}

// �r�o���
void BossWingEffect::flyOut(float deltaTime)
{
	position_ += flyPower_ * 
		Vector2(MathHelper::Cos(degree_), -MathHelper::Sin(degree_)) * 
		(deltaTime * 60.0f);
	// �͂̌��Z
	flyPower_ -= deltaTime * 22.0f * 10.0f;
	flyPower_ = max(flyPower_, 0.0f);
	// �͂������Ȃ�����A������ԂɑJ��
	if (flyPower_ == 0.0f) 
		changeState(State::Fall);
}

// �������
void BossWingEffect::fall(float deltaTime)
{
	//auto time = deltaTime / 5;
	auto time = deltaTime / 5 * (rotaSpeed_ / 4.0f);
	// �ړ���
	auto velo = bezier(time, Vector2(2.0f, 1.0f));
	// �ȈՖ��C��
	// rotaSpeed_ = 4.0f;
	auto f = bezier(time, Vector2(0.0f, 0.0f), Vector2(0.0f, 1.0f), Vector2(0.0f, 0.0f));
	texDegree_ -= direction_.x * (1 - velo.y) * (rotaSpeed_ * f.y) * (deltaTime * 60.0f);
	position_ += direction_ * velo *  4.0f * (deltaTime * 60.0f);
	// �x�W�F���I�������A�ēx�s��
	if (bezierTimer_ >= 1.0f) {
		bezierTimer_ = 0.0f;
		direction_.x *= -1.0f;
	}
}

// ���S���
void BossWingEffect::deadMove(float deltaTime)
{
	/*alpha_ -= 255 * (deltaTime / 2);
	alpha_ = max(alpha_, 0.0f);
	if (alpha_ <= 0.0f)
		dead();*/
	//dead();
}

// �x�W�F�Ȑ����擾���܂�(�n�_�E�I�_0)
Vector2 BossWingEffect::bezier(float deltaTime, const Vector2 & direPoint)
{
	/*auto startPoint = Vector2(0.0f, 0.0f);auto endPoint = Vector2(0.0f, 0.0f);*/
	return bezier(deltaTime, Vector2::Zero, direPoint, Vector2::Zero);
}

// �x�W�F�Ȑ����擾���܂�(�n�_�ƏI�_�̎w��)
Vector2 BossWingEffect::bezier(
	float deltaTime, const Vector2 & startPoint, 
	const Vector2 & direPoint, const Vector2 & endPoint)
{
	bezierTimer_ += deltaTime;
	bezierTimer_ = min(bezierTimer_, 1.0f);

	auto x = (1.0f - bezierTimer_) * (1.0f - bezierTimer_) * startPoint.x +
		2 * (1.0f - bezierTimer_) * bezierTimer_ * direPoint.x +
		bezierTimer_ * bezierTimer_ * endPoint.x;

	auto y = (1.0f - bezierTimer_) * (1.0f - bezierTimer_) * startPoint.y +
		2 * (1.0f - bezierTimer_) * bezierTimer_ * direPoint.y +
		bezierTimer_ * bezierTimer_ * endPoint.y;

	return Vector2(x, y);
}

//�n�ʂ̈ʒu�ɕ␳���܂�
void  BossWingEffect::groundClamp(Actor & actor)
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
			changeState(State::Dead);
			isHit = true;
			return;
		}
		// ���ɕ��
		if (bottom > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
			isHit = true;
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
			changeState(State::Dead);
			return;
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

// �����_���̒l���擾���܂�
int BossWingEffect::getRandomInt(const int min, const int max)
{
	// �͈͂̎w��(int�^)
	std::uniform_int_distribution<> value(min, max);
	return value(mt_);
}
