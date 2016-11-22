#pragma once
#ifndef TEST_CHARA_H_
#define TEST_CHARA_H_
#include"../../Actor/Base/Actor.h"

#define CHIPSIZE 32

class TestChara :public Actor {
public:
	TestChara(IWorld* world, Vector2& position) :
		Actor(world, "Player", Vector2(position.x, position.y), CollisionBase(
			Vector2(0, 0),30.f))
	{
	}
private:
	virtual void onUpdate(float deltaTime) {
		previousPosition = position_;

		if (InputMgr::GetInstance().IsKeyOn(KeyCode::Z))
		{
			mama++;
			position_=body_.setSegmentPoint(position_,Vector2(10*mamama,10*mama),Vector2(30*mamama,30*mama));
			
		}
		if (InputMgr::GetInstance().IsKeyOn(KeyCode::D))
		{
			position_ += Vector2(50, 0);
			//box_ = box_.translate({ 10,0 });
		}
		if (InputMgr::GetInstance().IsKeyOn(KeyCode::A))
		{
			position_ += Vector2(-50, 0);
			//	box_ = box_.translate({ -10,0 });
		}
		if (InputMgr::GetInstance().IsKeyOn(KeyCode::W))
		{
			position_ += Vector2(0, -50);
			//box_ = box_.translate({ 0,-10 });
		}
		if (InputMgr::GetInstance().IsKeyOn(KeyCode::S))
		{
			position_ += Vector2(0, 50);
			//		box_ = box_.translate({ 0,10 });
		}
		if (InputMgr::GetInstance().IsKeyOn(KeyCode::RIGHT))
		{
			position_ += Vector2(1, 0);
			//box_ = box_.translate({ 10,0 });
		}
		if (InputMgr::GetInstance().IsKeyOn(KeyCode::LEFT))
		{
			position_ += Vector2(-1, 0);
			//	box_ = box_.translate({ -10,0 });
		}
		if (InputMgr::GetInstance().IsKeyOn(KeyCode::UP))
		{
			position_ += Vector2(0, -1);
			//box_ = box_.translate({ 0,-10 });
		}
		if (InputMgr::GetInstance().IsKeyOn(KeyCode::DOWN))
		{
			position_ += Vector2(0, 1);
			//		box_ = box_.translate({ 0,10 });
		}
		//DrawFormatString(0, 0, GetColor(255,255,255), "X:%f Y:%f",
			//position_.x, position_.y);

	}
	virtual void onDraw() const override {
		body_.draw();
		DrawFormatString(250, 100, GetColor(255, 255, 255), "%f:%f", position_.x, position_.y);

	}
	virtual void onCollide(Actor& other) {
		Vector2 myCenter,segCenter, segPoint, targetPoint, targetVec;
		float posReset;
		//DrawFormatString(250, 100, GetColor(255, 255, 255), "deta");
		DrawFormatString(250, 150, GetColor(255, 255, 255), "%f:%f", other.position_.x, other.position_.y);
		if (other.name_ == "SegmentCollider") {//ê¸ï™ÇÕpositionÇíÜêSÇ…éÊÇÈ

			//Vector2 myCenter = Vector2(previousPosition.x,previousPosition.y);
			segCenter = other.position_;
			myCenter = previousPosition - segCenter;
			segPoint=(other.body_.GetSegment().component_.point[1]) - segCenter;
			segPoint= segPoint.Normalize();
			
			posReset = (segPoint.x*myCenter.x)+ (segPoint.y*myCenter.y);
			
			targetPoint = segPoint*posReset;
			
			targetVec = previousPosition- (targetPoint+other.position_);

			targetVec = targetVec.Normalize();

			position_ = (segCenter+targetPoint)+(targetVec*body_.GetCircle().component_.radius);

		}
	}
private:
	int mama = 1;
	int mamama = 5;
	Vector2 previousPosition;

};

#endif // !MAPCHIP_H_


