#pragma once

#include "../Base/IScene.h"
#include"../../Math/Vector2.h"
#include"SceneChange.h"
#include<map>

class MainMenuScene : public IScene {
public:
	MainMenuScene(SceneDataKeeper* keeper);
	~MainMenuScene();
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
	int targetPoint;
	int sinCount;
	int alphaCou[2];
	int alphadefSpeeds[2];

	std::map<int,Vector2> textPoses;
	std::map<int,Scene> nextScene;
	std::map<int, Vector2> lastPoses;

	std::map<int, Vector2> shotPos;
	std::map<int, int> defposlist;
	std::map<int, Vector2> setPoses;
	std::map<int, int> boundCou;
	std::map<int, bool> isPoint;
	std::map<int, bool> isShotArrive;
	std::map<int, bool> isArrive;

};

