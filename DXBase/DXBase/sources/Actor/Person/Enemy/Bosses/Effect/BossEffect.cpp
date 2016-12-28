#include "BossEffect.h"

BossEffect::BossEffect(
	IWorld * world,
	std::string name,
	const Vector2 & position,
	const Vector2 & texSize,
	const int animeNum,
	const AnimationID id) :
	Actor(world, name, position,CollisionBase()),
	animation_(EnemyAnimation2D()),
	scale_(1.0f),
	texSize_(texSize)
{
	//auto texSize = 512;
	// 敵の画像に合わせて調整
	// 待機
	animation_.addAnimation(
		static_cast<int>(animeNum),
		ResourceLoader::GetInstance().getAnimationIDs(id));
	animation_.changeAnimation(static_cast<int>(animeNum));
}

BossEffect::~BossEffect(){
	// アニメーションをクリアする
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
	// アニメーションの描画
	auto pos = Vector2(vec3Pos.x, vec3Pos.y);
	animation_.draw(
		pos,
		texSize_ * scale_,
		scale_);
	body_.draw();
}

void BossEffect::onCollide(Actor & actor){}

// アニメーションの追加を行います
//void BossEffect::addAnimation()
//{
//	auto texSize = 256;
//	// 敵の画像に合わせて調整
//	// 待機
//	/*animation_.addAnimation(
//		animeNum,
//		ResourceLoader::GetInstance().getTextureID(id),
//		texSize, 8, 4, 1);
//	animation_.changeAnimation(animeNum);*/
//}
