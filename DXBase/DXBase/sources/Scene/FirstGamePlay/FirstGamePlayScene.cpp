#include "FirstGamePlayScene.h"
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


FirstGamePlayScene::FirstGamePlayScene(SceneDataKeeper* keeper) :nextScene_(Scene::GameOver), isStopped_(false) {
	isEnd_ = false;
	keeper_ = keeper;
	//name_��csv�t�@�C�����ƍ��킹�鎖
	name_ = "stage00";
	deltaTime_ = 1 / 60.f;

	//�l�̕\�����s��
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

FirstGamePlayScene::~FirstGamePlayScene() {
}

void FirstGamePlayScene::start() {
	//�N���A���̕\���p�N���X
	clear_ = ClearScreen(keeper_);
	isClearStage_ = false;

	deltaTime_ = Time::GetInstance().deltaTime();
	stageTime_ = 0.0f;

	//Pause���ǂ����𔻕ʂ���
	isStopped_ = false;

	stageAlpha_ = 0.0f;
	stageTime_ = 0.0f;
	stageFlag_ = true;

	//SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>(keeper_);
	world_->CollisitionOffOn(true);
	MapGenerator gener = MapGenerator(world_.get());

	//csv�̃t�@�C������name�����킹�鎖
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

	gener.create("./resources/file/" + name_ + ".csv", 0, 0);

	//scenedatakeeper�ɂ��̃X�e�[�W�̖��O��n��
	keeper_->setCurrentSceneName(name_);

	Vector2 csvSize = gener.GetCellSize();// Vector2(gener.GetColumnSize(), gener.GetRowSize());
	world_->SetScreenPlayerPos(SCREEN_SIZE / 2);
	world_->SetScroolJudge(Vector2(1, 1), world_->GetScreenPlayerPos(), Vector2(csvSize.x*CHIPSIZE - (SCREEN_SIZE.x - world_->GetScreenPlayerPos().x), csvSize.y*CHIPSIZE - (SCREEN_SIZE.y - world_->GetScreenPlayerPos().y)));

	backManager = new BackGraundManager(world_.get());
	float graundPos = -(world_->GetScreenPlayerPos().y)*1.5f;
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
	world_->clear(false);

	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_STAGE_123), DX_PLAYTYPE_LOOP);
	playerFont_ = new PlayerFont(world_.get(), Vector2::Zero);

	playerFont_->AddEvent(TxtEvent::START_EVENT, "./resources/file/Txt/Start.txt", 5);
	playerFont_->AddEvent(TxtEvent::STARGET_EVENT, "./resources/file/Txt/StarGet.txt", 2);
	playerFont_->AddEvent(TxtEvent::GOOL_EVENT, "./resources/file/Txt/Gool.txt", 4);

	playerFont_->ChangeFont(TxtEvent::START_EVENT);
	playerFont_->StartFont();

	world_->PlayerNotMove(true);
	eventFlag1_ = true;
	eventFlag2_ = true;
}

void FirstGamePlayScene::update() {
	//isClearStage_��true�ɂȂ�����A�X�e�[�W�N���A���̃��U���g��ʂ݂̂��X�V����
	if (isClearStage_) {
		if (clear_.update(name_, nextScene_)) {
			isEnd_ = true;
		};
		return;
	}
	if (!playerFont_->GetEndFont()) world_->PlayerNotMove(false);
	if (keeper_->GetItemCount() >= 1 && eventFlag1_) {
		eventFlag1_ = false;
		playerFont_->ChangeFont(TxtEvent::STARGET_EVENT);
		playerFont_->StartFont();
	}
	if (world_->is_clear() && eventFlag2_) {
		eventFlag2_ = false;
		playerFont_->ChangeFont(TxtEvent::GOOL_EVENT);
		playerFont_->StartFont();
	}
	if (!eventFlag2_&&!playerFont_->GetEndFont()) {
		isClearStage_ = world_->is_clear();
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

	//��������Q�[�����I�����Ă��邩�̔���
	auto player = world_->findActor("Player");



	if (player == nullptr) {
		isEnd_ = true;
		nextScene_ = Scene::GameOver;
	}
	if (world_->is_clear()) {
		nextScene_ = Scene::StageClear;
	}


	if (!isEnd_) {
		isStopped_ ? isEnd_ = pause_.update(nextScene_) : isEnd_ = move_.update(name_, nextScene_, isClearStage_);
	}
	keeper_->setItemCount(world_->getCount());
	//�����܂ŃQ�[�����I�����Ă��邩�̔���
	playerFont_->Update();
}

void FirstGamePlayScene::draw() const {
	backManager->Draw();
	//world�`��
	world_->draw();

	backManager->BackDraw();
	playerFont_->Draw();

	//�N���A����Clear��p�̃V�[����\��
	if (isClearStage_) {
		clear_.draw();
		return;
	}


	//��������A�C�e���擾���̕`��
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
	//�����܂ŃA�C�e�����̕`��

	isStopped_ ? pause_.draw() : move_.draw();
}

void FirstGamePlayScene::end() {
	delete backManager;
	delete playerFont_;
	StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_STAGE_123));
}

bool FirstGamePlayScene::isEnd() const {

	return isEnd_;
}

Scene FirstGamePlayScene::next() const {
	return nextScene_;
}

