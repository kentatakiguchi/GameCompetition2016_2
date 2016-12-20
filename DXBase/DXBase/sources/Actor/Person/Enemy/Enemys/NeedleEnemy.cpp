#include "NeedleEnemy.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../../../../Define.h"

NeedleEnemy::NeedleEnemy(
	IWorld * world,
	const Vector2 & position,
	const float degrees) :
	Actor(world, "BaseEnemy", position,
		std::make_shared<BoundingBox>(Vector2::One * CHIPSIZE / -2.0f, Matrix::Identity, CHIPSIZE, CHIPSIZE, true))

/*		CollisionBase(
			Vector2(position.x + CHIPSIZE / 2.0f, position.y + CHIPSIZE / 2.0f),
			Vector2(position.x - CHIPSIZE / 2.0f, position.y + CHIPSIZE / 2.0f),
			Vector2(position.x + CHIPSIZE / 2.0f, position.y - CHIPSIZE / 2.0f),
			Vector2(position.x - CHIPSIZE / 2.0f, position.y - CHIPSIZE / 2.0f)
			))*/,
	degrees_(degrees)
{}

void NeedleEnemy::onUpdate(float deltaTime){}

void NeedleEnemy::onDraw() const
{
	// êjÇÃâÊëúÇÃï˚å¸ÇïœÇ¶ÇÈ
	// direction_
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// êjÇÃï\é¶
	/*DrawGraph(
		vec3Pos.x - scale_ / 2.0f, vec3Pos.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_NEEDLE_TEX), 0);*/
	DrawRotaGraph(vec3Pos.x, vec3Pos.y, 1.0f, MathHelper::ToRadians(degrees_),
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_NEEDLE_TEX), 1);
}

void NeedleEnemy::onCollide(Actor &){}

void NeedleEnemy::onMessage(EventMessage event, void *){}
