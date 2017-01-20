#ifndef BOSS_STAGE_H_
#define BOSS_STAGE_H_

#include "../Base/IScene.h"
#include <memory>
#include "../../Math/Math.h"
#include"../GamePlay/PauseScreen.h"
#include"../GamePlay/MoveScreen.h"
#include "../../Animation/Base/Animation2D.h"
#include "../../Actor/Door/Door.h"
#include "../../Animation/Base/Animation2D.h"
class World;
class BackGraundManager;
class BaseBoss;

class BossStage : public IScene {
public:
	BossStage(SceneDataKeeper* keeper);
	~BossStage();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;

private:
	using WorldPtr = std::shared_ptr<World>;
	// ワールド
	WorldPtr	world_;

	BackGraundManager* backManager;
	BaseBoss* boss_;				// ボス
	Door* door_;

	Scene nextScene_;

	float deltaTime_;

	bool isStopped_;

	float mIvemtTime;

	PauseScreen pause_;
	MoveScreen move_;

	ActorPtr player;

	Animation2D hatenaAnm_;
};

#endif
