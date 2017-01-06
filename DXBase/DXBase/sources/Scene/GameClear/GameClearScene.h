#ifndef GAME_CLEAR_SCENE_H_
#define GAME_CLEAR_SCENE_H_

#include "../Base/IScene.h"
#include<map>
#include"../../ResourceLoader/ResourceLoader.h"
#include"../StageClear/StageClearTextAnm.h"

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
	int targetPoint;
	int sinCount;

	std::map<int, Scene> nextScene;
	std::map<int, Vector2> textPoses;

	std::map<int, TextureID> textIDs;

	StageClearTextAnm anmer_;

};

#endif