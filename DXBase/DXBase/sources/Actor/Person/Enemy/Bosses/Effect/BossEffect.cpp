#include "BossEffect.h"

BossEffect::BossEffect(
	IWorld * world,
	std::string name,
	const Vector2 & position,
	const int animeNum,
	const TextureID id,
	const Vector2 texSize,
	const Vector2 size,
	const int surplus) :
	Actor(world, name, position, CollisionBase()),
	animation_(EnemyAnimation2D())
{
	//auto texSize = 512;
	// �G�̉摜�ɍ��킹�Ē���
	// �ҋ@
	animation_.addAnimation(
		static_cast<int>(animeNum),
		ResourceLoader::GetInstance().getTextureID(id),
		texSize, (int)size.x, (int)size.y, surplus);
	animation_.changeAnimation(static_cast<int>(animeNum));
}

BossEffect::~BossEffect(){
	// �A�j���[�V�������N���A����
	//animation_.
}

void BossEffect::onUpdate(float deltaTime)
{
	animation_.update(deltaTime);
	if (animation_.isEndAnimation())
		dead();
}

void BossEffect::onDraw() const
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �A�j���[�V�����̕`��
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	animation_.draw(
		pos - Vector2(
			body_.GetCircle().getRadius() * 2,
			body_.GetCircle().getRadius() * 2),
		Vector2::One * (body_.GetBox().getWidth() * 2),
		1.0f);
}

void BossEffect::onCollide(Actor & actor){}

// �A�j���[�V�����̒ǉ����s���܂�
//void BossEffect::addAnimation()
//{
//	auto texSize = 256;
//	// �G�̉摜�ɍ��킹�Ē���
//	// �ҋ@
//	/*animation_.addAnimation(
//		animeNum,
//		ResourceLoader::GetInstance().getTextureID(id),
//		texSize, 8, 4, 1);
//	animation_.changeAnimation(animeNum);*/
//}
