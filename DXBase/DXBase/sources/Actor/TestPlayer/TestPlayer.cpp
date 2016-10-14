#include "TestPlayer.h"
#include "../../Game/Time.h"
TestPlayer::TestPlayer(IWorld * world, const Vector3 & position) :
	Actor(world, "Player", position, BoundingSphere(5.0f))
{
	position_ = Vector3::Zero;
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::onUpdate(float deltaTime)
{
	prePosition = Vector2(position_.x, position_.y);
	Vector2 vec;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::A))
	{
		vec.x = -1.0f;
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::D))
	{
		vec.x = 1.0f;
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::S))
	{
		vec.y = 1.0f;
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::W))
	{
		vec.y = -1.0f;
	}
	vec = vec.Normalize();
	position_ += Vector3(vec.x, vec.y, 0.0f)*100.0f*Time::GetInstance().deltaTime();
	curPosition = Vector2(position_.x, position_.y);
	//‘¬“x‚ðŒvŽZ
	mVelo = prePosition - curPosition;
}

void TestPlayer::onDraw() const
{
	DrawCircle(position_.x, position_.y, 10.0f, GetColor(255, 255, 255), TRUE);
}

void TestPlayer::onCollide(Actor & other)
{
}
