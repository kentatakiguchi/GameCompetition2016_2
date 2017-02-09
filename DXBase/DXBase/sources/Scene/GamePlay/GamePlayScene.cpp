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
#include <memory>
#include <random>


GamePlayScene::GamePlayScene(SceneDataKeeper* keeper) :nextScene_(Scene::GameOver), isStopped_(false) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "stage00";
	deltaTime_ = 1 / 60.f;
	stageNum_ = 0;
	stageTexs_.push_back(TextureID::STAGE_01_TEX);
	stageTexs_.push_back(TextureID::STAGE_02_TEX);
	stageTexs_.push_back(TextureID::STAGE_03_TEX);
	stageTexs_.push_back(TextureID::STAGE_04_TEX);

	numberTexes_.push_back(TextureID::NUMBER_ZERO_TEX);
	numberTexes_.push_back(TextureID::NUMBER_ONE_TEX);
	numberTexes_.push_back(TextureID::NUMBER_TWO_TEX);
	numberTexes_.push_back(TextureID::NUMBER_THREE_TEX);
	numberTexes_.push_back(TextureID::NUMBER_FOUR_TEX);
	numberTexes_.push_back(TextureID::NUMBER_FIVE_TEX);
	numberTexes_.push_back(TextureID::NUMBER_SIX_TEX);
	numberTexes_.push_back(TextureID::NUMBER_SEVEN_TEX);
	numberTexes_.push_back(TextureID::NUMBER_EIGHT_TEX);
	numberTexes_.push_back(TextureID::NUMBER_NINE_TEX);
}

GamePlayScene::~GamePlayScene() {
}

