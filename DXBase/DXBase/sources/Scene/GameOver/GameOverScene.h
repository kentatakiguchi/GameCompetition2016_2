#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "../Base/IScene.h"

class GameOverScene : public IScene{
public:
	GameOverScene();
	~GameOverScene();
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