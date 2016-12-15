#include "SampleBossScene.h"
#include "../../World/World.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../Actor/Person/Enemy/ImportEnemys.h"
#include "../../Actor/Person/Enemy/Bosses/SampleBoss.h"

#include "../../Field/MapGenerator.h"
#include "../../ResourceLoader/ResourceLoader.h"
#include "../../Actor/BackGraundManager/BackGraundManager.h"

SampleBossScene::SampleBossScene(SceneDataKeeper * keeper) :
	nextScene_(Scene::GameOver),
	isStopped_(false) {
	//boss_(nullptr){
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "sampleBossStage";
	deltaTime_ = 1 / 60.f;
}

SampleBossScene::~SampleBossScene()
{}

void SampleBossScene::start()
{
	deltaTime_ = Time::GetInstance().deltaTime();
	isStopped_ = false;
	SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();

	MapGenerator gener = MapGenerator(world_.get());

	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(),
		gener.findStartPoint("./resources/file/" + name_ + ".csv")));
	// サンプルボスの追加
	auto boss = std::make_shared<SampleBoss>(world_.get(), Vector2(1000, 600));
	world_->addActor(ActorGroup::Enemy, boss);

	gener.create("./resources/file/" + name_ + ".csv");
	//gener.create("./resources/file/boss01/boss01BodyStage01.csv", 1, 15);

	backManager = new BackGraundManager(world_.get());
	//先にセットされたテクスチャほど奥に描写される
	//backManager->SetUpBackGraund(TextureID::BACKGRAUND_TOP_TEX);
	//backManager->SetDownBackGraund(TextureID::BACKGRAUND_BOT_TEX);

	world_->clear(false);
}

void SampleBossScene::update()
{
	if(InputMgr::GetInstance().IsKeyDown(KeyCode::T)) {
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

void SampleBossScene::draw() const
{
	backManager->Draw();
	//world描画
	world_->draw();

	isStopped_ ? pause_.draw() : move_.draw();
}

void SampleBossScene::end()
{
}

bool SampleBossScene::isEnd() const
{
	return isEnd_;
}

Scene SampleBossScene::next() const
{
	return nextScene_;
}
