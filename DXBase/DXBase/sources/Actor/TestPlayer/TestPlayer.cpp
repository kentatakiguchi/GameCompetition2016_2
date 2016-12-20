#include "TestPlayer.h"
#include "../../Game/Time.h"

TestPlayer::TestPlayer(IWorld * world, const Vector2 & position) :
	Actor(world, "TestPlayer", position, std::make_shared<BoundingCircle>(position_, Matrix::Identity, 10.0f, true))
{
	time = 0.0f;
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::onUpdate(float deltaTime)
{
	time += Time::GetInstance().deltaTime();

	if (time >= 2.0f) {
		dead_ = true;
	}
}

void TestPlayer::onDraw() const
{
	DrawCircle(position_.x, position_.y, 100.0f, GetColor(255, 255, 255), TRUE);
	DrawFormatString(25, 25, GetColor(255, 0, 255), "ç¿ïW:%f,%f", position_.x,position_.y);
}

void TestPlayer::onCollide(Actor & other)
{
}
