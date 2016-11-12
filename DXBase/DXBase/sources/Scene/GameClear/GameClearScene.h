#pragma once
#ifndef GAME_CLEAR_SCENE_H_
#define GAME_CLEAR_SCENE_H_

#include "../Base/IScene.h"

class GameClearScene : public IScene {
public:
	GameClearScene(SceneDataKeeper* keeper);
	~GameClearScene();
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