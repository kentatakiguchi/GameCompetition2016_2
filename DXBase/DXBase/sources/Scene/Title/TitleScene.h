#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "../Base/IScene.h"
#include"../../ResourceLoader/ResourceLoader.h"

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
	int slideSize;

	int id;	
	int sinCount;
	int alphaCou;

	Vector2 textPos;
	std::map<int,Vector2> shotPos;
	std::map<int, int> defposlist;
	std::map<int, Vector2> lastPoses;
	std::map<int, Vector2> setPoses;
	std::map<int, int> boundCou;
	std::map<int, bool> isPoint;
	std::map<int, bool> isShotArrive;
	std::map<int, bool> isArrive;
	std::map<int, int> titleBackStageNum;
	//背景を変更する時間を設定する
	std::map<int, float> titleBackChangeTime;
	//各番号で表示される画像のIDをセットしておく
	std::map<int,TextureID> baseTitleBackID;
	//現在の背景画像のID
	std::vector<TextureID> currentTitleBackID;
	//背景画像を変更するタイミングを決める
	std::map<int, bool> changeBackChecker;
	//背景画像の移動先を決める
	std::vector<int> changeTargetChecker;
};

#endif