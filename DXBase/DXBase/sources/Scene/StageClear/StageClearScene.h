#pragma once
#ifndef STAGE_CLEAR_SCENE_H_
#define STAGE_CLEAR_SCENE_H_

#include "../Base/IScene.h"

class StageClearScene : public IScene {
public:
	StageClearScene(SceneDataKeeper* keeper);
	~StageClearScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;
private:
	int id;
};

#endif