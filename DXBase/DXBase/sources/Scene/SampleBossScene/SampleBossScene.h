#ifndef SAMPLE_BOSS_SCENE_H_
#define SAMPLE_BOSS_SCENE_H_

#include "../Base/IScene.h"
#include "../../Actor/Person/Player/Status/Status.h"
#include <memory>
#include "../../Math/Math.h"
#include"../GamePlay/PauseScreen.h"
#include"../GamePlay/MoveScreen.h"

class World;
class BackGraundManager;

class SampleBossScene : public IScene {
public:
	SampleBossScene(SceneDataKeeper* keeper);
	~SampleBossScene();
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

	Status status_;

	BackGraundManager* backManager;

	Scene nextScene_;

	float deltaTime_;

	bool isStopped_;

	PauseScreen pause_;
	MoveScreen move_;
};

#endif
