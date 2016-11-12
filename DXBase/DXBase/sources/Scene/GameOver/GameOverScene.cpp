#include "GameOverScene.h"

GameOverScene::GameOverScene(SceneDataKeeper* keeper) :
	id(0) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "GameOver";

	int listNum = 0;
	listBase.push_back(changeTextList);
	std::vector<std::string> list1;
	list1.push_back("リザルト");
	listBase[0] = list1;
	textPosList.push_back(Vector2(200, 200));
	changeTextList.clear();

	listBase.push_back(changeTextList);
	std::vector<std::string> list2;
	list2.push_back("SPACEボタンでタイトルへ");
	listBase[1] = list2;
	textPosList.push_back(Vector2(200, 500));
	changeTextList.clear();

}

GameOverScene::~GameOverScene(){

}

void GameOverScene::start() {
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	// グラフィックのロード
	id = LoadGraph("./resources/Player.png");
}

void GameOverScene::update() {
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::RETURN))	
	{
		if (keeper_->getSceneName() == "stage01") keeper_->setSceneName("stage03");
		else if (keeper_->getSceneName() == "stage02") keeper_->setSceneName("stage01");
		else if (keeper_->getSceneName() == "stage03") keeper_->setSceneName("stage02");

		nextScene_ = Scene::GamePlay;

		isEnd_ = true;

	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::SPACE))
	{
		nextScene_ = Scene::Title;
		isEnd_ = true;
		//ゴールポイントについた時点でシーンを遷移
	}
}

void GameOverScene::draw() const {
	int strLen, strWidth, center, count, heightPoint;
	count = 0;
	heightPoint = 0;
	for (auto lists : listBase) {
		for (auto my : lists) {
			strLen = strlen(my.c_str());
			strWidth = GetDrawStringWidthToHandle(my.c_str(), strLen, FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
			center = SCREEN_SIZE.x / 2;
			DrawStringToHandle(center - (strWidth / 2), textPosList.at(count).y + ((FontManager::GetInstance().GetFontSize(FontName::GamePlayFont))*heightPoint), my.c_str(), GetColor(255, 255, 255), FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
			heightPoint++;
		}
		count++;
		heightPoint = 0;
	}
}

void GameOverScene::end() {

}

bool GameOverScene::isEnd() const {
	return isEnd_;
}

Scene GameOverScene::next() const {
	return nextScene_;
}
