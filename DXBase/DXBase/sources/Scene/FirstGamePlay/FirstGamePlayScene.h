#pragma once

#include "../Base/IScene.h"
#include <memory>
#include "../../Math/Math.h"
#include"../GamePlay/PauseScreen.h"
#include"../GamePlay/MoveScreen.h"
#include "../../ResourceLoader/ResourceLoader.h"
#include"../GamePlay/ClearScreen.h"

class World;
class BackGraundManager;
class FirstGamePlayScene : public IScene {
public:
	FirstGamePlayScene(SceneDataKeeper* keeper);
	~FirstGamePlayScene();
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

	BackGraundManager* backManager;

	Scene nextScene_;

	float deltaTime_;

	bool isStopped_;

	bool isClearStage_;

	PauseScreen pause_;
	MoveScreen move_;
	ClearScreen clear_;

	//�X�e�[�W�Љ�̃�
	float stageAlpha_;
	float stageTime_;
	bool stageFlag_;
	std::vector<TextureID> numberTexes_;
};
