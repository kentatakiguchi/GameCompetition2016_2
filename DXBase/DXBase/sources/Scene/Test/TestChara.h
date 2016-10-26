#pragma once
#ifndef TEST_CHARA_H_
#define TEST_CHARA_H_
#include"../../Actor/Base/Actor.h"

#define CHIPSIZE 32

class TestChara :public Actor {
public:
	TestChara(IWorld* world, Vector2& position) :
		Actor(world, "TestChara", Vector3(position.x, position.y, 0), CollisionBase(
			Vector2(0,0),0.f))
	{

	}
private:
	virtual void onUpdate(float deltaTime) {
		if (InputMgr::GetInstance().IsKeyOn(KeyCode::RIGHT))
		{
			position_ += Vector3(1, 0, 0);
			//box_ = box_.translate({ 10,0 });
		}
		if (InputMgr::GetInstance().IsKeyOn(KeyCode::LEFT))
		{
			position_ += Vector3(-1, 0, 0);
			//	box_ = box_.translate({ -10,0 });
		}
		if (InputMgr::GetInstance().IsKeyOn(KeyCode::UP))
		{
			position_ += Vector3(0, -1, 0);
			//box_ = box_.translate({ 0,-10 });
		}
		if (InputMgr::GetInstance().IsKeyOn(KeyCode::DOWN))
		{
			position_ += Vector3(0, 1, 0);
			//		box_ = box_.translate({ 0,10 });
		}

	}
	virtual void onDraw() const override {
		body_.draw();
	}
	virtual void onCollide(Actor& other) {
		DrawFormatString(250, 100, GetColor(255, 255, 255), "deta");
	}
};

#endif // !MAPCHIP_H_


