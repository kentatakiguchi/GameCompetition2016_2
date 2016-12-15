#include "GameClearScene.h"
#include"../../ResourceLoader/ResourceLoader.h"

GameClearScene::GameClearScene(SceneDataKeeper* keeper) :
	id(0) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "GameClear";

	nextScene[1] = MainMenu;


	int listNum = 0;
	listBase.push_back(changeTextList);
	std::vector<std::string> list1;
	list1.push_back("ゲームクリア");
	listBase[0]=list1;
	textPosList.push_back(Vector2(200, 200));
	changeTextList.clear();

	listBase.push_back(changeTextList);
	std::vector<std::string> list2;
	list2.push_back("メニューに戻る");
	listBase[1] = list2;
	textPoses[1] = Vector2(200, 600);
	textPosList.push_back(textPoses[1]);
	changeTextList.clear();
	//OutputDebugString(listBase[0].at(0).c_str());

}

GameClearScene::~GameClearScene() {

}

void GameClearScene::start() {
	targetPoint = 1;
	sinCount = 0;

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
}

void GameClearScene::update() {
	sinCount += FlashTempo;
	sinCount = sinCount % 360;
	sinCount = min(max(sinCount, 0), 360);
	
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_UP)) {
		targetPoint--;
		sinCount = 0;
	}
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_DOWN)) {
		targetPoint++;
		sinCount = 0;
	}
	targetPoint = min(max(targetPoint, 1), 1);

	
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_CIRCLE))	isEnd_ = true;
}

void GameClearScene::draw() const {
	int strLen, strWidth, center, count, heightPoint;
	count = 0;
	heightPoint = 0;
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
	DrawGraph(textPoses.at(targetPoint).x, textPoses.at(targetPoint).y, ResourceLoader::GetInstance().getTextureID(TextureID::SELECT_TARGET_TEX), TRUE);

}

void GameClearScene::end() {

}

bool GameClearScene::isEnd() const {
	return isEnd_;
}

Scene GameClearScene::next() const {
	return Scene::MainMenu;
}