void GamePlayScene::start() {

	clear_ = ClearScreen(keeper_);
	isClearStage_ = false;

	deltaTime_ = Time::GetInstance().deltaTime();
	stageTime_ = 0.0f;

	isStopped_ = false;

	stageAlpha_ = 0.0f;
	stageTime_ = 0.0f;
	stageFlag_ = true;

	//SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>(keeper_);
	world_->CollisitionOffOn(true);
	MapGenerator gener = MapGenerator(world_.get());
	int stg = keeper_->getNextSceneName(name_);
	if (stg == 0) {
		name_ = "stage01";
		stg = 1;
	}
	world_->SetPlayerPos(gener.findStartPoint("./resources/file/" + name_ + ".csv"));

	//world_->addEventMessageListener(
	//	[=](EventMessage msg, void* param) {
	//	handleMessage(msg, param);
	//}
	//);
	//world_->addField(std::make_shared<Field>("./resources/file/" + name_ + ".csv", 0, 0, stg));
	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), gener.findStartPoint("./resources/file/" + name_ + ".csv")));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<FloorTurnEnemy>(world_.get(), START_POS + Vector2(200, -200)));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<WallTrunEnemy>(world_.get(), Vector2(250, 325)));

	gener.create("./resources/file/" + name_ + ".csv", 0, 0, stg);

	keeper_->setCurrentSceneName(name_);

	Vector2 csvSize = gener.GetCellSize();// Vector2(gener.GetColumnSize(), gener.GetRowSize());
	if (name_ == "stage01") {
		stageNum_ = 1;
		world_->SetScroolJudge(Vector2(1, 1), world_->GetScreenPlayerPos(), Vector2(csvSize.x*CHIPSIZE - SCREEN_SIZE.x / 2, (csvSize.y*CHIPSIZE) + (SCREEN_SIZE.y / 2 - world_->GetScreenPlayerPos().y)));
		
		keeper_->setMaxItemCount(gener.getItemCount(), name_);
	}
	else if (name_ == "stage02") {
		stageNum_ = 2;
		world_->SetScroolJudge(Vector2(1, 1), world_->GetScreenPlayerPos(), Vector2(csvSize.x*CHIPSIZE - SCREEN_SIZE.x / 2, (csvSize.y*CHIPSIZE) + (SCREEN_SIZE.y / 2 - world_->GetScreenPlayerPos().y)));
	
		keeper_->setMaxItemCount(gener.getItemCount(), name_);
	}
	else if (name_ == "stage03") {
		stageNum_ = 3;
		world_->SetScreenPlayerPos(SCREEN_SIZE/2);
		world_->SetScroolJudge(Vector2(1, 1),  world_->GetPlayerPos(),Vector2(csvSize.x*CHIPSIZE - SCREEN_SIZE.x / 2, (csvSize.y*CHIPSIZE) - (SCREEN_SIZE.y / 2)));
	
		keeper_->setMaxItemCount(gener.getItemCount(), name_);
	}
	else if (name_ == "stage04") {
		stageNum_ = 4;
		world_->SetScreenPlayerPos(SCREEN_SIZE / 2);
		world_->SetScroolJudge(Vector2(1, 1), world_->GetScreenPlayerPos(), Vector2(csvSize.x*CHIPSIZE-(SCREEN_SIZE.x-world_->GetScreenPlayerPos().x),csvSize.y*CHIPSIZE-(SCREEN_SIZE.y-world_->GetScreenPlayerPos().y)));
	
		keeper_->setMaxItemCount(gener.getItemCount(), name_);
	}

	backManager = new BackGraundManager(world_.get());
	if (name_ == "stage01" || name_ == "stage02") {
		float graundPos = -(world_->GetScreenPlayerPos().y);
		//先にセットされたテクスチャほど奥に描写される
		//backManager->SetBackGraund(TextureID::BACKSTAGE1_1_TEX, TextureID::BACKSTAGE1_1_TEX,graundPos);
		backManager->BossFlag(true);

		backManager->SetBackGraund(TextureID::BACKSTAGE1_2_TEX, TextureID::BACKSTAGE1_2_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_3_TEX, TextureID::BACKSTAGE1_3_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_4_TEX, TextureID::BACKSTAGE1_4_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_5_TEX, TextureID::BACKSTAGE1_5_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_6_1_TEX, TextureID::BACKSTAGE1_6_1_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_6_1_TEX, TextureID::BACKSTAGE1_6_2_TEX, graundPos);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_7_TEX, TextureID::BACKSTAGE1_7_TEX, graundPos*1.5f);
		backManager->SetBackGraund(TextureID::BACKSTAGE1_8_TEX, TextureID::BACKSTAGE1_8_TEX, graundPos*2.5f, true);

		backManager->AddKonoha(TextureID::HAPPA1_1_TEX);
		backManager->AddKonoha(TextureID::HAPPA1_2_TEX);
		backManager->SetUpBackGraund(TextureID::BACKSTAGE1_1_TEX, 8);

		//backManager->SetUpBackGraund(TextureID::BACKGRAUND_TOP_TEX);
		//backManager->SetDownBackGraund(TextureID::BACKGRAUND_BOT_TEX);
	}
	else if (name_ == "stage03")
	{
		backManager->BossFlag(true);
		float graundPos = csvSize.y*CHIPSIZE-world_->GetScreenPlayerPos().y/2;
		backManager->SetBackGraund(TextureID::BACKSTAGE2_1_TEX, TextureID::BACKSTAGE2_1_TEX, graundPos, false, true);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_2_TEX, TextureID::BACKSTAGE2_2_TEX, graundPos, false, true);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_3_TEX, TextureID::BACKSTAGE2_3_TEX, graundPos, false, true);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_4_TEX, TextureID::BACKSTAGE2_4_TEX, graundPos, false, true);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_5_TEX, TextureID::BACKSTAGE2_5_TEX, graundPos, false, true);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_6_TEX, TextureID::BACKSTAGE2_6_TEX, graundPos, false, true);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_7_TEX, TextureID::BACKSTAGE2_7_TEX, graundPos, false, true);
		backManager->SetBackGraund(TextureID::BACKSTAGE2_8_TEX, TextureID::BACKSTAGE2_8_TEX, graundPos, false, true);
		//backManager->SetBackGraund(TextureID::BACKSTAGE2_9_TEX, TextureID::BACKSTAGE2_9_TEX, graundPos, false, true);
		//backManager->SetBackGraund(TextureID::BACKSTAGE2_10_TEX, TextureID::BACKSTAGE2_10_TEX, graundPos, false, true);
		backManager->SetUpBackGraund(TextureID::BACKSTAGE2_TOP1_TEX, 8);
		backManager->SetUpBackGraund(TextureID::BACKSTAGE2_TOP2_TEX, 4);
		backManager->SetUpBackGraund(TextureID::BACKSTAGE2_TOP3_TEX, 1);

		backManager->AddKonoha(TextureID::HAPPA3_1_TEX);
		backManager->AddKonoha(TextureID::HAPPA3_2_TEX);
	}
	else if (name_ == "stage04")
	{
		backManager->SetBackGraund(TextureID::BACKSTAGE4_1_TEX,TextureID::BACKSTAGE4_1_TEX);
		backManager->SetUpBackGraund(TextureID::BACKSTAGE4_1_TEX,1);
	}
	world_->clear(false);

	if (name_ != "stage04")
	{
		PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_STAGE_123), DX_PLAYTYPE_LOOP);
		//PlaySoundFile("./resources/file/stage1,2,3_BGM.mp3", DX_PLAYTYPE_LOOP);
	}
	else {
		PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_STAGE_4), DX_PLAYTYPE_LOOP);
		//PlaySoundFile("./resources/file/stage4_BGM.mp3", DX_PLAYTYPE_LOOP);
	}

	world_->setCount(keeper_->GetItemCount());
	//keeper_->jumpReset();
	//keeper_->DamageReset();
}

