#include "BonusStage.h"
#include "../../World/World.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../ResourceLoader/ResourceLoader.h"
#include "../../Field/MapGenerator.h"
#include "../../Actor/BackGraundManager/BackGraundManager.h"
#include "../../Renderer/NumberTexture.h"
#include "../../Input/InputMgr.h"
BonusStage::BonusStage(SceneDataKeeper * keeper)
{
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "tutoreal01";

}

BonusStage::~BonusStage()
{
}

void BonusStage::start()
{
	keeper_->setCurrentSceneName(name_);
	isResult_ = false;
	pointDrawFlag_ = false;
	drawPoint_ = 0;
	resultAlpha_ = 0.0f;
	point_ = 0;
	pointCount_ = 0;
	pointRandomTime_ = 0.0f;
	pointDrawTime_ = 0.0f;
	scaleNum = 1;
	nextScene_ = Scene::MainMenu;
	world_ = std::make_shared<World>(keeper_);
	world_->CollisitionOffOn(true);
	MapGenerator gener = MapGenerator(world_.get());
	int stg = keeper_->getNextSceneName(name_);
	name_ = "clear_stage";
	gener.create("./resources/file/" + name_ + ".csv", 0, 0, stg);
	Vector2 csvSize = gener.GetCellSize();// Vector2(gener.GetColumnSize(), gener.GetRowSize());
	world_->SetScroolJudge(Vector2(1, 1), world_->GetScreenPlayerPos(), Vector2(csvSize.x*CHIPSIZE - SCREEN_SIZE.x / 2, (csvSize.y*CHIPSIZE) + (SCREEN_SIZE.y / 2 - world_->GetScreenPlayerPos().y)));
	world_->SetPlayerPos(gener.findStartPoint("./resources/file/" + name_ + ".csv"));

	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), gener.findStartPoint("./resources/file/" + name_ + ".csv")));

	creditSize_ = ResourceLoader::GetInstance().GetTextureSize(TextureID::CREDIT_TEX);


	creditPos_ = Vector2(0.0f, creditSize_.y);
	//”wŒiÝ’è
	float graundPos = -(world_->GetScreenPlayerPos().y);
	backManager = new BackGraundManager(world_.get());
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

	kiriTexSize_ = ResourceLoader::GetInstance().GetTextureSize(TextureID::KIRIKABU_TEX);

	keeper_->addMaxItemCount(gener.getItemCount(), name_);
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_MENU), DX_PLAYTYPE_LOOP);

}

void BonusStage::update()
{
	if (!isResult_)
		creditPos_.y -= 400.0f*Time::GetInstance().deltaTime();
	else {
		if (!pointDrawFlag_) {
			point_ = keeper_->GetItemCount("All")+ world_->getCount();
			int pointLeng = std::to_string(point_).length();
			int num = 1;
			for (int i = 0; i < pointLeng; i++) {
				points_.push_back(point_ / num % 10);
				num *= 10;
			}
			//PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_ROLL), DX_PLAYTYPE_LOOP);
			pointDrawFlag_ = true;
		}
		else {
			resultAlpha_ += Time::GetInstance().deltaTime();
			pointDrawTime_ += Time::GetInstance().deltaTime();
			pointRandomTime_ += Time::GetInstance().deltaTime();
			if (pointDrawTime_ >= 1.5f&&points_.size()>pointCount_&&pointRandomTime_ >= 4.0f) {
				pointDrawTime_ = 0.0f;
				PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_SHOWMAX), DX_PLAYTYPE_BACK);
				pointCount_++;
				if (points_.size() - 1 >= pointCount_) StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_ROLL));
			}
		}
	}
	if (resultAlpha_ >= 13.0f) {
		isEnd_ = true;
	}
	if (creditPos_.y <= -creditSize_.y) {
		isResult_ = true;
		world_->PlayerNotMove(true);
	}
	
	world_->update(Time::GetInstance().deltaTime());
	backManager->Update(Time::GetInstance().deltaTime());
}

void BonusStage::draw() const
{
	backManager->Draw();
	//world•`‰æ
	world_->draw();

	backManager->BackDraw();
	if (!isResult_)
		DrawGraph(creditPos_.x, creditPos_.y, ResourceLoader::GetInstance().getTextureID(TextureID::CREDIT_TEX), TRUE);
	if (isResult_) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, MathHelper::Lerp(0.0f, 255.0f, resultAlpha_));
		//DrawGraph(0, 0, ResourceLoader::GetInstance().getTextureID(TextureID::RESULT_BACL_TEX), true);
		//NumberTexture bonus = NumberTexture(TextureID::NUMBERS_TEX, 96, 96);
		//bonus.draw2(Vector2(SCREEN_SIZE.x / 2 - 182, SCREEN_SIZE.y / 2 + 128), bonusPoint_, 4, Vector3(255, 255, 255));
		NumberTexture all = NumberTexture(TextureID::NUMBERS_TEX, 96, 96);
		int size = 4;
		for (int i = 0; i < size - pointCount_; i++) {
			Vector2 pos = Vector2(SCREEN_SIZE.x / 2 - 192, SCREEN_SIZE.y / 2) + Vector2(96 * i, 0);
			if (points_.size() - 1 >= pointCount_)
				all.draw2(pos, GetRand(9), 1, Vector3(255, 255, 255));
			else
				all.draw2(pos, 0, 1, Vector3(255, 255, 255));
		}
		for (int i = 0; i < pointCount_; i++) {
			Vector2 pos = Vector2(SCREEN_SIZE.x / 2 - 192, SCREEN_SIZE.y / 2) + Vector2(96 * ((size - i) - 1), 0);
			all.draw2(pos, points_[i], 1, Vector3(255, 255, 255), 1.0f);
		}
		Vector2 sizetext = Vector2(SCREEN_SIZE.x / 2 - 192 - 96, SCREEN_SIZE.y / 2);
		DrawGraph(sizetext.x, sizetext.y, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), true);
		//DrawGraph(300, 900, ResourceLoader::GetInstance().getTextureID(TextureID::KIRIKABU_TEX), true);
		//DrawGraph(SCREEN_SIZE.x -kiriTexSize_.x- 300, 900, ResourceLoader::GetInstance().getTextureID(TextureID::KIRIKABU_TEX), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void BonusStage::end()
{
	StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_MENU));
}

bool BonusStage::isEnd() const
{
	return isEnd_;
}

Scene BonusStage::next() const
{
	return nextScene_;
}
