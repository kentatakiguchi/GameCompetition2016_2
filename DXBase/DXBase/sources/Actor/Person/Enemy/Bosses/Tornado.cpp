#include "Tornado.h"
#include "../../../../ResourceLoader/ResourceLoader.h"

Tornado::Tornado(IWorld * world, const Vector2 & position, const Vector2& bodyScale) :
	Actor(world, "Tornado", position,
		CollisionBase(
			Vector2(position.x + bodyScale.x, position.y + bodyScale.y / 2.0f),
			Vector2(position.x, position.y + bodyScale.y / 2.0f),
			Vector2(position.x + bodyScale.x, position.y - bodyScale.y / 2.0f),
			Vector2(position.x, position.y - bodyScale.y / 2.0f)
			)),
	angle_(0.0f),
	initPosition_(position),
	animation_(EnemyAnimation2D())
{
	// �A�j���[�V�����̒ǉ�
	animation_.addAnimation(
		0,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_EFFECT_ATTACK_SUIKOMI_TEX));
	animation_.changeAnimation(0);
	/*animation_.changeAnimation(
		static_cast<int>(0));*/
}

void Tornado::onUpdate(float deltaTime)
{
	animation_.update(deltaTime);

	// ���̑{��
	//auto mouse = world_->findActor("BossEntry");
	/*if (mouse != nullptr)
		position_ = mouse->getPosition();*/

	//auto a = rotation_.;
	//body_.

	//body_.RotateBox(-45);

	/*auto point = body_.GetBox().component_.point;
	auto addPos = (0.0f, -100.0f);

	body_.GetBox().transform(
		point[1] + addPos, point[2] + addPos,
		point[3] + addPos, point[4] + addPos);*/

	//findPlayer();
	//auto player = world_
}

void Tornado::onDraw() const
{
	//findPlayer();
	/*auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;*/
	// �f�o�b�O
	//DrawFormatString(600, 25, GetColor(255, 0, 255), "���W:%f,%f", position_.x,position_.y);

	//body_.draw(inv_);

	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �A�j���[�V�����̕`��
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	DrawGraph(
		vec3Pos.x,
		vec3Pos.y,
		ResourceLoader::GetInstance().getTextureID(
			TextureID::ENEMY_NEEDLE_TEX), 0);
	animation_.draw(
		pos,
		Vector2::Zero,
		2.0f);
}

void Tornado::onCollide(Actor & actor){}

void Tornado::onMessage(EventMessage event, void *){}

// �ʒu�����������܂�
void Tornado::initPosition()
{
	position_ = initPosition_;
}

// �p�x��ύX���܂�
void Tornado::setAngle(int angle)
{
	body_.RotateBox(angle);
	angle_ = angle;
}

// �v���C���[��T���܂�
void Tornado::findPlayer() const
{
	auto player = world_->findActor("PlayerBody1");
	auto playerLength_ = 0.0f;
	if (player != nullptr) {
		playerLength_ = Vector2(player->getPosition() - position_).Length();
	}
	if (playerLength_ >=
		SCREEN_SIZE.x / 2.0f + body_.GetBox().getHeight())
		return;
}
