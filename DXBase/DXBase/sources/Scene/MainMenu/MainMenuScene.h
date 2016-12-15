#pragma once

#include "../Base/IScene.h"
#include"../../Math/Vector2.h"
#include"SceneChange.h"
#include<map>
#include"../../ResourceLoader/ResourceLoader.h"


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
	bool isTitle_;

	int slideSize;
	
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

	std::map<int, int> titleBackStageNum;
	//”wŒi‚ğ•ÏX‚·‚éŠÔ‚ğİ’è‚·‚é
	std::map<int, float> titleBackChangeTime;
	//Še”Ô†‚Å•\¦‚³‚ê‚é‰æ‘œ‚ÌID‚ğƒZƒbƒg‚µ‚Ä‚¨‚­
	std::map<int, TextureID> baseTitleBackID;
	//Œ»İ‚Ì”wŒi‰æ‘œ‚ÌID
	std::vector<TextureID> currentTitleBackID;
	//”wŒi‰æ‘œ‚ğ•ÏX‚·‚éƒ^ƒCƒ~ƒ“ƒO‚ğŒˆ‚ß‚é
	std::map<int, bool> changeBackChecker;
	//”wŒi‰æ‘œ‚ÌˆÚ“®æ‚ğŒˆ‚ß‚é
	std::vector<int> changeTargetChecker;

};