void GamePlayScene::update() {
	//keeper_->addJumpCount(1);
	//world_->keeper_->addDamageCount(1);

	

	if (isClearStage_) {
		if (clear_.update(name_, nextScene_)) {
			isEnd_ = true;
		};
		return;
	}

	if (stageFlag_) {
		stageAlpha_ += Time::GetInstance().deltaTime();
		if (stageAlpha_ >= 1.0f) {
			stageFlag_ = false;
		}
	}
	else
	{
		stageTime_ += Time::GetInstance().deltaTime();
		if (stageTime_ >= 3.0f) stageAlpha_ -= Time::GetInstance().deltaTime();
	}
	stageAlpha_ = MathHelper::Clamp(stageAlpha_, 0.0f, 1.0f);

	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_START)) {
		isStopped_ ? deltaTime_ = Time::GetInstance().deltaTime() : deltaTime_ = 0;
		isStopped_ = !isStopped_;
	}
	world_->update(deltaTime_);

	backManager->Update(deltaTime_);

	auto player = world_->findActor("Player");

	isClearStage_ = world_->is_clear();
	//isEnd_ = player == nullptr || world_->is_clear();

	if (player == nullptr) {
		isEnd_ = true;
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
		isStopped_ ? isEnd_ = pause_.update(nextScene_) : isEnd_ = move_.update(name_, nextScene_, isClearStage_);
		//isStopped_ ? isEnd_ = pause_.update(nextScene_) : isEnd_ = move_.update(name_, nextScene_);
	}
	keeper_->setItemCount(world_->getCount());
}

void GamePlayScene::draw() const {
	backManager->Draw();
	//world描画
	world_->draw();

	int stage = stageNum_ - 1;
	Vector2 size = ResourceLoader::GetInstance().GetTextureSize(stageTexs_[stage]) / 2;
	Vector2 pos = SCREEN_SIZE / 2 - size;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)MathHelper::Lerp(0.f, 255.f, stageAlpha_));
	DrawGraph((int)pos.x, (int)pos.y, ResourceLoader::GetInstance().getTextureID(stageTexs_[stage]), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	backManager->BackDraw();

	if (isClearStage_) {
		clear_.draw();
		return;
	}

	DrawGraph((int)(SCREEN_SIZE.x - CountPos - ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX).x), 50, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), TRUE);

	int drawNum = keeper_->GetItemCount();
	int baseNum = keeper_->GetItemCount();
	int posCount = 0;
	std::vector<int> drawNumberList;

	for (int i = 0;;) {

		if (baseNum < 10) {
			drawNumberList.push_back(baseNum);
			//DrawGraph((SCREEN_SIZE.x - CountPos)
			//	- ResourceLoader::GetInstance().GetTextureSize(numberTexes_[baseNum]).x*posCount, 50, ResourceLoader::GetInstance().getTextureID(numberTexes_[baseNum]), TRUE);
			break;
		}

		drawNum = (int)(baseNum*0.1);
		drawNum = drawNum * 10;
		int textNum = baseNum - drawNum;

		drawNumberList.push_back(textNum);
		//DrawGraph((SCREEN_SIZE.x - CountPos) 
		//	- ResourceLoader::GetInstance().GetTextureSize(numberTexes_[textNum]).x*posCount, 50, ResourceLoader::GetInstance().getTextureID(numberTexes_[textNum]), TRUE);

		baseNum = (int)(baseNum*0.1);
		posCount++;
		//DrawFormatString(SCREEN_SIZE.x - 100, 50, GetColor(0, 0, 0), "%d", );
	}
	int drawPosCount = drawNumberList.size() - 1;
	for (int i = 0; i < (int)drawNumberList.size(); i++) {

		DrawGraph((int)((SCREEN_SIZE.x - CountPos)
			+ ResourceLoader::GetInstance().GetTextureSize(numberTexes_[drawNumberList[i]]).x*drawPosCount), 50, ResourceLoader::GetInstance().getTextureID(numberTexes_[drawNumberList[i]]), TRUE);

		drawPosCount--;
	}

	isStopped_ ? pause_.draw() : move_.draw();
}

void GamePlayScene::end() {
	if (!isClearStage_) {
		world_->minusCount();
		keeper_->setItemCount(world_->getCount());
	}
	world_->resetGetCount();

	delete backManager;
	if (name_ != "stage04")
	{
		StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_STAGE_123));
		//PlaySoundFile("./resources/file/stage1,2,3_BGM.mp3", DX_PLAYTYPE_LOOP);
	}
	else {
		StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_STAGE_4));
		//PlaySoundFile("./resources/file/stage4_BGM.mp3", DX_PLAYTYPE_LOOP);
	}
}

bool GamePlayScene::isEnd() const {

	return isEnd_;
}

Scene GamePlayScene::next() const {
	return nextScene_;
}

