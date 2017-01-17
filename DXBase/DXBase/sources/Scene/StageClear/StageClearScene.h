#ifndef STAGE_CLEAR_SCENE_H_
#define STAGE_CLEAR_SCENE_H_

#include "../Base/IScene.h"
#include<map>
#include"../../ResourceLoader/ResourceLoader.h"
#include"StageClearTextAnm.h"

class BackGraundManager;

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
	int slideSize;
	int targetPoint;
	int sinCount;

	std::map<int, Scene> nextScene;
	std::map<int, Vector2> textPoses;

	std::map<int, TextureID> textIDs;

	StageClearTextAnm anmer_;

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


	//”wŒiƒNƒ‰ƒX
	BackGraundManager* backManager;

};

#endif