#include "KataokaScene.h"
#include "../../World/World.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../Actor/Person/Enemy/ImportEnemys.h"
#include "../../Actor/Door/Door.h"
#include "../../Field/MapGenerator.h"
#include "../../ResourceLoader/ResourceLoader.h"
#include "../../Actor/BackGraundManager/BackGraundManager.h"
#include "../../Actor/Person/Player/PlayerBody.h"

#include "../../Actor/Person/Enemy/Bosses/BaseBoss.h"

KataokaScene::KataokaScene(SceneDataKeeper* keeper):
nextScene_(Scene::GameOver),
isStopped_(false) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "test";
	deltaTime_ = 1 / 60.f;
	mIvemtTime = 0.0f;
}

KataokaScene::~KataokaScene()
{
}

void KataokaScene::start()
{

	deltaTime_ = Time::GetInstance().deltaTime();
	isStopped_ = false;
	SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();

	MapGenerator gener = MapGenerator(world_.get());

	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(),
		gener.findStartPoint("./resources/file/" + name_ + ".csv")));
	//プレイヤーのスタート位置を設定
	world_->SetPlayerPos(gener.findStartPoint("./resources/file/" + name_ + ".csv"));

	gener.create("./resources/file/" + name_ + ".csv");

	world_->SetScroolJudge(Vector2(1), Vector2::Zero, Vector2(10000, 10000));
	world_->CollisitionOffOn(true);

	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_STAGE_5), DX_PLAYTYPE_LOOP);
}

void KataokaScene::update()
{
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::T)) {
		isStopped_ ? deltaTime_ = Time::GetInstance().deltaTime() : deltaTime_ = 0;
		isStopped_ = !isStopped_;
	}
	world_->update(deltaTime_);

	auto player = world_->findActor("Player");
	isEnd_ = player == nullptr || world_->is_clear();
	if (player == nullptr) {
		nextScene_ = Scene::GameOver;
	}

	if (!isEnd_) {
		isStopped_ ? isEnd_ = pause_.update(nextScene_) : isEnd_ = move_.update(name_, nextScene_);
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::RETURN)) isEnd_ = true;
}

void KataokaScene::draw() const
{
	world_->draw();
	isStopped_ ? pause_.draw() : move_.draw();
}

void KataokaScene::end()
{

}

bool KataokaScene::isEnd() const
{
	return isEnd_;
}

Scene KataokaScene::next() const
{
	return Scene::Kataoka;
}
