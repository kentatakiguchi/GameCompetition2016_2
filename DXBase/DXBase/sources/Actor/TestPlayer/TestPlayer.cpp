#include "TestPlayer.h"
#include "../../Game/Time.h"
#include"../Body/CollisionBase.h"

TestPlayer::TestPlayer(IWorld * world, const Vector3 & position) :
	Actor(world, "Player", position, CollisionBase()),
	mPositionVelo(Vector2(800 / 2, 600 / 2))
{
	position_ = Vector3(800/2,600/2,0);
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::onUpdate(float deltaTime)
{
	prePosition = mPositionVelo;
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
	mPositionVelo += Vector2(vec.x, vec.y)*500.0f*Time::GetInstance().deltaTime();
	position_ += Vector3(vec.x, vec.y,0)*500.0f*Time::GetInstance().deltaTime();
	curPosition =mPositionVelo;
	//速度を計算
	mVelo = prePosition - curPosition;
}

void TestPlayer::onDraw() const
{
	DrawCircle(position_.x, position_.y, 10.0f, GetColor(255, 255, 255), TRUE);
	DrawFormatString(500, 125, GetColor(255, 255, 255), 
		"プレイヤー座標:%d,%d", (int)position_.x, (int)position_.y);
}

void TestPlayer::onCollide(Actor & other)
{
}
