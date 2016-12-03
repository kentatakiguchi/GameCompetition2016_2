#pragma once

#include "../Base/IScene.h"
#include <memory>

class World;

class LoadingScene : public IScene {
public:
	LoadingScene(SceneDataKeeper* keeper);
	~LoadingScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;

private:
	void load_player_res();
private:
	bool isEnd_;
};