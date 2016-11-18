#include "BossStage.h"
#include "../../World/World.h"
#include "../../Actor/Camera/Camera.h"
#include "../../Actor/Light/Light.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../Actor/Person/Enemy/ImportEnemys.h"

#include "../../Field/MapGenerator.h"
#include "../../ResourceLoader/ResourceLoader.h"
#include "../../Actor/BackGraundManager/BackGraundManager.h"

//const Vector2 START_POS = Vector2(300, 900);

BossStage::BossStage(SceneDataKeeper* keeper) : 
	nextScene_(Scene::Title), 
	isStopped_(false),
	boss_(nullptr){
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "bossStage01";
	deltaTime_ = 1 / 60.f;
}

BossStage::~BossStage()
{
}

void BossStage::start()
{
	deltaTime_ = Time::GetInstance().deltaTime();
	isStopped_ = false;
	SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();

	world_ = std::make_shared<World>();
	world_->addField(std::make_shared<Field>(ResourceLoader::GetInstance().getModelID(ModelID::STAGE), ResourceLoader::GetInstance().getModelID(ModelID::STAGE_COLL), ResourceLoader::GetInstance().getModelID(ModelID::SKYDOME)));
	//world_->addCamera(std::make_shared<Camera>(world_.get()));
	world_->addLight(std::make_shared<Light>(world_.get(), Vector2(10.0f, 10.0f)));
	/*world_->addActor(
		ActorGroup::Player,
		std::make_shared<Player>(world_.get(), START_POS));*/
	// ボス
	auto boss = std::make_shared<BaseBoss>(
		world_.get(), START_POS + Vector2(1000, 50), 128.0f / 2.0f);
	world_->addActor(ActorGroup::Enemy, boss);
	boss_ = boss.get();

	MapGenerator gener = MapGenerator(world_.get());
	/*keeper_->getNextSceneName(name_);
	auto csvName = "resources/file/" + name_ + ".csv";*/
	gener.create("resources/file/bossStage01.csv");

	// status_ = Status(10);

	backManager = new BackGraundManager(world_.get());
	//先にセットされたテクスチャほど奥に描写される
	backManager->SetBackGraund(TextureID::BACKGRAUND4_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND3_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND2_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND1_TEX);

	backManager->SetUpBackGraund(TextureID::BACKGRAUND_TOP_TEX);
	backManager->SetDownBackGraund(TextureID::BACKGRAUND_BOT_TEX);
}

void BossStage::update()
{
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::T)) {
		isStopped_ ? deltaTime_ = Time::GetInstance().deltaTime() : deltaTime_ = 0;
		isStopped_ = !isStopped_;
	}
	world_->update(deltaTime_);
	backManager->Update(deltaTime_);

	if (boss_->isSceneEnd()) {
		isEnd_ = true;
		return;
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::RETURN)) isEnd_ = true;
	// isStopped_ ? isEnd_ = pause_.update(nextScene_) : isEnd_ = move_.update(name_, nextScene_);
}

void BossStage::draw() const
{
	backManager->Draw();
	world_->draw();

	// isStopped_ ? pause_.draw() : move_.draw();
}

void BossStage::end()
{
}

bool BossStage::isEnd() const
{
	return isEnd_;
}

Scene BossStage::next() const
{
	return nextScene_;
}
