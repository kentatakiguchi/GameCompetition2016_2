#include "StageClearScene.h"
#include"../../ResourceLoader/ResourceLoader.h"

static const int MaxTexSize = 1920;
static const int SlideSpeed = 10;
static const float DefBackSpriteChangeTime = 10.f;
static const int TitleFadeInSpeed = 10;

StageClearScene::StageClearScene(SceneDataKeeper* keeper) :
	id(0) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "StageClear";

	nextScene[1] = GamePlay;
	nextScene[2] = MainMenu;
	nextScene[3] = BossStage01;



	//textIDs[0] = TextureID::TEXT_STAGECLEAR_ANM_TEX;
	textIDs[1] = TextureID::TEXT_NEXTSTAGE_TEX;
	textIDs[2] = TextureID::TEXT_MENUBACK_TEX;
	textIDs[3] = TextureID::TEXT_NEXTSTAGE_TEX;



	int listNum = 0;
	listBase.push_back(changeTextList);
	std::vector<std::string> list1;
	list1.push_back("ステージクリア");
	listBase[0] = list1;
	textPosList.push_back(Vector2(200, 200));
	changeTextList.clear();

	listBase.push_back(changeTextList);
	std::vector<std::string> list2;
	list2.push_back("次のステージへ");
	listBase[1] = list2;
	textPoses[1] = Vector2(200, 600);
	textPoses[3] = Vector2(200, 600);
	textPosList.push_back(textPoses[1]);
	changeTextList.clear();
	
	listBase.push_back(changeTextList);
	std::vector<std::string> list3;
	list3.push_back("メニューに戻る");
	listBase[2] = list3;
	textPoses[2] = Vector2(200, 700);
	textPosList.push_back(textPoses[2]);
	changeTextList.clear();


	currentTitleBackID.push_back(TextureID::TITLE_BACK_TEX);
	currentTitleBackID.push_back(TextureID::TITLE_BACK_TEX);

	changeTargetChecker.push_back(0);
	changeTargetChecker.push_back(0);

	baseTitleBackID[0] = TextureID::TITLE_BACK_TEX;
	baseTitleBackID[1] = TextureID::TITLE_BACK2_TEX;
	baseTitleBackID[2] = TextureID::TITLE_BACK3_TEX;
	baseTitleBackID[3] = TextureID::TITLE_BACK4_TEX;

}

StageClearScene::~StageClearScene() {

}

void StageClearScene::start() {

	targetPoint = 1;
	sinCount = 0;
	slideSize = 0;
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	// グラフィックのロード

	for (int i = 0; i < 2; i++) {
		titleBackStageNum[i] = 1;
		//0が1枚目、1が2枚目で、1枚につきMaxTexSize移動フレーム分の時間をスライドの変更時間に追加する
		titleBackChangeTime[i] = DefBackSpriteChangeTime + ((MaxTexSize / SlideSpeed) / 60 * (i));

		if(keeper_->getSceneName()=="stage01")
			currentTitleBackID[i] = TextureID::TITLE_BACK_TEX;

		if (keeper_->getSceneName() == "stage02")
			currentTitleBackID[i] = TextureID::TITLE_BACK2_TEX;

		if (keeper_->getSceneName() == "stage03")
			currentTitleBackID[i] = TextureID::TITLE_BACK3_TEX;

		if (keeper_->getSceneName() == "stage04")
			currentTitleBackID[i] = TextureID::TITLE_BACK4_TEX;

		changeBackChecker[i] = false;
	}


	anmer_ = StageClearTextAnm();
	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_STAGECLEAR), DX_PLAYTYPE_BACK);
}

void StageClearScene::update() {

	anmer_.update_e(Time::GetInstance().deltaTime());

	sinCount += FlashTempo;
	sinCount = sinCount % 360;
	sinCount = min(max(sinCount, 0), 360);

	slideSize += SlideSpeed;
	if (slideSize >= MaxTexSize) {
		slideSize = 0;
	}

	if (targetPoint != 3)
	{
		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_UP)) {
			targetPoint--;
			sinCount = 0;
			PlaySound("./resources/sounds/menuse/menu_cursor.mp3", DX_PLAYTYPE_BACK);
		}
		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_DOWN)) {
			targetPoint++;
			sinCount = 0;
			PlaySound("./resources/sounds/menuse/menu_cursor.mp3", DX_PLAYTYPE_BACK);
		}
		targetPoint = min(max(targetPoint, 1), 2);


		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_CIRCLE))
		{
			isEnd_ = true;
			if (targetPoint == 1 && keeper_->getSceneName() == "stage04")targetPoint = 3;
			PlaySound("./resources/sounds/menuse/menu_decision.mp3", DX_PLAYTYPE_BACK);

		}
	}
}

void StageClearScene::draw() const {

	DrawGraph(MaxTexSize - slideSize, 0, ResourceLoader::GetInstance().getTextureID(currentTitleBackID[0]), TRUE);
	DrawGraph(-slideSize, 0, ResourceLoader::GetInstance().getTextureID(currentTitleBackID[1]), TRUE);


	int strLen, strWidth, center, count,heightPoint;
	count = 0;
	heightPoint=0;
	int forcount = 0;
	center = SCREEN_SIZE.x / 2;

	anmer_.draw_e(Vector2(center-320,textPosList.at(0).y));

	for (auto lists : listBase) {
		for (auto my : lists) {
			if (count == 0)break;

			strLen = strlen(my.c_str());
			strWidth = GetDrawStringWidthToHandle(my.c_str(), strLen, FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));

			if (forcount == targetPoint && forcount != 0)SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(sin(sinCount*MathHelper::Pi / 180)) * 255);
			//DrawStringToHandle(center - (strWidth / 2), textPosList.at(count).y + ((FontManager::GetInstance().GetFontSize(FontName::GamePlayFont))*heightPoint), my.c_str(), GetColor(255, 255, 255), FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
			
			DrawGraph(center - 320, textPosList.at(count).y, ResourceLoader::GetInstance().getTextureID(textIDs.at(count)), TRUE);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			heightPoint++;
		}
		forcount++;
		count++;
		heightPoint = 0;
	}

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawGraph(textPoses.at(targetPoint).x, textPoses.at(targetPoint).y, ResourceLoader::GetInstance().getTextureID(TextureID::SELECT_TARGET_TEX), TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//int strLen, strWidth, center;
	//for (int i = 0; i < changeTextList.size(); i++) {
	//	strLen = strlen(changeTextList[i].c_str());
	//	strWidth = GetDrawStringWidthToHandle(changeTextList[i].c_str(), strLen, FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
	//	center = SCREEN_SIZE.x / 2;
	//	DrawStringToHandle(center - (strWidth / 2), 550 + ((FontManager::GetInstance().GetFontSize(FontName::GamePlayFont))*i), changeTextList[i].c_str(), GetColor(255, 255, 255), FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
	//}

}

void StageClearScene::end() {

}

bool StageClearScene::isEnd() const {
	return isEnd_;
}

Scene StageClearScene::next() const {
	return nextScene.at(targetPoint);
}
