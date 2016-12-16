#include "BossStage.h"
#include "../../World/World.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../Actor/Person/Enemy/ImportEnemys.h"

#include "../../Field/MapGenerator.h"
#include "../../ResourceLoader/ResourceLoader.h"
#include "../../Actor/BackGraundManager/BackGraundManager.h"

//const Vector2 START_POS = Vector2(300, 900);

BossStage::BossStage(SceneDataKeeper* keeper) :
	nextScene_(Scene::GameOver),
	isStopped_(false){
	//boss_(nullptr){
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "bossStage01";
	deltaTime_ = 1 / 60.f;
}

BossStage::~BossStage()
{
}

void BossStage::start() {

	deltaTime_ = Time::GetInstance().deltaTime();
	isStopped_ = false;
	SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();

	world_->SetScroolJudge(Vector2(1, 1), Vector2(3000, 8000));
	MapGenerator gener = MapGenerator(world_.get());
	//keeper_->getNextSceneName(name_);

	//world_->addEventMessageListener(
	//	[=](EventMessage msg, void* param) {
	//	handleMessage(msg, param);
	//}
	//);
	//world_->addField(std::make_shared<Field>(ResourceLoader::GetInstance().getModelID(ModelID::STAGE), ResourceLoader::GetInstance().getModelID(ModelID::STAGE_COLL), ResourceLoader::GetInstance().getModelID(ModelID::SKYDOME)));
	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), 
		gener.findStartPoint("./resources/file/" + name_ + ".csv")));
	//プレイヤーのスタート位置を設定
	world_->SetPlayerPos(gener.findStartPoint("./resources/file/" + name_ + ".csv"));
	/*auto boss = std::make_shared<BaseBoss>(
		world_.get(), Vector2(1000, 200), 128.0f / 2.0f);
	world_->addActor(ActorGroup::Enemy, boss);
	boss_ = boss.get();*/

	gener.create("./resources/file/" + name_ + ".csv");
	//gener.create("./resources/file/boss01/boss01BodyStage01.csv", 1, 15);
	world_->SetScroolJudge(Vector2(0, 0), Vector2(99999, 99999));
	backManager = new BackGraundManager(world_.get());
	//先にセットされたテクスチャほど奥に描写される
	//backManager->SetBackGraund(TextureID::BACKGRAUND4_TEX);
	//backManager->SetBackGraund(TextureID::BACKGRAUND3_TEX);
	//backManager->SetBackGraund(TextureID::BACKGRAUND2_TEX);
	//backManager->SetBackGraund(TextureID::BACKGRAUND1_TEX);
	backManager->SetBackGraund(TextureID::BACKSTAGE4_1_TEX, TextureID::BACKSTAGE4_1_TEX);
	backManager->SetBackGraund(TextureID::BACKSTAGE4_2_TEX, TextureID::BACKSTAGE4_2_TEX);
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_STAGE_5), DX_PLAYTYPE_LOOP);

	world_->clear(false);
}

void BossStage::update() {

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::T)) {
		isStopped_ ? deltaTime_ = Time::GetInstance().deltaTime() : deltaTime_ = 0;
		isStopped_ = !isStopped_;
	}
	world_->update(deltaTime_);
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

void BossStage::draw() const {
	backManager->Draw();
	//world描画
	world_->draw();

	isStopped_ ? pause_.draw() : move_.draw();

}

void BossStage::end() {
	StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_STAGE_5));
}

bool BossStage::isEnd() const {

	return isEnd_;
}

Scene BossStage::next() const {
	return nextScene_;
}
