#include "BossEffect.h"

BossEffect::BossEffect(
	IWorld * world,
	std::string name,
	const Vector2 & position,
	const Vector2 & texSize,
	const int animeNum,
	const AnimationID id,
	const bool isLoop) :
	Actor(world, name, position,CollisionBase()),
	animation_(EnemyAnimation2D()),
	//alpha_(255),
	scale_(1.0f),
	isLoop_(isLoop),
	texSize_(texSize)
{
	//auto texSize = 512;
	// �G�̉摜�ɍ��킹�Ē���
	// �ҋ@
	animation_.addAnimation(
		static_cast<int>(animeNum),
		ResourceLoader::GetInstance().getAnimationIDs(id));
	animation_.changeAnimation(static_cast<int>(animeNum));
}

BossEffect::~BossEffect(){
	// �A�j���[�V�������N���A����
	//animation_.
}

void BossEffect::onUpdate(float deltaTime)
{
	animation_.update(deltaTime);
	if (animation_.isEndAnimation() && !isLoop_)
		dead();
}

void BossEffect::onDraw() const
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �A�j���[�V�����̕`��
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	// ���u�����h�̐ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha_);
	animation_.draw(
		pos,
		texSize_ / 2,
		Vector2::One * scale_);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void BossEffect::onCollide(Actor & actor){}
