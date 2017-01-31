#include "Tubo.h"
#include "../../Game/Time.h"

#include "../../ResourceLoader/ResourceLoader.h"

Tubo::Tubo(IWorld * world, const Vector2 & position) :
	Actor(world, "Tubo", position, CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE),position.y },
		Vector2{ position.x,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE),position.y - (CHIPSIZE) }
		)),
	mVelo(Vector2::Zero),
	mDownFlag(false),
	timer_(0)
{

}

Tubo::~Tubo()
{
}

void Tubo::onUpdate(float deltaTime)
{

	if (mDownFlag) {
		mVelo += Vector2(0.0f, 1.0f)*Time::GetInstance().deltaTime();
		position_ += mVelo;

		if (timer_ >= 5.0f)return;
		timer_ += deltaTime * 2;
		if (timer_ >= 5.0f) {
			world_->setEntry(false, true);
		}
	}


	//mVelo = Vector2::Clamp(mVelo, Vector2(0, 0), Vector2(0, 10));



}

void Tubo::onDraw() const{
	body_.draw(ResourceLoader::GetInstance().getTextureID(TextureID::VASE_TEX), inv_);
	//body_.draw(inv_);
}

void Tubo::onCollide(Actor & other)
{
	if (other.getName() == "PlayerBody1"||
		other.getName() == "PlayerBody2") {
		if (timer_ >= 5.0f)return;
		world_->setEntry(true, false);
		mDownFlag = true;
	}
	//if (other.getName() == "MovelessFloorBreak") {
	//	////’x‚­‚È‚é
	//	mVelo = Vector2::Zero;
	//}
	if (other.getName() == "MovelessFloor") {
		mDownFlag = false;
	}
}
