#ifndef BOSS_STAGE_H_
#define BOSS_STAGE_H_

#include "../Base/IScene.h"
#include <memory>
#include "../../Math/Math.h"
//#include"PauseScreen.h"
//#include"MoveScreen.h"

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
	// ���[���h
	WorldPtr	world_;

	// Status status_;

	BackGraundManager* backManager;
	BaseBoss* boss_;				// �{�X

	Scene nextScene_;

	float deltaTime_;

	bool isStopped_;

	/*PauseScreen pause_;
	MoveScreen move_;*/
};

#endif
