#ifndef _GAME_PLAY_SCENE_H_
#define _GAME_PLAY_SCENE_H_

#include "../Base/IScene.h"
#include <memory>
#include "../../Math/Math.h"
#include"PauseScreen.h"
#include"MoveScreen.h"

class World;
class BackGraundManager;
class GamePlayScene : public IScene{
public:
	GamePlayScene(SceneDataKeeper* keeper);
	~GamePlayScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;
private:
	using WorldPtr = std::shared_ptr<World>;
	// ÉèÅ[ÉãÉh
	WorldPtr	world_;

	BackGraundManager* backManager;

	Scene nextScene_;

	float deltaTime_;

	bool isStopped_;

	PauseScreen pause_;
	MoveScreen move_;
};

#endif