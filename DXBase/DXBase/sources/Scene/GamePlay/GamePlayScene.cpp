#include "GamePlayScene.h"
#include "../../World/World.h"
#include "../../Actor/Camera/Camera.h"
#include "../../Actor/Light/Light.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
//#include "../../Actor/Person/Enemy/Enemy.h"
//#include "../../Actor/Person/Enemy/EnemySpawner.h"
#include "../../ResourceLoader/ResourceLoader.h"

#include "../../Actor/Person/Enemy/Enemys/FloorTurnEnemy.h"
#include "../../Actor/Person/Enemy/Enemys/WallTurnEnemy.h"
#include "../../Field/MapGenerator.h"
#include "../../Actor/BackGraundManager/BackGraundManager.h"
#include "../../Actor/TestPlayer/TestPlayer.h"
#include <memory>
#include <random>


GamePlayScene::GamePlayScene(SceneDataKeeper* keeper) :nextScene_(Scene::GameOver), isStopped_(false) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "stage00";
	deltaTime_ = 1 / 60.f;

}

GamePlayScene::~GamePlayScene() {
}

void GamePlayScene::start() {

	deltaTime_ = Time::GetInstance().deltaTime();
	isStopped_ = false;
	//SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();

	MapGenerator gener = MapGenerator(world_.get());
	int stg=keeper_->getNextSceneName(name_);


	//world_->addEventMessageListener(
	//	[=](EventMessage msg, void* param) {
	//	handleMessage(msg, param);
	//}
	//);
	//world_->addField(std::make_shared<Field>(ResourceLoader::GetInstance().getModelID(ModelID::STAGE), ResourceLoader::GetInstance().getModelID(ModelID::STAGE_COLL), ResourceLoader::GetInstance().getModelID(ModelID::SKYDOME)));
	world_->addCamera(std::make_shared<Camera>(world_.get()));
	world_->addLight(std::make_shared<Light>(world_.get(), Vector2(10.0f, 10.0f)));
	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), gener.findStartPoint("./resources/file/" + name_ + ".csv")));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<FloorTurnEnemy>(world_.get(), START_POS + Vector2(200, -200)));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<WallTrunEnemy>(world_.get(), Vector2(250, 325)));

	gener.create("./resources/file/" + name_ + ".csv",0,0,stg);


	status_ = Status(10);

	backManager = new BackGraundManager(world_.get());
	if (name_ != "stage03") {
		if(name_=="stage01")
		world_->SetScroolJudge(Vector2(1, 0),Vector2(9408 - SCREEN_SIZE.x / 2, 0));
		else
		world_->SetScroolJudge(Vector2(1, 1), Vector2(4416 - SCREEN_SIZE.x / 2, SCREEN_SIZE.y*10.0f));
		//先にセットされたテクスチャほど奥に描写される
		backManager->SetBackGraund(TextureID::BACKSTAGE1_1_TEX, TextureID::BACKSTAGE1_1_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_2_1_TEX, TextureID::BACKSTAGE1_2_2_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_3_1_TEX, TextureID::BACKSTAGE1_3_2_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_4_TEX, TextureID::BACKSTAGE1_4_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_5_TEX, TextureID::BACKSTAGE1_5_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_6_TEX, TextureID::BACKSTAGE1_6_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_7_TEX, TextureID::BACKSTAGE1_7_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_8_1_TEX, TextureID::BACKSTAGE1_8_2_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_9_TEX, TextureID::BACKSTAGE1_9_TEX,true);

		//backManager->SetUpBackGraund(TextureID::BACKGRAUND_TOP_TEX);
		//backManager->SetDownBackGraund(TextureID::BACKGRAUND_BOT_TEX);
	}
	else
	{
		world_->SetScroolJudge(Vector2(0, 1), Vector2(0, SCREEN_SIZE.y*10.0f));
		backManager->SetTateBackGraund(TextureID::BACKGRAUND_TATE41_TEX, TextureID::BACKGRAUND_TATE41_TEX);
		backManager->SetTateBackGraund(TextureID::BACKGRAUND_TATE31_TEX, TextureID::BACKGRAUND_TATE31_TEX);
		backManager->SetTateBackGraund(TextureID::BACKGRAUND_TATE21_TEX, TextureID::BACKGRAUND_TATE21_TEX);
		backManager->SetTateBackGraund(TextureID::BACKGRAUND_TATE11_TEX, TextureID::BACKGRAUND_TATE11_TEX);
		backManager->SetTateYokoBackGraund(TextureID::BACKGRAUND_TATEYOKO_TEX);
	}

	world_->clear(false);

	if (name_ != "stage04")
	{
		PlaySoundFile("./resources/file/stage1,2,3_BGM.mp3", DX_PLAYTYPE_LOOP);

	}
	else {
		PlaySoundFile("./resources/file/stage4_BGM.mp3", DX_PLAYTYPE_LOOP);

	}
}

void GamePlayScene::update() {

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::T)) {
		isStopped_ ? deltaTime_ = Time::GetInstance().deltaTime() : deltaTime_ = 0;
		isStopped_ = !isStopped_;
	}
	world_->update(deltaTime_);
	if (name_ == "stage03")
		backManager->TateUpdate(deltaTime_);
	else
		backManager->Update(deltaTime_);

	auto player = world_->findActor("Player");
	isEnd_ = player == nullptr || world_->is_clear();
	if (player == nullptr) {
		nextScene_ = Scene::GameOver;
	}

	if (world_->is_clear()) {

		//if (name_ != "stage04")
		//{
			nextScene_ = Scene::StageClear;
		//}
		//else
		//{
		//	nextScene_ = Scene::GameClear;
		//}
	}
	if (!isEnd_) {
		isStopped_ ? isEnd_ = pause_.update(nextScene_) : isEnd_ = move_.update(name_, nextScene_);
	}
}

void GamePlayScene::draw() const {
	backManager->Draw();
	//world描画
	world_->draw();
	backManager->BackDraw();
	isStopped_ ? pause_.draw() : move_.draw();

}

void GamePlayScene::end() {
	delete backManager; 
	StopSoundFile();
}

bool GamePlayScene::isEnd() const {

	return isEnd_;
}

Scene GamePlayScene::next() const {
	return nextScene_;
}

