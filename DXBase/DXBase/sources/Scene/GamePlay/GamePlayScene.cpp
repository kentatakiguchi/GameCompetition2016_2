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
	keeper_->getNextSceneName(name_);


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

	gener.create("./resources/file/" + name_ + ".csv");


	status_ = Status(10);

	backManager = new BackGraundManager(world_.get());
	if (name_ != "stage03") {
		//先にセットされたテクスチャほど奥に描写される
		backManager->SetBackGraund(TextureID::BACKGRAUND4_TEX, TextureID::BACKGRAUND42_TEX);
		backManager->SetBackGraund(TextureID::BACKGRAUND3_TEX, TextureID::BACKGRAUND32_TEX);
		backManager->SetBackGraund(TextureID::BACKGRAUND2_TEX, TextureID::BACKGRAUND22_TEX);
		backManager->SetBackGraund(TextureID::BACKGRAUND1_TEX, TextureID::BACKGRAUND12_TEX);

		backManager->SetUpBackGraund(TextureID::BACKGRAUND_TOP_TEX);
		backManager->SetDownBackGraund(TextureID::BACKGRAUND_BOT_TEX);
	}
	else
	{

		backManager->SetTateBackGraund(TextureID::BACKGRAUND_TATE41_TEX, TextureID::BACKGRAUND_TATE41_TEX);
		backManager->SetTateBackGraund(TextureID::BACKGRAUND_TATE31_TEX, TextureID::BACKGRAUND_TATE31_TEX);
		backManager->SetTateBackGraund(TextureID::BACKGRAUND_TATE21_TEX, TextureID::BACKGRAUND_TATE21_TEX);
		backManager->SetTateBackGraund(TextureID::BACKGRAUND_TATE11_TEX, TextureID::BACKGRAUND_TATE11_TEX);
		backManager->SetTateYokoBackGraund(TextureID::BACKGRAUND_TATEYOKO_TEX);
	}

	world_->clear(false);
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

		if (name_ != "stage03")
		{
			nextScene_ = Scene::StageClear;
		}
		else
		{
			nextScene_ = Scene::GameClear;
		}
	}
	if (!isEnd_) {
		isStopped_ ? isEnd_ = pause_.update(nextScene_) : isEnd_ = move_.update(name_, nextScene_);
	}
}

void GamePlayScene::draw() const {
	backManager->Draw();
	//world描画
	world_->draw();

	isStopped_ ? pause_.draw() : move_.draw();

}

void GamePlayScene::end() {
	delete backManager;
}

bool GamePlayScene::isEnd() const {

	return isEnd_;
}

Scene GamePlayScene::next() const {
	return nextScene_;
}

