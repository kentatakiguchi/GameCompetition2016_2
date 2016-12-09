#pragma once
#ifndef TEST_CHARA_H_
#define TEST_CHARA_H_
#include"../../Actor/Base/Actor.h"

#define CHIPSIZE 32

static const float slipspeed = 1;

class TestChara :public Actor {
public:
	TestChara(IWorld* world, Vector2& position) :
		Actor(world, "Player", Vector2(position.x, position.y), CollisionBase(
			Vector2(0, 0),30.f))	{
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


		speed_.Length() > 0 ? speed_ -= speed_/10:speed_=Vector2::Zero;

		position_ += speed_;

	}
	virtual void onDraw() const override {
		body_.draw();
		DrawFormatString(250, 100, GetColor(255, 255, 255), "%f:%f", position_.x, position_.y);
	}
	virtual void onCollide(Actor& other) {
		Vector2 myCenter, segCenter, segPoint, targetPoint, targetVec;
		float posReset;
		//DrawFormatString(250, 100, GetColor(255, 255, 255), "deta");
		DrawFormatString(250, 150, GetColor(255, 255, 255), "%f:%f", other.position_.x, other.position_.y);
		if (other.name_ == "SegmentCollider") {//線分はpositionを中心に取る


			//Vector2 myCenter = Vector2(previousPosition.x,previousPosition.y);
			//相手の線分の中心
			segCenter = other.position_;
			//自分の前の位置-相手の中心
			myCenter = previousPosition - segCenter;
			//相手の中心から端へのベクトル(内積の計算に使う)
			segPoint = (other.body_.GetSegment().component_.point[1]) - segCenter;
			//正規化、内積のaの部分にする
			segPoint = segPoint.Normalize();
			//segpointをa、自分をbとして、内積の計算を行う
			posReset = (segPoint.x*myCenter.x) + (segPoint.y*myCenter.y);
			//内積の計算で求めた、中心点から自分の位置への長さを相手の線分の向きに補正する
			targetPoint = segPoint*posReset;
			//前の位置-
			targetVec = previousPosition - (targetPoint + other.position_);

			targetVec = targetVec.Normalize();

			Vector2 posCenter = position_ - segCenter;
			Vector2 positionPoint = (segPoint)* ((segPoint.x*posCenter.x) + (segPoint.y*posCenter.y));

			position_ = (segCenter + positionPoint) + (targetVec*body_.GetCircle().component_.radius);

			Vector2 moves = position_ - previousPosition;

			if (moves.y > 0)speed_ = slipspeed * ((segCenter + positionPoint) - (segCenter + targetPoint));
			

		}


	}
private:
	int mama = 1;
	int mamama = 5;
	Vector2 previousPosition;
	Vector2 speed_;
};

#endif // !MAPCHIP_H_


