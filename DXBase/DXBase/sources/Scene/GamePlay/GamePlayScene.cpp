#include "GamePlayScene.h"
#include "../../World/World.h"
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
	world_->SetPlayerPos(gener.findStartPoint("./resources/file/" + name_ + ".csv"));

	//world_->addEventMessageListener(
	//	[=](EventMessage msg, void* param) {
	//	handleMessage(msg, param);
	//}
	//);
	//world_->addField(std::make_shared<Field>(ResourceLoader::GetInstance().getModelID(ModelID::STAGE), ResourceLoader::GetInstance().getModelID(ModelID::STAGE_COLL), ResourceLoader::GetInstance().getModelID(ModelID::SKYDOME)));
	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), gener.findStartPoint("./resources/file/" + name_ + ".csv")));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<FloorTurnEnemy>(world_.get(), START_POS + Vector2(200, -200)));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<WallTrunEnemy>(world_.get(), Vector2(250, 325)));

	gener.create("./resources/file/" + name_ + ".csv",0,0,stg);



	Vector2 csvSize = Vector2(gener.GetColumnSize(), gener.GetRowSize());
	if (name_ == "stage01")
		world_->SetScroolJudge(Vector2(1, 0), Vector2(csvSize.x*CHIPSIZE - SCREEN_SIZE.x / 2, 1000.0f));
	else if (name_ == "stage02")
		world_->SetScroolJudge(Vector2(1, 1), Vector2(csvSize.x*CHIPSIZE - SCREEN_SIZE.x / 2, csvSize.y*CHIPSIZE + SCREEN_SIZE.y / 2.0f));
	else if (name_ == "stage03")
		world_->SetScroolJudge(Vector2(0, 1), Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y*100.0f));
	else if (name_ == "stage04")
		world_->SetScroolJudge(Vector2(1, 1), Vector2(99999, 99999));
	else if (name_ == "test")
		world_->SetScroolJudge(Vector2(1, 1), Vector2(99999, 99999));
	status_ = Status(10);

	backManager = new BackGraundManager(world_.get());
	if (name_ == "stage01") {
		//先にセットされたテクスチャほど奥に描写される
		backManager->SetBackGraund(TextureID::BACKSTAGE1_1_TEX, TextureID::BACKSTAGE1_1_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_2_1_TEX, TextureID::BACKSTAGE1_2_2_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_3_1_TEX, TextureID::BACKSTAGE1_3_2_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_4_TEX, TextureID::BACKSTAGE1_4_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_5_TEX, TextureID::BACKSTAGE1_5_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_6_TEX, TextureID::BACKSTAGE1_6_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_7_TEX, TextureID::BACKSTAGE1_7_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_8_1_TEX, TextureID::BACKSTAGE1_8_2_TEX);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_9_TEX, TextureID::BACKSTAGE1_9_TEX, true);

		//backManager->SetUpBackGraund(TextureID::BACKGRAUND_TOP_TEX);
		//backManager->SetDownBackGraund(TextureID::BACKGRAUND_BOT_TEX);
	}
	else if (name_ == "stage02")
	{
		float graundPos = csvSize.y*CHIPSIZE - SCREEN_SIZE.y;
		backManager->SetBackGraund(TextureID::BACKSTAGE2_1_TEX, TextureID::BACKSTAGE2_1_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_2_TEX, TextureID::BACKSTAGE2_2_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_3_TEX, TextureID::BACKSTAGE2_3_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_4_TEX, TextureID::BACKSTAGE2_4_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_5_TEX, TextureID::BACKSTAGE2_5_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_6_TEX, TextureID::BACKSTAGE2_6_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_7_TEX, TextureID::BACKSTAGE2_7_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_8_TEX, TextureID::BACKSTAGE2_8_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_9_TEX, TextureID::BACKSTAGE2_9_TEX, graundPos);
		backManager->SetUpBackGraund(TextureID::BACKSTAGE2_TOP_TEX, 2);
	}
	else if (name_ == "stage03")
	{
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

