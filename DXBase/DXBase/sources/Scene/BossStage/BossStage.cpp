#include "BossStage.h"
#include "../../World/World.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../Actor/Person/Enemy/Bosses/BaseBoss.h"

#include "../../Field/MapGenerator.h"
#include "../../ResourceLoader/ResourceLoader.h"
#include "../../Actor/BackGraundManager/BackGraundManager.h"

#include "../../Input/InputMgr.h"
#include "../../Actor/Person/Player/PlayerBody.h"

//const Vector2 START_POS = Vector2(300, 900);

BossStage::BossStage(SceneDataKeeper* keeper) :
	nextScene_(Scene::GameOver),
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

void BossStage::start() {
	mIvemtTime = 0.0f;

	deltaTime_ = Time::GetInstance().deltaTime();
	isStopped_ = false;
	SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();

	world_->SetScroolJudge(Vector2(1, 1),Vector2::Zero, Vector2(3000, 8000));
	MapGenerator gener = MapGenerator(world_.get());

	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(),
		gener.findStartPoint("./resources/file/" + name_ + ".csv") - Vector2(400, 0)));
	//プレイヤーのスタート位置を設定
	world_->SetPlayerPos(gener.findStartPoint("./resources/file/" + name_ + ".csv") - Vector2(400, 0));


	// ボスの取得
	auto boss = std::make_shared<BaseBoss>(
		world_.get(), Vector2(CHIPSIZE * 16 + 50, -150.0f));
	world_->addActor(ActorGroup::Enemy, boss);

	gener.create("./resources/file/" + name_ + ".csv");


	boss_ = boss.get();

	// ボスの位置を設定
	boss_->setMovePosition(Vector2(CHIPSIZE * 16 + 50, -150.0f), 0.0f);
	world_->SetScroolJudge(Vector2(0, 0),Vector2::Zero, Vector2(99999, 99999));


	//gener.create("./resources/file/boss01/boss01BodyStage01.csv", 1, 15);
	backManager = new BackGraundManager(world_.get());
	//先にセットされたテクスチャほど奥に描写される
	//backManager->SetBackGraund(TextureID::BACKGRAUND4_TEX);
	//backManager->SetBackGraund(TextureID::BACKGRAUND3_TEX);
	//backManager->SetBackGraund(TextureID::BACKGRAUND2_TEX);
	//backManager->SetBackGraund(TextureID::BACKGRAUND1_TEX);
	backManager->SetBackGraund(TextureID::BACKSTAGE4_1_TEX, TextureID::BACKSTAGE4_1_TEX);
	backManager->SetBackGraund(TextureID::BACKSTAGE4_2_TEX, TextureID::BACKSTAGE4_2_TEX);
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_STAGE_5), DX_PLAYTYPE_LOOP);

	door_ = dynamic_cast<Door*>(world_->findActor("Door").get());

	world_->PlayerNotMove(true);
	world_->CollisitionOffOn(false);
	world_->clear(false);
	door_->DoorOpen(true);

	hatenaAnm_.add_anim(0, ResourceLoader::GetInstance().getAnimationIDs(AnimationID::HATENA));
	hatenaAnm_.change_param(0, 0.0f);
}

void BossStage::update() {

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::T)) {
		isStopped_ ? deltaTime_ = Time::GetInstance().deltaTime() : deltaTime_ = 0;
		isStopped_ = !isStopped_;
	}
	//イベント関係
	if (!isStopped_) {
		mIvemtTime += deltaTime_;
		if (mIvemtTime <= 7.0f) {
			dynamic_cast<PlayerBody*>(world_->findActor("PlayerBody1").get())->ForcedMove(Vector2(150.0f, 0.0f));
			dynamic_cast<PlayerBody*>(world_->findActor("PlayerBody2").get())->ForcedMove(Vector2(150.0f, 0.0f));
		}
		else if (mIvemtTime > 7.0f&&mIvemtTime <= 8) {
			hatenaAnm_.change_param(0, 1.0f);
		}
		else if (mIvemtTime >= 9.0f&&mIvemtTime <= 15.0f) {
			boss_->setMovePosition(Vector2(CHIPSIZE * 16 + 50, CHIPSIZE * 8 - 5), 4.0f);
		}
		else if (boss_->isMovePosition() && mIvemtTime >= 15.0f) {
			boss_->setIsBattle(true);
			world_->PlayerNotMove(false);
			world_->CollisitionOffOn(true);
			door_->DoorOpen(false);
		}
	}

	if (hatenaAnm_.end_anim()) hatenaAnm_.change_param(0, 0.0f);

	world_->update(deltaTime_);
	backManager->Update(deltaTime_);
	hatenaAnm_.update(deltaTime_);


	// ボスが死亡したら、クリアする
	if (boss_->isSceneEnd())
		world_->clear(true);

	player = world_->findActor("Player");
	isEnd_ = player == nullptr || world_->is_clear();
	if (player == nullptr) {
		nextScene_ = Scene::GameOver;
	}

	if (world_->is_clear()) {

		//if (name_ != "stage03")
		//{
		//	nextScene_ = Scene::StageClear;
		//}
		//else
		//{
			nextScene_ = Scene::GameClear;
		//}
	}
	if (!isEnd_) {
		isStopped_ ? isEnd_ = pause_.update(nextScene_) : isEnd_ = move_.update(name_, nextScene_);
	}

}

void BossStage::draw() const {
	backManager->Draw();
	//world描画
	world_->draw();
	// プレイヤーが消えてら返す
	if (player == nullptr) return;
	Vector2 pos = player->getPosition()-Vector2(0,256+128);
	hatenaAnm_.draw(pos,Vector2::Zero,Vector2(0.7,0.7),0);
	isStopped_ ? pause_.draw() : move_.draw();

}

void BossStage::end() {
	StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_STAGE_5));
	boss_->onEnd();
	boss_->dead();
	boss_ = nullptr;
}

bool BossStage::isEnd() const {

	return isEnd_;
}

Scene BossStage::next() const {
	return nextScene_;
}
