#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "../Base/IScene.h"

class TitleScene : public IScene{
public:
	TitleScene(SceneDataKeeper* keeper);
	~TitleScene();
	virtual void start() override;
	virtual void update() override;
	void slideText(int targettext);
	void moveText(int targettext);
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;

private:
	int id;	
	int sinCount;
	Vector2 textPos;
	std::map<int,Vector2> shotPos;
	std::map<int, int> defposlist;
	std::map<int, Vector2> lastPoses;
	std::map<int, Vector2> setPoses;
	std::map<int, int> boundCou;
	std::map<int, bool> isPoint;
	std::map<int, bool> isShotArrive;
	std::map<int,bool> isArrive;
};

#endif