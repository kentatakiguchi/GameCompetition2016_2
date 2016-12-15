#include "StageClearScene.h"
#include"../../ResourceLoader/ResourceLoader.h"

StageClearScene::StageClearScene(SceneDataKeeper* keeper) :
	id(0) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "StageClear";

	nextScene[1] = GamePlay;
	nextScene[2] = MainMenu;
	nextScene[3] = BossStage01;


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

}

StageClearScene::~StageClearScene() {

}

void StageClearScene::start() {

	targetPoint = 1;
	sinCount = 0;
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	// グラフィックのロード
}

void StageClearScene::update() {

	sinCount += FlashTempo;
	sinCount = sinCount % 360;
	sinCount = min(max(sinCount, 0), 360);

	if (targetPoint != 3)
	{
		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_UP)) {
			targetPoint--;
			sinCount = 0;
		}
		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_DOWN)) {
			targetPoint++;
			sinCount = 0;
		}
		targetPoint = min(max(targetPoint, 1), 2);


		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_CIRCLE))
		{
			isEnd_ = true;
			if (targetPoint == 1 && keeper_->getSceneName() == "stage04")targetPoint = 3;
		}
	}
}

void StageClearScene::draw() const {

	int strLen, strWidth, center, count,heightPoint;
	count = 0;
	heightPoint=0;
	int forcount = 0;
	for (auto lists : listBase) {
		for (auto my : lists) {
			strLen = strlen(my.c_str());
			strWidth = GetDrawStringWidthToHandle(my.c_str(), strLen, FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
			center = SCREEN_SIZE.x / 2;

			if (forcount == targetPoint && forcount != 0)SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(sin(sinCount*MathHelper::Pi / 180)) * 255);
			DrawStringToHandle(center - (strWidth / 2), textPosList.at(count).y + ((FontManager::GetInstance().GetFontSize(FontName::GamePlayFont))*heightPoint), my.c_str(), GetColor(255, 255, 255), FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
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
