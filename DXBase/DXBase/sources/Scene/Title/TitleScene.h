#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "../Base/IScene.h"

class TitleScene : public IScene{
public:
	TitleScene();
	~TitleScene();
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