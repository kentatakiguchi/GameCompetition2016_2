#pragma once
#ifndef _TEST_SCENE_H_
#define _TEST_SCENE_H_

#include "../Base/IScene.h"
#include"../../Actor/Base/Actor.h"
#include"../../Field/MapGenerator.h"
#include"../../World/World.h"

class TestScene : public IScene {
public:
	TestScene();
	~TestScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;

private:
	int id;
	BoundingBox box_;
	BoundingBox box2_;
	BoundingCapsule capsule_;
	BoundingCapsule capsule2_;
	BoundingSegment segment_;
	BoundingSegment segment2_;
	BoundingCircle circle_;
	BoundingCircle circle2_;
	Actor a;
	Actor b;
	using WorldPtr = std::shared_ptr<World>;

	WorldPtr	world_;

};

#endif