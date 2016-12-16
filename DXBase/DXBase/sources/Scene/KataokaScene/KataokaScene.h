#ifndef _KATAOKA_SCENE_H_
#define _KATAOKA_SCENE_H_

#include "../Base/IScene.h"
#include <memory>
#include "../../Math/Math.h"
#include"../GamePlay/PauseScreen.h"
#include"../GamePlay/MoveScreen.h"
class World;

class KataokaScene : public IScene {
public:
	KataokaScene(SceneDataKeeper* keeper);
	~KataokaScene();
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

	//BaseBoss* boss_;				// ボス

	Scene nextScene_;

	float deltaTime_;

	bool isStopped_;

	float mIvemtTime;



	PauseScreen pause_;
	MoveScreen move_;
};

#endif