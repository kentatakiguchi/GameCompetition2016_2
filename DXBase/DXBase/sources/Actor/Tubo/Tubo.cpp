#include "Tubo.h"
#include "../../Game/Time.h"
Tubo::Tubo(IWorld * world, const Vector2 & position) :
	Actor(world, "Tubo", position, CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE),position.y },
		Vector2{ position.x,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE),position.y - (CHIPSIZE) }
		)),
	mVelo(Vector2::Zero),
	mDownFlag(false)
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
	}


	//mVelo = Vector2::Clamp(mVelo, Vector2(0, 0), Vector2(0, 10));



}

void Tubo::onDraw() const
{
	body_.draw(inv_);
}

void Tubo::onCollide(Actor & other)
{
	if (other.getName() == "PlayerBody1"||
		other.getName() == "PlayerBody2") {
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
