#include "NeedleEnemy.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../../../../Define.h"

NeedleEnemy::NeedleEnemy(
	IWorld * world,
	const Vector2 & position,
	const float degrees) :
	BaseEnemy(world, position, CHIPSIZE),
	degrees_(degrees)
{
	// d—Í‚ğg‚í‚È‚¢
	isUseGravity_ = false;
}

void NeedleEnemy::update(float deltaTime){}

void NeedleEnemy::onDraw() const
{
	// j‚Ì‰æ‘œ‚Ì•ûŒü‚ğ•Ï‚¦‚é
	// direction_
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// j‚Ì•\¦
	/*DrawGraph(
		vec3Pos.x - scale_ / 2.0f, vec3Pos.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_NEEDLE_TEX), 0);*/
	DrawRotaGraph(vec3Pos.x, vec3Pos.y, 1.0f, MathHelper::ToRadians(degrees_),
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_NEEDLE_TEX), 1);
}

void NeedleEnemy::onCollide(Actor &){}

void NeedleEnemy::onMessage(EventMessage event, void *){}

// “®‚©‚È‚¢‚Ì‚Å‰½‚à‚µ‚È‚¢
void NeedleEnemy::idel(){}
